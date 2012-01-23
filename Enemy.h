#ifndef ENEMY_H
#define ENEMY_H

#include <Ogre.h>
#include "iCore.h"
#include "GameObject.h"

class Enemy: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;
	Ogre::Entity *mObjectEntity;
	Ogre::Real mTimeBeforeDelete;

public:
	Enemy(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, Ogre::Vector2 xPos);
	~Enemy();

	virtual void update(const Ogre::FrameEvent& evt);
};

#endif
