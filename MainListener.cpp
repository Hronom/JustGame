#include "MainListener.h"

MainListener::MainListener(OIS::InputManager* xInputManager)
{
	mInputManager = xInputManager;
}


MainListener::~MainListener()
{

}

void MainListener::init()
{
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
}

void MainListener::windowResized(Ogre::RenderWindow* xRenderWindow)
{
	unsigned int xWidth, xHeight, xDepth;
	int xLeft, xTop;
	xRenderWindow->getMetrics(xWidth, xHeight, xDepth, xLeft, xTop);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = xWidth;
	ms.height = xHeight;
}

void MainListener::windowClosed(Ogre::RenderWindow* xRenderWindow)
{
	if(mInputManager != 0)
	{
		mInputManager->destroyInputObject( mMouse );
		mInputManager->destroyInputObject( mKeyboard );
	}
}

bool MainListener::frameRenderingQueued(const Ogre::FrameEvent& xFrameEvent)
{
    mKeyboard->capture();
    mMouse->capture();
 
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
 
    return true;
}