#ifndef BULLET_H
#define BULLET_H

#include <Ogre.h>
#include <ICore.h>
#include "MyGameObject.h"

class Bullet: public MyGameObject
{
private:
	Ogre::ManualObject *mManualObject;

	Ogre::Real mLiveTime;
	Ogre::Real mTimeBeforeDelete;

public:
	Bullet(ICore *xCore, IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);
	~Bullet();

	virtual void update(const Ogre::FrameEvent& evt);
	virtual int getDamage();
};

#endif

