#ifndef BULLET_H
#define BULLET_H

#include "iGameObject.h"
#include "iControlled.h"

#include <Ogre.h>
#include <string>
#include "iCore.h"

class Bullet: public iGameObject, public iControlled
{
private:
	iCore *mCore;
	Ogre::SceneNode *mObjectNode;
	Ogre::Vector3 mMoveDirection;
	Ogre::Real mMoveSpeed;

	Ogre::Vector2 mLookAt;

public:
	Bullet(iCore *xCore, std::string xBulletName, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);
	~Bullet();

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

	virtual void shoot(bool doShoot);
};

#endif

