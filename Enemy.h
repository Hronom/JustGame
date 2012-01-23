#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>
#include "iCore.h"
#include "GameObject.h"

class Enemy: public GameObject
{
public:
	Enemy(iCore *xCore, Ogre::String xObjectName, Ogre::Vector2 xPos);
	~Enemy();
};

#endif
