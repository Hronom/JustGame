#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <OIS/OIS.h>
#include "iSystemsListener.h"

class InputSystem : public OIS::MouseListener, public OIS::KeyListener
{ 
private:
	iSystemsListener *mMainListener;

	OIS::InputManager *mInputManager;
	OIS::Keyboard *mKeyboard;
	OIS::Mouse *mMouse;

public: 
	InputSystem(iSystemsListener *xMainListener);
	~InputSystem();

	void init(unsigned int xWinHandle, unsigned int xWinWidth, unsigned int xWinHeight);
	void needUpdate();
	void injectWindowResized(unsigned int xNewWidth, unsigned int xNewHeight);

private:
	bool mouseMoved(const OIS::MouseEvent& e);
	bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);
};

#endif
