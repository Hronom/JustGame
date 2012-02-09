#include "GraphicSystem.h"

GraphicSystem::GraphicSystem(iMainListener *xMainListener) 
{ 
	mMainListener = xMainListener;
} 

GraphicSystem::~GraphicSystem()
{
	//----------------------------------------------------
	// 9 удаление
	//----------------------------------------------------
	mMyGUI->shutdown();
	delete mMyGUI;
	mMyGUI = 0;   

	mOgrePlatform->shutdown();
	delete mOgrePlatform;
	mOgrePlatform = 0;

	Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, this);

	//Огр
	delete mRoot;
	mRoot = 0;
}

bool GraphicSystem::init()
{
	mOgreCfg = "ogre.cfg";
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";
	mLogFileName = "ogre.log";

	//-----------------------------------------------------
	// 1 Создание рута
	//-----------------------------------------------------
	mRoot = new Ogre::Root();

	//-----------------------------------------------------
	// 2 Настройка приложение и создание окна
	//-----------------------------------------------------
	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		delete mRoot;
		return false;
	}

	mRenderWindow = mRoot->initialise(true, "JustGame");

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	//-----------------------------------------------------
	// 3 Загрузка ресурсов из конфига
	//-----------------------------------------------------
	Ogre::ConfigFile xConfigFile;
	xConfigFile.load(mResourcesCfg);

	// Проходим по всем секция в файле
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

	// Грузим все ресурсы
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//-----------------------------------------------------
	// 4 Создание менеджера сцен
	//
	//		ST_GENERIC = octree
	//		ST_EXTERIOR_CLOSE = simple terrain
	//		ST_EXTERIOR_FAR = nature terrain (depreciated)
	//		ST_EXTERIOR_REAL_FAR = paging landscape
	//		ST_INTERIOR = Quake3 BSP
	//----------------------------------------------------- 
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC); 

	//----------------------------------------------------- 
	// 5 Создание камеры
	//----------------------------------------------------- 
	mCamera = mSceneManager->createCamera("MainCamera"); 
	mCamera->setPosition(Ogre::Vector3(0,0,100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);

	//----------------------------------------------------- 
	// 6 Создание вьюпорта
	//----------------------------------------------------- 
	Ogre::Viewport* xViewport = mRenderWindow->addViewport(mCamera);
	xViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

	mCamera->setAspectRatio(Ogre::Real(xViewport->getActualWidth()) / Ogre::Real(xViewport->getActualHeight()));

	// Set ambient light
	mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	//----------------------------------------------------- 
	// 6 Инициализация MyGUI
	//----------------------------------------------------- 
	mOgrePlatform = new MyGUI::OgrePlatform();
	mOgrePlatform->initialise(mRenderWindow, mSceneManager); // mWindow is Ogre::RenderWindow*, mSceneManager is Ogre::SceneManager*
	mMyGUI = new MyGUI::Gui();
	mMyGUI->initialise();

	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);
	mRoot->addFrameListener(this);

	return true;
}

void GraphicSystem::start()
{
	//----------------------------------------------------
	// 8 старт рендера
	//----------------------------------------------------
	mRoot->startRendering(); // цикл кончается когда фреймлистенер вернёт false ( что и происходит при нажатии ESCAPE )
}

bool GraphicSystem::frameStarted(const  Ogre::FrameEvent& evt) 
{
	return mMainListener->needUpdate(evt);
}

bool GraphicSystem::frameEnded(const  Ogre::FrameEvent& evt) 
{ 
	return true; 
}

void GraphicSystem::windowResized(Ogre::RenderWindow* xRenderWindow)
{
	/*unsigned int xWidth, xHeight, xDepth;
	int xLeft, xTop;
	xRenderWindow->getMetrics(xWidth, xHeight, xDepth, xLeft, xTop);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = xWidth;
	ms.height = xHeight;*/
}

void GraphicSystem::windowClosed(Ogre::RenderWindow* xRenderWindow)
{
}

void GraphicSystem::injectMouseMoved( const OIS::MouseEvent &arg )
{
	//mMyGUI->injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
	MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
}

void GraphicSystem::injectMousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	//mMyGUI->injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void GraphicSystem::injectMouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	//mMyGUI->injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void GraphicSystem::injectKeyPressed( const OIS::KeyEvent &arg )
{
	//mMyGUI->injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
}

void GraphicSystem::injectKeyReleased( const OIS::KeyEvent &arg )
{
	//mMyGUI->injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
	MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
}

void GraphicSystem::loadLayout(Ogre::String xLayoutName)
{
	unloadLayout();
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstance().loadLayout(xLayoutName);
}

void GraphicSystem::unloadLayout()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstance().unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void GraphicSystem::addButtonDelegate(Ogre::String xButtonName, iState *xState)
{
	MyGUI::ButtonPtr xButton = mMyGUI->findWidget<MyGUI::Button>(xButtonName);
	xButton->eventMouseButtonClick += MyGUI::newDelegate(xState, &iState::buttonClick);
}

size_t GraphicSystem::getWinHandle()
{
	size_t xWinHandle = 0;
	mRenderWindow->getCustomAttribute("WINDOW", &xWinHandle);
	
	return xWinHandle;
}

unsigned int GraphicSystem::getWinWidth()
{
	return mRenderWindow->getWidth();
}

unsigned int GraphicSystem::getWinHeight()
{
	return mRenderWindow->getHeight();
}

Ogre::SceneManager* GraphicSystem::getSceneManager()
{
	return mSceneManager;
}

Ogre::Camera* GraphicSystem::getCamera()
{
	return mCamera;
}