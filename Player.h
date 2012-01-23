#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "iCore.h"
#include "GameObject.h"

class Player: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;
	Ogre::Entity *mObjectEntity;

public:
	Player(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos);
	~Player();
};

#endif