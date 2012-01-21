#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "iGameObject.h"

class Player: public iGameObject
{
private:
	Ogre::SceneNode *mPlayerNode;

	Ogre::Vector3 mDirection;

public:
	Player(Ogre::SceneManager *xSceneManager, Ogre::Vector3 xPos);
	~Player();

	virtual void update(const Ogre::FrameEvent& evt);

	virtual Ogre::Vector3 getCurrentPos();
	virtual void acceptCurrentPos();
	virtual void rejectCurrentPos();
	virtual Ogre::Quaternion getCurrentOrientation();

	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();
	void playerShoot();
};

#endif