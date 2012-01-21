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
	mCore->addPlayer(Ogre::Vector3(10,10,0));
}

void PlayGameState::exit()
{
}

void PlayGameState::needUpdate(const Ogre::FrameEvent& evt)
{
}

void PlayGameState::mouseMoved(const OIS::MouseEvent& e)
{
}

void PlayGameState::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void PlayGameState::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
}

void PlayGameState::keyPressed(const OIS::KeyEvent& e)
{
	if(e.key == OIS::KC_W) mCore->movePlayerUp(); 

	if(e.key == OIS::KC_ESCAPE) mCore->needShutdown();
}

void PlayGameState::keyReleased(const OIS::KeyEvent& e)
{
}

void PlayGameState::buttonClick(MyGUI::WidgetPtr xSender)
{
}
