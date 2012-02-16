#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "ICore.h"
#include "GameObject.h"

class Player: public GameObject
{
private:
	Ogre::ManualObject *mManualObject;

public:
	Player(ICore *xCore, IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Player();

	virtual void update(const Ogre::FrameEvent& evt);

private:
	void rotatePlayer(Ogre::Real xTimeSinceLastFrame);
	void movePlayer(Ogre::Real xTimeSinceLastFrame);
	void playerShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif