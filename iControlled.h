#ifndef ICONTROLLED_H
#define ICONTROLLED_H

#include <Ogre.h>

class iControlled
{
public:
	iControlled(){};
	virtual ~iControlled(){};

	virtual void moveUp(bool doMove) = 0;
	virtual void moveDown(bool doMove) = 0;
	virtual void moveRight(bool doMove) = 0;
	virtual void moveLeft(bool doMove) = 0;

	virtual void rotateTo(Ogre::Vector2 xDot) = 0;

	virtual void shoot() = 0;
};

#endif