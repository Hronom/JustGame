#ifndef GRAPHICSYSTEM_H
#define GRAPHICSYSTEM_H

#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OGRE\OgreWindowEventUtilities.h>

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <OIS\OIS.h>

#include "iMainListener.h"

class GraphicSystem : public Ogre::FrameListener, public Ogre::WindowEventListener
{ 
private: 
	iMainListener *mMainListener;

	Ogre::String mOgreCfg;
	Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;
	Ogre::String mLogFileName;

	Ogre::Root *mRoot;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::Camera* mCamera; 

	MyGUI::OgrePlatform *mPlatform;
	MyGUI::Gui *mMyGUI;

public: 
	GraphicSystem(iMainListener *xMainListener);
	~GraphicSystem();
	bool init();
	void start();

private:
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	virtual void windowResized(Ogre::RenderWindow* xRenderWindow);
	virtual void windowClosed(Ogre::RenderWindow* xRenderWindow);

public:
	void injectMouseMoved( const OIS::MouseEvent &arg );
	void injectMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	void injectMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	void injectKeyPressed( const OIS::KeyEvent &arg );
	void injectKeyReleased( const OIS::KeyEvent &arg );

	unsigned int getWinHandle();
	unsigned int getWinWidth();
	unsigned int getWinHeight();
	Ogre::SceneManager* getSceneManager();
}; 

#endif


