#include "MainClass.h"

#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

MainClass::MainClass(): mRoot(0),  mResourcesCfg(Ogre::StringUtil::BLANK), mPluginsCfg(Ogre::StringUtil::BLANK)
{
	mOgreCfg = "ogre.cfg";
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
	mLogFileName = "ogre.log";
}

MainClass::~MainClass()
{
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, mMainListener);

	OIS::InputManager::destroyInputSystem(mInputManager);
	mInputManager = 0;

	delete mRoot;
}

bool MainClass::start()
{
	if(initRoot() == false) 
		return false;

	initResources();

	initScene();

	initOIS();

	mMainListener = new MainListener(mInputManager);
	mMainListener->init();

	//Set initial mouse clipping size
	mMainListener->windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, mMainListener);

	/*while(true)
	{
	// Pump window messages for nice behaviour
	Ogre::WindowEventUtilities::messagePump();

	if(mWindow->isClosed() == true)
	{
	return false;
	}

	// Render a frame
	if(mRoot->renderOneFrame() == false) return false;
	}*/

	mRoot->addFrameListener(mMainListener);

	mRoot->startRendering();

	return true;
}

bool MainClass::initRoot()
{
	mRoot = new Ogre::Root(mPluginsCfg, mOgreCfg, mLogFileName);

	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;

	mWindow = mRoot->initialise(true, "JustGame");

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	return true;
}

void MainClass::initResources()
{
	Ogre::ConfigFile xResourcesCfgFile;
	xResourcesCfgFile.load(mResourcesCfg);

	Ogre::ConfigFile::SectionIterator seci = xResourcesCfgFile.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}

void  MainClass::initScene()
{
	// Create the SceneManager, in this case a generic one
	mSceneManager = mRoot->createSceneManager("DefaultSceneManager");

	Ogre::Camera* mCamera;

	// Create the camera
	mCamera = mSceneManager->createCamera("PlayerCam");

	// Position it at 80 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);


	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));



	Ogre::Entity* ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");

	Ogre::SceneNode* headNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	headNode->attachObject(ogreHead);

	// Set ambient light
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light* l = mSceneManager->createLight("MainLight");
	l->setPosition(20,80,50);
}

void MainClass::initOIS()
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

}