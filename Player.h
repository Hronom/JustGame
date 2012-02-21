#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include <MainSystem.h>
#include "MyGameObject.h"

class Player: public MyGameObject
{
private:
	Ogre::ManualObject *mManualObject;

public:
	Player(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Player();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotatePlayer(Ogre::Real xTimeSinceLastFrame);
	void movePlayer(Ogre::Real xTimeSinceLastFrame);
	void playerShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif