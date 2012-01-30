#include "MainClass.h"

//using namespace OgreBulletCollisions;
//using namespace OgreBulletDynamics;

MainClass::MainClass()
{
	mOgreCfg = "ogre.cfg";
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
	mLogFileName = "ogre.log";

	//-----------------------------------------------------
	// 1 �������� ����
	//-----------------------------------------------------
	mRoot = new Ogre::Root();

//	OgreBullet::OgreBulletListener::init(root, win, application);
}

MainClass::~MainClass()
{
	//----------------------------------------------------
	// 9 ��������
	//----------------------------------------------------
	delete mMainManager;
	mMainManager = 0;

	mMyGUI->shutdown();
	delete mMyGUI;
	mMyGUI = 0;   
	mPlatform->shutdown();
	delete mPlatform;
	mPlatform = 0;

	Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, mGameWindowEventListener);

	//OIS
	mInputManager->destroyInputObject(mMouse); 
	mMouse = 0;

	mInputManager->destroyInputObject(mKeyboard); 
	mKeyboard = 0;

	OIS::InputManager::destroyInputSystem(mInputManager);
	mInputManager = 0;

	//���������
	delete mGameKeyListener;
	mGameKeyListener = 0;
	delete mGameMouseListener; 
	mGameMouseListener = 0;
	delete mGameFrameListener;
	mGameFrameListener = 0;
	delete mGameWindowEventListener;
	mGameWindowEventListener = 0;

	//���
	delete mRoot;
	mRoot = 0;
}

bool MainClass::run()
{
	if(initConfig() == false) return false;
	createWindow();
	loadResources();
	createScene();
	initMyGUI();
	initPhysics();
	initOIS();
	mMainManager = new MainManager(mMyGUI, mSceneManager, mCamera, mDynamicsWorld);
	initListeners();

	//----------------------------------------------------
	// 8 ����� �������
	//----------------------------------------------------
	mRoot->startRendering(); // ���� ��������� ����� ������������� ����� false ( ��� � ���������� ��� ������� ESCAPE )

	return true;
}

bool MainClass::initConfig()
{
	//-----------------------------------------------------
	// 2 ��������� ���������� � �������� ����
	//-----------------------------------------------------
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		delete mRoot;
		return false;
	}

	return true;
}

void MainClass::createWindow()
{
	mRenderWindow = mRoot->initialise(true, "JustGame");

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
}

void MainClass::loadResources()
{
	//-----------------------------------------------------
	// 3 �������� �������� �� �������
	//-----------------------------------------------------
	Ogre::ConfigFile xConfigFile;
	xConfigFile.load(mResourcesCfg);

	// �������� �� ���� ������ � �����
	Ogre::ConfigFile::SectionIterator seci = xConfigFile.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end();   i++)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	// ������ ��� �������
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void MainClass::createScene()
{
	//-----------------------------------------------------
	// 4 �������� ��������� ����
	//
	//		ST_GENERIC = octree
	//		ST_EXTERIOR_CLOSE = simple terrain
	//		ST_EXTERIOR_FAR = nature terrain (depreciated)
	//		ST_EXTERIOR_REAL_FAR = paging landscape
	//		ST_INTERIOR = Quake3 BSP
	//----------------------------------------------------- 
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC); 

	//----------------------------------------------------- 
	// 5 �������� ������
	//----------------------------------------------------- 
	mCamera = mSceneManager->createCamera("MainCamera"); 
	mCamera->setPosition(Ogre::Vector3(0,0,100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);

	//----------------------------------------------------- 
	// 6 �������� ��������
	//----------------------------------------------------- 
	Ogre::Viewport* xViewport = mRenderWindow->addViewport(mCamera);
	xViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	mCamera->setAspectRatio(Ogre::Real(xViewport->getActualWidth()) / Ogre::Real(xViewport->getActualHeight()));

	// Set ambient light
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}

void MainClass::initMyGUI()
{
	mPlatform = new MyGUI::OgrePlatform();
	mPlatform->initialise(mRenderWindow, mSceneManager); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
	mMyGUI = new MyGUI::Gui();
	mMyGUI->initialise();
}

void MainClass::initPhysics()
{
	// Start Bullet
	mDynamicsWorld = new OgreBulletDynamics::DynamicsWorld(mSceneManager,
		Ogre::AxisAlignedBox(Ogre::Vector3(-10000, -10000, -10000),Ogre::Vector3(10000,  10000,  10000)), Ogre::Vector3(0,0,0));
	// add Debug info display tool
	mDebugDrawer = new OgreBulletCollisions::DebugDrawer();
	mDebugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
	mDynamicsWorld->setDebugDrawer(mDebugDrawer);
	mDynamicsWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
	Ogre::SceneNode *xNode = mSceneManager->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
	xNode->attachObject(static_cast <Ogre::SimpleRenderable*> (mDebugDrawer));
}

void MainClass::initOIS()
{
	//---------------------------------------------------- 
	// 7 ���������� OIS ��� ��������� ������� 
	//----------------------------------------------------
	OIS::ParamList xParamList;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	//������� OIS ����� ���� ���� �����������
	mRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	xParamList.insert(std::make_pair(Ogre::String("WINDOW"), windowHndStr.str()));

	//��������� ���������, ����� � ���� ��� �������
	mInputManager = OIS::InputManager::createInputSystem(xParamList);
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	//������� OIS � �������� ������ ����
	unsigned int width, height, depth;
	int top, left;
	mRenderWindow->getMetrics(width, height, depth, left, top);
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void MainClass::initListeners()
{
	//������ ����������
	mGameWindowEventListener = new GameWindowEventListener(mMainManager, mMouse);
	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, mGameWindowEventListener);

	mGameFrameListener = new GameFrameListener(mMainManager, mKeyboard, mMouse);
	mRoot->addFrameListener(mGameFrameListener); 

	mGameMouseListener = new GameMouseListener(mMainManager);
	mMouse->setEventCallback(mGameMouseListener);

	mGameKeyListener = new GameKeyListener(mMainManager);
	mKeyboard->setEventCallback(mGameKeyListener);
}