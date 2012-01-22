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
	mControlledPlayer = mCore->addPlayer(Ogre::Vector2(0,0));
}

void PlayGameState::exit()
{
}

void PlayGameState::needUpdate(const Ogre::FrameEvent& evt)
{
}

void PlayGameState::mouseMoved(const OIS::MouseEvent& e)
{
	MyGUI::IntPoint xMousePosition = MyGUI::InputManager::getInstance().getMousePosition();
	MyGUI::IntSize xSize = MyGUI::RenderManager::getInstance().getViewSize();
	Ogre::Ray xMouseRay =  mCore->getCamera()->getCameraToViewportRay(xMousePosition.left / float(xSize.width), xMousePosition.top / float(xSize.height));
	Ogre::Vector3 xVector = xMouseRay.getPoint(100);//почему 100? Расстояние между камерой и нулевой точкой оси z равно 100

	mControlledPlayer->rotateTo(Ogre::Vector2(xVector.x, xVector.y));
}

void PlayGameState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void PlayGameState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void PlayGameState::keyPressed(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KC_W:
		mControlledPlayer->moveUp(true); 
		break;
	case OIS::KC_S:
		mControlledPlayer->moveDown(true); 
		break;
	case OIS::KC_D:
		mControlledPlayer->moveRight(true); 
		break;
	case OIS::KC_A:
		mControlledPlayer->moveLeft(true); 
		break;
	default: break;
	}
}

void PlayGameState::keyReleased(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KC_W:
		mControlledPlayer->moveUp(false); 
		break;
	case OIS::KC_S:
		mControlledPlayer->moveDown(false); 
		break;
	case OIS::KC_D:
		mControlledPlayer->moveRight(false); 
		break;
	case OIS::KC_A:
		mControlledPlayer->moveLeft(false); 
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
