#pragma once

#include <OIS/OIS.h>
#include "MainListener.h"

class GameMouseListener : public OIS::MouseListener
{
private:
	MainListener *mListener;

public: 
	GameMouseListener(MainListener *xListener);
	bool mouseMoved(const OIS::MouseEvent& e);
	bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
};
