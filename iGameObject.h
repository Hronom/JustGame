#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <Ogre.h>

class iGameObject
{
public:
	iGameObject(){};
	virtual ~iGameObject(){};

	virtual void update(const Ogre::FrameEvent& evt) = 0;

	virtual std::string getName() = 0;
	virtual Ogre::Vector3 getCurrentPos() = 0;
	virtual void acceptCurrentPos() = 0;
	virtual void rejectCurrentPos() = 0;
	virtual Ogre::Quaternion getCurrentOrientation() = 0;
};

#endif