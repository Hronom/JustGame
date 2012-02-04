#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#define BIT(x) (1<<(x))
enum CollisionGroups 
{
	EMPTY_GROUP = 0,
    PLAYER_GROUP = BIT(0), //<Collide with PLAYER
    ENEMY_GROUP = BIT(1), //<Collide with ENEMY
	BULLET_GROUP = BIT(2) //<Collide with BULLET
};

#include <Ogre.h>

class iCore;
class iGameObjectsListener;
class GameObject
{
protected:
	iCore *mCore;
	iGameObjectsListener *mGameObjectsListener;

	Ogre::String mObjectName;
	short mObjectType;
	int mHealthCount;
	int mDamage;
	Ogre::Real mMoveSpeed;

	Ogre::SceneNode *mObjectNode;
	float mObjectRadius;
	Ogre::Vector2 mDestinationDot;
	Ogre::Vector3 mMoveDirection;
	
	bool mCanDoShot;
	Ogre::Real mShootDelay;
	Ogre::Real mTimeAfterLastShoot;

	bool mNeedDelete;

public:
	GameObject(iCore *xCore, iGameObjectsListener *xGameObjectsListener, Ogre::String xObjectName, short xObjectType);
	virtual ~GameObject();

	virtual void update(const Ogre::FrameEvent& evt);

	virtual Ogre::String getObjectName();
	virtual int getCurrentHealth();
	virtual int getDamage();
	virtual void doDamage(int xDamage);
	
	virtual Ogre::Vector2 getCurrentPos();
	virtual bool isNeedDelete();

	virtual void moveUp(bool doMove);
	virtual void moveDown(bool doMove);
	virtual void moveRight(bool doMove);
	virtual void moveLeft(bool doMove);
	virtual void rotateTo(Ogre::Vector2 xDestinationDot);
	virtual void shoot(bool doShoot);
};

#endif