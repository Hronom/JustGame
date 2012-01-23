#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Ogre.h>

class iCore;
class iGameObjectsListener;
class GameObject
{
protected:
	iCore *mCore;
	iGameObjectsListener *mGameObjectsListener;

	Ogre::String mObjectName;
	int mHealthCount;
	int mDamage;
	Ogre::Real mMoveSpeed;

	Ogre::SceneNode *mObjectNode;
	Ogre::Vector2 mDestinationDot;
	Ogre::Vector3 mMoveDirection;
	
	bool isCanShoot;
	Ogre::Real mShootDelay;
	Ogre::Real mTimeAfterLastShoot;

public:
	GameObject(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName);
	virtual ~GameObject();

	virtual void update(const Ogre::FrameEvent& evt);

	virtual Ogre::String getObjectName();
	virtual int getCurrentHealth();
	virtual int getDamage();
	virtual void doDamage(int xDamage);
	virtual Ogre::Vector2 getCurrentPos();

	virtual void moveUp(bool doMove);
	virtual void moveDown(bool doMove);
	virtual void moveRight(bool doMove);
	virtual void moveLeft(bool doMove);
	virtual void rotateTo(Ogre::Vector2 xDestinationDot);
	virtual void shoot(bool doShoot);
};

#endif