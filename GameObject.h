#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Ogre.h>

class iCore;
class GameObject
{
protected:
	iCore *mCore;
	Ogre::SceneNode *mObjectNode;
	Ogre::Vector3 mMoveDirection;
	Ogre::Real mMoveSpeed;
	Ogre::Vector2 mLookAt;

	Ogre::String mObjectName;
	int mDamage;
	int mHealthCount;
	bool isCanShoot;
	Ogre::Real mShootDelay;
	Ogre::Real mTimeAfterLastShoot;

public:
	GameObject(iCore *xCore, Ogre::String xObjectName);
	virtual ~GameObject();

	virtual void update(const Ogre::FrameEvent& evt);

	virtual Ogre::String getObjectName();
	virtual Ogre::Vector2 getCurrentPos();

	virtual int getDamage();
	virtual void doDamage(int xDamage);
	virtual int getCurrentHealth();
	virtual void moveUp(bool doMove);
	virtual void moveDown(bool doMove);
	virtual void moveRight(bool doMove);
	virtual void moveLeft(bool doMove);

	virtual void rotateTo(Ogre::Vector2 xDot);

	virtual void shoot(bool doShoot);
};

#endif