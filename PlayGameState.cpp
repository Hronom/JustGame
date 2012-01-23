#include "PlayGameState.h"

PlayGameState::PlayGameState(iCore *xCore)
{
	mCore = xCore;
}

PlayGameState::~PlayGameState()
{
}

void PlayGameState::enter()
{
	mPlayer = mCore->addPlayer(Ogre::Vector2(0,0));

	GameObject *xEnemy;
	xEnemy = mCore->addEnemy(Ogre::Vector2( ((rand()%30)+1), ((rand()%30)+1)));
	mEnemys.push_back(xEnemy);
	xEnemy = mCore->addEnemy(Ogre::Vector2( ((rand()%30)+1), ((rand()%30)+1)));
	mEnemys.push_back(xEnemy);
	xEnemy = mCore->addEnemy(Ogre::Vector2( ((rand()%30)+1), ((rand()%30)+1)));
	mEnemys.push_back(xEnemy);
}

void PlayGameState::exit()
{
}

void PlayGameState::needUpdate(const Ogre::FrameEvent& evt)
{
	for(int i=0; i<mEnemys.size(); i++)
	{
		mEnemys[i]->rotateTo(mPlayer->getCurrentPos());

		if(mPlayer->getCurrentPos().distance(mEnemys[i]->getCurrentPos()) > 33.3f) 
		{
			mEnemys[i]->shoot(false);
			mEnemys[i]->moveUp(true);
		}
		else
		{
			mEnemys[i]->moveUp(false);
			mEnemys[i]->shoot(true);
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
