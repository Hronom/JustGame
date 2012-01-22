#ifndef PLAYER_H
#define PLAYER_H

#include <Ogre.h>
#include "iGameObject.h"
#include "iControlled.h"

class Player: public iGameObject, public iControlled
{
private:
	Ogre::SceneNode *mPlayerNode;
	Ogre::Vector3 mMoveDirection;
	Ogre::Real mMoveSpeed;

	Ogre::Vector2 mLookAt;

public:
	Player(Ogre::SceneManager *xSceneManager, Ogre::Vector2 xPos);
	~Player();

	//-----------------------------------------------------
	// iGameObject
	//-----------------------------------------------------
	virtual void update(const Ogre::FrameEvent& evt);

	virtual std::string getName();
	virtual Ogre::Vector3 getCurrentPos();
	virtual void acceptCurrentPos();
	virtual void rejectCurrentPos();
	virtual Ogre::Quaternion getCurrentOrientation();

	//-----------------------------------------------------
	// iControlled
	//-----------------------------------------------------
	virtual void moveUp(bool doMove);
	virtual void moveDown(bool doMove);
	virtual void moveRight(bool doMove);
	virtual void moveLeft(bool doMove);

	virtual void rotateTo(Ogre::Vector2 xDot);

	virtual void shoot();
};

#endif