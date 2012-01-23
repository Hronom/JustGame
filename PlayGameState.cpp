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
	for (Ogre::Real i = -50.0f; i < 50.0f; i+=1.0f)
	{
		mGridManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
		mGridManualObject->position(i * 10.0f, -1500.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->position(i * 10.0f, +1500.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->end();
		mGridManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
		mGridManualObject->position(-1500.0f, i * 10.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->position(1500.0f, i * 10.0f, -100.0f);
		mGridManualObject->colour(xColor);
		mGridManualObject->end();
	}
	// add ManualObject to the RootSceneNode (so it will be visible)
	mGridManualObject->convertToMesh("grid_mesh");
	mGridSceneNode = mCore->getSceneManager()->getRootSceneNode()->createChildSceneNode("grid_node");
	mGridSceneNode->attachObject(mGridManualObject);
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

	for(unsigned i=0; i<mUnits.size(); i++)
		delete mUnits[i];
	mUnits.clear();

	for(unsigned i=0; i<mBullets.size(); i++)
		delete mBullets[i];
	mBullets.clear();

	for(unsigned i=0; i<mForDelete.size(); i++)
		delete mForDelete[i];
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

	// Обновление юнитов
	for(unsigned i=0; i<mUnits.size(); i++)
	{
		mUnits[i]->update(evt);

		mUnits[i]->rotateTo(mPlayer->getCurrentPos());

		if(mPlayer->getCurrentPos().distance(mUnits[i]->getCurrentPos()) > 33.3f) 
		{
			mUnits[i]->shoot(false);
			mUnits[i]->moveUp(true);
		}
		else
		{
			mUnits[i]->moveUp(false);
			mUnits[i]->shoot(true);
		}	

		if(mUnits[i]->getCurrentHealth() <= 0)
		{
			mForDelete.push_back(mUnits[i]);
			mUnits.erase(mUnits.begin() + i);
		}
	}

	// Обновление пуль
	for(unsigned i=0; i<mBullets.size(); i++)
	{
		mBullets[i]->update(evt);

		if(mBullets[i]->getCurrentHealth() <= 0)
		{
			mForDelete.push_back(mBullets[i]);
			mBullets.erase(mBullets.begin() + i);
		}
	}

	checkBullets();

	// Обновление объектов для удаления
	for(unsigned i=0; i<mForDelete.size(); i++)
	{
		mForDelete[i]->update(evt);

		if(mForDelete[i]->isNeedDelete() == true) 
		{
			delete mForDelete[i];
			mForDelete.erase(mForDelete.begin() + i);
		}
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

		for(unsigned y=0; y<mBullets.size(); y++)
		{
			GameObject *xBullet = mBullets[y];
			Ogre::String xBulletType = xBullet->getObjectString();
			Ogre::Vector2 xBulletPos = xBullet->getCurrentPos();
			float xBulletRadius = xBullet->getObjectRadius();


			if(xUnit->getCurrentHealth() > 0 && xBulletType != xUnitType && xBulletPos.distance(xUnitPos) <= xBulletRadius+xUnitRadius )
			{
				xUnit->doDamage(xBullet->getDamage());
				mBullets[y]->doDamage(10);
				mBullets.erase(mBullets.begin()+y);
				mForDelete.push_back(xBullet);
			}
		}
	}

	// Обновление пуль для врагов
	for(unsigned x=0; x<mUnits.size(); x++)
	{
		GameObject *xUnit = mUnits[x];
		Ogre::String xUnitType = xUnit->getObjectString();
		Ogre::Vector2 xUnitPos = xUnit->getCurrentPos();
		float xUnitRadius = xUnit->getObjectRadius();

		for(unsigned y=0; y<mBullets.size(); y++)
		{
			GameObject *xBullet = mBullets[y];
			Ogre::String xBulletType = xBullet->getObjectString();
			Ogre::Vector2 xBulletPos = xBullet->getCurrentPos();
			float xBulletRadius = xBullet->getObjectRadius();


			if(xUnit->getCurrentHealth() > 0 && xBulletType != xUnitType && xBulletPos.distance(xUnitPos) <= xBulletRadius+xUnitRadius )
			{
				xUnit->doDamage(xBullet->getDamage());
				mBullets[y]->doDamage(10);
				mBullets.erase(mBullets.begin()+y);
				mForDelete.push_back(xBullet);
			}
		}
	}
}
