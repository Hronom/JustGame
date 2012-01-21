#ifndef STATESMANAGER_H
#define STATESMANAGER_H

#include "iState.h"
#include "GUIManager.h"
#include "iCore.h"

class StateManager
{
private:
	iState *mCurrentState;

public:
	StateManager(iCore *xCore, GUIManager *xGUIManager);
	~StateManager();

};

#endif

