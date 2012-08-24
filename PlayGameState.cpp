#include "PlayGameState.h"
#include <GraphicSystem.h>
#include <PhysicsSystem.h>
#include <StatesSystem.h>

PlayGameState::PlayGameState()
{
	mRaySceneQuery = 0;
	mPlayer = 0;
	mGridManualObject = 0;
	mGridSceneNode = 0;
	mEnemyCount = 0;
	mBulletsCount = 0;
}

PlayGameState::~PlayGameState()
{
	exit();
}

void PlayGameState::prepareState()
{
	JGC::StatesSystem::instance()->injectStateLoadProgress(0, "Loading game UI");
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstancePtr()->loadLayout("GameUI.layout");
	MyGUI::LayerManager::getInstancePtr()->resizeView(MyGUI::RenderManager::getInstancePtr()->getViewSize());
	mCurrentLayoutWidgets[0]->setVisible(false);

	mRaySceneQuery = JGC::GraphicSystem::instance()->getSceneManager()->createRayQuery(Ogre::Ray());

	JGC::StatesSystem::instance()->injectStateLoadProgress(0, "Loading world");
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

	mGridSceneNode = JGC::GraphicSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("grid_node");
	mGridSceneNode->attachObject(mGridManualObject);

	JGC::StatesSystem::instance()->injectStateLoadProgress(50, "Loading player");

	setPlayer(Ogre::Vector2(0,0));
	MyGUI::ProgressBar *xProgressBar;
	xProgressBar = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::ProgressBar>("PlayerHealthBar");
	xProgressBar->setProgressRange(mPlayer->getCurrentHealth());
	xProgressBar->setProgressPosition(mPlayer->getCurrentHealth());

	JGC::StatesSystem::instance()->injectStateLoadProgress(70, "Loading enemys");

	Ogre::Vector2 xVectorPos(-100.0f,-100.0f);
	for(int i=0; i<3; i++)
		addEnemy(xVectorPos.randomDeviant(100));

	JGC::StatesSystem::instance()->injectStateLoadProgress(100, "Loading complete");
}

void PlayGameState::enter()
{
	mCurrentLayoutWidgets[0]->setVisible(true);
}

void PlayGameState::exit()
{
    MyGUI::PointerManager::getInstancePtr()->setPointer("arrow");

	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}

	if(mRaySceneQuery != 0)
	{
		JGC::GraphicSystem::instance()->getSceneManager()->destroyQuery(mRaySceneQuery);
		mRaySceneQuery = 0;
	}

	if(mGridManualObject != 0)
	{
		JGC::GraphicSystem::instance()->getSceneManager()->destroyManualObject(mGridManualObject);
		mGridManualObject = 0;
	}

	if(mGridSceneNode != 0)
	{
		mGridSceneNode->removeAndDestroyAllChildren();
		JGC::GraphicSystem::instance()->getSceneManager()->destroySceneNode(mGridSceneNode);
		mGridSceneNode = 0;
	}

	mEnemyCount = 0;
	mBulletsCount = 0;

	if(mPlayer != 0)
	{
		delete mPlayer;
		mPlayer = 0;
	}

	std::list<MyGameObject*>::iterator xElement;

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

void PlayGameState::injectUpdate(const float& xTimeSinceLastFrame)
{
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstancePtr()->getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstancePtr()->getViewSize();
	Ogre::Ray xMouseRay =  JGC::GraphicSystem::instance()->getCamera()->getCameraToViewportRay(xMousePosition.left / float(xSize.width), xMousePosition.top / float(xSize.height));
	Ogre::Vector3 xVector = xMouseRay.getPoint(100);//почему 100? Расстояние между камерой и нулевой точкой оси z равно 100

	mPlayer->rotateTo(Ogre::Vector2(xVector.x, xVector.y));

	// Обновление игрока
	mPlayer->update(xTimeSinceLastFrame);

	// Обновление юнитов
	std::list<MyGameObject*>::iterator xUnit;
	xUnit = mUnits.begin();
	while(xUnit != mUnits.end())
	{
		(*xUnit)->update(xTimeSinceLastFrame);

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
	std::list<MyGameObject*>::iterator xBullet;
	xBullet = mBullets.begin();
	while(xBullet != mBullets.end())
	{
		(*xBullet)->update(xTimeSinceLastFrame);

		if((*xBullet)->getCurrentHealth() <= 0)
		{
			mForDelete.push_back((*xBullet));
			xBullet = mBullets.erase(xBullet);
		}
		else
			++xBullet;
	}
	
	// Нанесение урона пулями
	int xNumManifolds = JGC::PhysicsSystem::instance()->getDynamicsWorld()->getDispatcher()->getNumManifolds();
	for (int i=0; i<xNumManifolds; i++)
	{
		btPersistentManifold* xContactManifold =  JGC::PhysicsSystem::instance()->getDynamicsWorld()->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* xObjA = static_cast<const btCollisionObject*>(xContactManifold->getBody0());
        const btCollisionObject* xObjB = static_cast<const btCollisionObject*>(xContactManifold->getBody1());

		MyGameObject *xGameObjectA = static_cast<MyGameObject*>(xObjA->getUserPointer());
		MyGameObject *xGameObjectB = static_cast<MyGameObject*>(xObjB->getUserPointer());

		xGameObjectA->makeDamage(xGameObjectB->getDamage());
		xGameObjectB->makeDamage(xGameObjectA->getDamage());
	}

	// Обновление отображения здоровья игрока
	MyGUI::ProgressBar *xProgressBar;
	xProgressBar = JGC::GraphicSystem::instance()->getGui()->findWidget<MyGUI::ProgressBar>("PlayerHealthBar");
	xProgressBar->setProgressPosition(mPlayer->getCurrentHealth());

	// Обновление объектов для удаления
	std::list<MyGameObject*>::iterator xForDelete;
	xForDelete = mForDelete.begin();
	while(xForDelete != mForDelete.end())
	{
		(*xForDelete)->update(xTimeSinceLastFrame);

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
		JGC::StatesSystem::instance()->needSwitchToState("LoseState");
		return;
	}

	if(mUnits.size() <= 0)
	{
		JGC::StatesSystem::instance()->needSwitchToState("WinState");
		return;
	}
}

void PlayGameState::injectMouseMoved(const OIS::MouseEvent& e)
{
	MyGUI::PointerManager::getInstancePtr()->setPointer("arrow");
	std::string xString;
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstancePtr()->getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
	Ogre::Ray ray = JGC::GraphicSystem::instance()->getCamera()->getCameraToViewportRay(xMousePosition.left/float(xSize.width), xMousePosition.top/float(xSize.height));
	mRaySceneQuery->setRay(ray);
	mRaySceneQuery->setSortByDistance(true);
	Ogre::RaySceneQueryResult& xResult = mRaySceneQuery->execute();
	for (Ogre::RaySceneQueryResult::iterator xIter = xResult.begin(); xIter != xResult.end(); ++xIter)
	{
		if (xIter->movable != 0)
		{
			Ogre::Any xAny = xIter->movable->getUserAny();
			int *x = Ogre::any_cast<int*>(xAny);
			if ((*x) == 1)
				MyGUI::PointerManager::getInstancePtr()->setPointer("hand");
		}
	}
}

void PlayGameState::injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left) mPlayer->shoot(true);
}

void PlayGameState::injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left) mPlayer->shoot(false);
}

void PlayGameState::injectKeyPressed(const OIS::KeyEvent& e)
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

void PlayGameState::injectKeyReleased(const OIS::KeyEvent& e)
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
		JGC::MainSystem::instance()->needShutdown();
		break;
	default: break;
	}
}

void PlayGameState::setPlayer(Ogre::Vector2 xPos)
{
	mPlayer = new Player(this, "Player", PLAYER_GROUP, xPos);
}

void PlayGameState::addEnemy(Ogre::Vector2 xPos)
{
	mEnemyCount++;
	Ogre::String xEnemyName;
	xEnemyName = "Enemy" + Ogre::StringConverter::toString(mEnemyCount);

	Enemy *xEnemy;
	xEnemy = new Enemy(this, xEnemyName, ENEMY_GROUP, xPos);
	mUnits.push_back(xEnemy);
}

void PlayGameState::addBullet(short xObjectCollideWith, Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mBulletsCount++;
	Ogre::String xBulletName;
	xBulletName = "Bullet" + Ogre::StringConverter::toString(mBulletsCount);

	Bullet *xBullet;
	xBullet = new Bullet(this, xBulletName, xObjectCollideWith, xPos, xDestination);
	mBullets.push_back(xBullet);
}
