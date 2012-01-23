#include "PlayGameState.h"

PlayGameState::PlayGameState(iCore *xCore)
{
	mCore = xCore;

	mEnemyCount = 0;
	mBulletsCount = 0;
}

PlayGameState::~PlayGameState()
{
}

void PlayGameState::enter()
{
	setPlayer(Ogre::Vector2(0,0));

	addEnemy(Ogre::Vector2(((rand()%50)+1), ((rand()%50)+1)));
	addEnemy(Ogre::Vector2(((rand()%50)+1), ((rand()%50)+1)));
	addEnemy(Ogre::Vector2(((rand()%50)+1), ((rand()%50)+1)));
}

void PlayGameState::exit()
{
}

void PlayGameState::needUpdate(const Ogre::FrameEvent& evt)
{
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

	// Обновление пуль
	for(int i=0; i<mBullets.size(); i++)
		mBullets[i]->update(evt);

	// Обновление юнитов
	for(int i=0; i<mUnits.size(); i++)
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
	}
}

void PlayGameState::mouseMoved(const OIS::MouseEvent& e)
{
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstance().getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
	Ogre::Ray xMouseRay =  mCore->getCamera()->getCameraToViewportRay(xMousePosition.left / float(xSize.width), xMousePosition.top / float(xSize.height));
	Ogre::Vector3 xVector = xMouseRay.getPoint(100);//почему 100? Расстояние между камерой и нулевой точкой оси z равно 100

	mPlayer->rotateTo(Ogre::Vector2(xVector.x, xVector.y));
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
}

void PlayGameState::addEnemy(Ogre::Vector2 xPos)
{
	mEnemyCount++;
	Ogre::String xEnemyName;
	xEnemyName = "Enemy" + Ogre::StringConverter::toString(mEnemyCount);

	Enemy *xEnemy;
	xEnemy = new Enemy(mCore, this, xEnemyName, xPos);
	mUnits.push_back(xEnemy);
}

void PlayGameState::addBullet(Ogre::Vector2 xPos, Ogre::Vector2 xDestination)
{
	mBulletsCount++;
	Ogre::String xBulletName;
	xBulletName = "Bullet" + Ogre::StringConverter::toString(mBulletsCount);

	Bullet *xBullet;
	xBullet = new Bullet(mCore, this, xBulletName, xPos, xDestination);
	mBullets.push_back(xBullet);
}
