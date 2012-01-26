#include "PlayGameState.h"

PlayGameState::PlayGameState(iCore *xCore)
{
	mCore = xCore;

	mPlayer = 0;
	mEnemyCount = 0;
	mBulletsCount = 0;

	Ogre::ColourValue xColor = Ogre::ColourValue(0.104f, 0.234f, 0.140f, 0.0f);
	// create ManualObject
	mGridManualObject = new Ogre::ManualObject("grid_manual");
	
	Ogre::Real xGridDistance = 10.0f;
	for (Ogre::Real i = -50.0f; i < 50.0f; i+=1.0f)
	{
		// Draw vertical line
		mGridManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
		mGridManualObject->position(i * xGridDistance, -500.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->position(i * xGridDistance, +500.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->end();
		// Draw gorizontal line
		mGridManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
		mGridManualObject->position(-500.0f, i * xGridDistance, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->position(+500.0f, i * xGridDistance, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->end();
	}
	// add ManualObject to the RootSceneNode (so it will be visible)
	Ogre::MeshPtr xMeshPtr = mGridManualObject->convertToMesh("grid_mesh");

	mGridSceneNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode("grid_node");
	mGridSceneNode->attachObject(mGridManualObject);

	/*Ogre::StaticGeometry *xStaticGeometry = new Ogre::StaticGeometry(mCore->getSceneManager(), "grid_stat");
	xStaticGeometry->addSceneNode(mGridSceneNode);
	xStaticGeometry->build();*/
}

PlayGameState::~PlayGameState()
{
	mGridSceneNode->detachAllObjects();
	mCore->getSceneManager()->destroyManualObject(mGridManualObject);
	mGridSceneNode->removeAndDestroyAllChildren();
	mCore->getSceneManager()->destroySceneNode(mGridSceneNode->getName());

	exit();
}

void PlayGameState::enter()
{
	setPlayer(Ogre::Vector2(0,0));

	Ogre::Vector2 xVectorPos(-100.0f,-100.0f);
	for(int i=0; i<3; i++)
		addEnemy(xVectorPos.randomDeviant(100));
}

void PlayGameState::exit()
{
	mEnemyCount = 0;
	mBulletsCount = 0;

	if(mPlayer != 0)
	{
		delete mPlayer;
		mPlayer = 0;
	}

	std::list<GameObject*>::iterator xElement;

	xElement = mUnits.begin();
	while(xElement != mUnits.end())
	{
		delete *xElement;
		++xElement;
	}
	mUnits.clear();

	xElement = mBullets.begin();
	while(xElement != mBullets.end())
	{
		delete *xElement;
		++xElement;
	}
	mBullets.clear();

	xElement = mForDelete.begin();
	while(xElement != mForDelete.end())
	{
		delete *xElement;
		++xElement;
	}
	mForDelete.clear();
}

void PlayGameState::needUpdate(const Ogre::FrameEvent& evt)
{
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstance().getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
	Ogre::Ray xMouseRay =  mCore->getCamera()->getCameraToViewportRay(xMousePosition.left / float(xSize.width), xMousePosition.top / float(xSize.height));
	Ogre::Vector3 xVector = xMouseRay.getPoint(100);//почему 100? Расстояние между камерой и нулевой точкой оси z равно 100

	mPlayer->rotateTo(Ogre::Vector2(xVector.x, xVector.y));

	// Обновление игрока
	mPlayer->update(evt);

	// Установка нового положения камеры
	Ogre::Vector2 xPlayerPos;
	xPlayerPos = mPlayer->getCurrentPos();

	Ogre::Vector3 xNewCameraPos;
	xNewCameraPos = mCore->getCamera()->getPosition();
	xNewCameraPos.x = xPlayerPos.x;
	xNewCameraPos.y = xPlayerPos.y;

	mCore->getCamera()->setPosition(xNewCameraPos);

	std::list<GameObject*>::iterator xUnit;
	xUnit = mUnits.begin();
	// Обновление юнитов
	while(xUnit != mUnits.end())
	{
		(*xUnit)->update(evt);

		(*xUnit)->rotateTo(mPlayer->getCurrentPos());

		if(mPlayer->getCurrentPos().distance((*xUnit)->getCurrentPos()) > 33.3f) 
		{
			(*xUnit)->shoot(false);
			(*xUnit)->moveUp(true);
		}
		else
		{
			(*xUnit)->moveUp(false);
			(*xUnit)->shoot(true);
		}	

		if((*xUnit)->getCurrentHealth() <= 0)
		{
			mForDelete.push_back((*xUnit));
			xUnit = mUnits.erase(xUnit);
		}
		else
			++xUnit;
	}

	// Обновление пуль
	std::list<GameObject*>::iterator xBullet;
	xBullet = mBullets.begin();
	while(xBullet != mBullets.end())
	{
		(*xBullet)->update(evt);

		if((*xBullet)->getCurrentHealth() <= 0)
		{
			mForDelete.push_back((*xBullet));
			xBullet = mBullets.erase(xBullet);
		}
		else
			++xBullet;
	}

	checkBullets();

	// Обновление объектов для удаления
	std::list<GameObject*>::iterator xForDelete;
	xForDelete = mForDelete.begin();
	while(xForDelete != mForDelete.end())
	{
		(*xForDelete)->update(evt);

		if((*xForDelete)->isNeedDelete() == true) 
		{
			delete (*xForDelete);
			xForDelete = mForDelete.erase(xForDelete);
		}
		else
			++xForDelete;
	}

	if(mPlayer->getCurrentHealth() <= 0)
	{
		mCore->needSwitchToStateId(3);
		return;
	}

	if(mUnits.size() <= 0)
	{
		mCore->needSwitchToStateId(2);
		return;
	}
}

void PlayGameState::mouseMoved(const OIS::MouseEvent& e)
{
	/*
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstance().getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
	Ogre::Ray xMouseRay =  mCore->getCamera()->getCameraToViewportRay(xMousePosition.left / float(xSize.width), xMousePosition.top / float(xSize.height));
	Ogre::Vector3 xVector = xMouseRay.getPoint(100);//почему 100? Расстояние между камерой и нулевой точкой оси z равно 100

	mPlayer->rotateTo(Ogre::Vector2(xVector.x, xVector.y));*/
}

void PlayGameState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left) mPlayer->shoot(true);
}

void PlayGameState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left) mPlayer->shoot(false);
}

void PlayGameState::keyPressed(const OIS::KeyEvent& e)
{
	Ogre::Vector2 xVectorPos(-100.0f,-100.0f);

	switch (e.key)
	{
	case OIS::KC_W:
		mPlayer->moveUp(true); 
		break;
	case OIS::KC_S:
		mPlayer->moveDown(true); 
		break;
	case OIS::KC_D:
		mPlayer->moveRight(true); 
		break;
	case OIS::KC_A:
		mPlayer->moveLeft(true); 
		break;
	case OIS::KC_E:
		addEnemy(xVectorPos.randomDeviant(100));
		break;
	default: break;
	}
}

void PlayGameState::keyReleased(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KC_W:
		mPlayer->moveUp(false); 
		break;
	case OIS::KC_S:
		mPlayer->moveDown(false); 
		break;
	case OIS::KC_D:
		mPlayer->moveRight(false); 
		break;
	case OIS::KC_A:
		mPlayer->moveLeft(false); 
		break;
	case OIS::KC_ESCAPE:
		mCore->needShutdown();
		break;
	default: break;
	}
}

void PlayGameState::buttonClick(MyGUI::WidgetPtr xSender)
{
}

void PlayGameState::setPlayer(Ogre::Vector2 xPos)
{
	mPlayer = new Player(mCore, this, "Player", xPos);
	mPlayer->setObjectString("Player");
}

void PlayGameState::addEnemy(Ogre::Vector2 xPos)
{
	mEnemyCount++;
	Ogre::String xEnemyName;
	xEnemyName = "Enemy" + Ogre::StringConverter::toString(mEnemyCount);

	Enemy *xEnemy;
	xEnemy = new Enemy(mCore, this, xEnemyName, xPos);
	xEnemy->setObjectString("Enemy");
	mUnits.push_back(xEnemy);
}

void PlayGameState::addBullet(Ogre::String xObjectString, Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mBulletsCount++;
	Ogre::String xBulletName;
	xBulletName = "Bullet" + Ogre::StringConverter::toString(mBulletsCount);

	Bullet *xBullet;
	xBullet = new Bullet(mCore, this, xBulletName, xPos, xDestination);
	xBullet->setObjectString(xObjectString);
	mBullets.push_back(xBullet);
}

void PlayGameState::checkBullets()
{
	// Обновление пуль для игрока
	{
		GameObject *xUnit = mPlayer;
		Ogre::String xUnitType = xUnit->getObjectString();
		Ogre::Vector2 xUnitPos = xUnit->getCurrentPos();
		float xUnitRadius = xUnit->getObjectRadius();

		std::list<GameObject*>::iterator xElement;
		xElement = mBullets.begin();
		while(xElement != mBullets.end())
		{
			GameObject *xBullet = (*xElement);
			Ogre::String xBulletType = xBullet->getObjectString();
			Ogre::Vector2 xBulletPos = xBullet->getCurrentPos();
			float xBulletRadius = xBullet->getObjectRadius();

			if(xUnit->getCurrentHealth() > 0 && xBulletType != xUnitType && xBulletPos.distance(xUnitPos) <= xBulletRadius+xUnitRadius )
			{
				xUnit->doDamage(xBullet->getDamage());
				xBullet->doDamage(10);
				xElement = mBullets.erase(xElement);
				mForDelete.push_back(xBullet);
			}
			else
				++xElement;
		}
	}

	// Обновление пуль для врагов
	std::list<GameObject*>::iterator xElement;
	xElement = mUnits.begin();
	while(xElement != mUnits.end())
	{
		GameObject *xUnit = (*xElement);
		Ogre::String xUnitType = xUnit->getObjectString();
		Ogre::Vector2 xUnitPos = xUnit->getCurrentPos();
		float xUnitRadius = xUnit->getObjectRadius();

		std::list<GameObject*>::iterator xElement2;
		xElement2 = mBullets.begin();
		while(xElement2 != mBullets.end())
		{
			GameObject *xBullet = (*xElement2);
			Ogre::String xBulletType = xBullet->getObjectString();
			Ogre::Vector2 xBulletPos = xBullet->getCurrentPos();
			float xBulletRadius = xBullet->getObjectRadius();


			if(xUnit->getCurrentHealth() > 0 && xBulletType != xUnitType && xBulletPos.distance(xUnitPos) <= xBulletRadius+xUnitRadius )
			{
				xUnit->doDamage(xBullet->getDamage());
				xBullet->doDamage(10);
				xElement2 = mBullets.erase(xElement2);
				mForDelete.push_back(xBullet);
			}
			else
				++xElement2;
		}

		++xElement;
	}
}
