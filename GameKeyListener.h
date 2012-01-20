#pragma once

#include <OIS/OIS.h>
#include "MainListener.h"

class GameKeyListener : public OIS::KeyListener 
{ 
private:
	MainListener *mListener;

public: 
	GameKeyListener(MainListener *xListener);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);
};
