#include "GUIManager.h"

GUIManager::GUIManager(MyGUI::Gui *xMyGUI)
{
	mMyGUI = xMyGUI;
}

GUIManager::~GUIManager()
{
	unloadLayout();
}

void GUIManager::mouseMoved( const OIS::MouseEvent &arg )
{
	mMyGUI->injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
	//MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
}

void GUIManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mMyGUI->injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	//MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void GUIManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mMyGUI->injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
	//MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
}

void GUIManager::keyPressed( const OIS::KeyEvent &arg )
{
	mMyGUI->injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
	//MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
}

void GUIManager::keyReleased( const OIS::KeyEvent &arg )
{
	mMyGUI->injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
	//MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
}

void GUIManager::loadLayout(std::string xLayoutName)
{
	unloadLayout();
	mCurrentLayoutWidgets = MyGUI::LayoutManager::getInstance().loadLayout(xLayoutName);
}

void GUIManager::unloadLayout()
{
	if(mCurrentLayoutWidgets.size() != 0)
	{
		MyGUI::LayoutManager::getInstance().unloadLayout(mCurrentLayoutWidgets);
		mCurrentLayoutWidgets.clear();
	}
}

void GUIManager::addButtonDelegate(std::string xButtonName, iState *xState)
{
	MyGUI::ButtonPtr xButton = mMyGUI->findWidget<MyGUI::Button>(xButtonName);
	xButton->eventMouseButtonClick += MyGUI::newDelegate(xState, &iState::buttonClick);
}
