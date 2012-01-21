#ifndef GAMEKEYLISTENER_H
#define GAMEKEYLISTENER_H

#include <OIS/OIS.h>
#include "iMainListener.h"

class GameKeyListener : public OIS::KeyListener 
{ 
private:
	iMainListener *mListener;

public: 
	GameKeyListener(iMainListener *xListener);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);
};

#endif
