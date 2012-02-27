#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include <MainSystem.h>
#include <SoundSystem.h>
#include <SoundListener.h>
#include <SoundSource.h>
#include "MyGameObject.h"

class Player: public MyGameObject
{
private:
	Ogre::ManualObject *mManualObject;
	JGC::SoundListener *mSoundListener;
	JGC::SoundSource *mSoundSource;

public:
	Player(IGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectCollideWith, Ogre::Vector2 xPos);
	~Player();

	virtual void update(const float& xTimeSinceLastFrame);

private:
	void rotatePlayer(Ogre::Real xTimeSinceLastFrame);
	void movePlayer(Ogre::Real xTimeSinceLastFrame);
	void playerShoot(Ogre::Real xTimeSinceLastFrame);
};

#endif