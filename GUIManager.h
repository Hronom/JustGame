#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <MyGUI.h>
#include <OIS\OIS.h>
#include <string>

#include "iState.h"

class GUIManager
{
private:
	MyGUI::Gui *mMyGUI;
public:
	GUIManager(MyGUI::Gui *xMyGUI);
	~GUIManager();

	void GUIManager::mouseMoved( const OIS::MouseEvent &arg );
	void GUIManager::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	void GUIManager::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	void GUIManager::keyPressed( const OIS::KeyEvent &arg );
	void GUIManager::keyReleased( const OIS::KeyEvent &arg );

	void loadLayout(std::string xLayoutName);
	void addButtonDelegate(std::string xButtonName, iState *xState);
};

#endif

