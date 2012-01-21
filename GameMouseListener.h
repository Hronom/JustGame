#ifndef GAMEMOUSELISTENER_H
#define GAMEMOUSELISTENER_H

#include <OIS/OIS.h>
#include "iMainListener.h"

class GameMouseListener : public OIS::MouseListener
{
private:
	iMainListener *mListener;

public: 
	GameMouseListener(iMainListener *xListener);
	bool mouseMoved(const OIS::MouseEvent& e);
	bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
};

#endif
