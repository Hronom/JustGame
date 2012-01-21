#ifndef ICORE_H
#define ICORE_H

#include "iState.h"
#include <Ogre.h>

class iCore
{
public:
	iCore() {};
	virtual ~iCore() {};

	virtual void needSwitchToStateId(int xStateId) = 0;
	virtual void needShutdown() = 0;

	virtual void loadGUILayout(std::string xLayoutName) = 0;
	virtual void unloadGUILayout() = 0;
	virtual void addButtonDelegate(std::string xButtonName, iState *xState) = 0;

	virtual void addPlayer(Ogre::Vector3 xPos) = 0;
	virtual void addEnemy(Ogre::Vector3 xPos) = 0;

	virtual void movePlayerUp() = 0;
	virtual void movePlayerDown() = 0;
	virtual void movePlayerLeft() = 0;
	virtual void movePlayerRight() = 0;
	virtual void playerShoot() = 0;
};

#endif
