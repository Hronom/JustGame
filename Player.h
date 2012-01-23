#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "iCore.h"
#include "GameObject.h"

class Player: public GameObject
{
public:
	Player(iCore *xCore, Ogre::String xObjectName, Ogre::Vector2 xPos);
	~Player();
};

#endif