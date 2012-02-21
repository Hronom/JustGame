#ifndef PLAYGAMESTATE_H
#define PLAYGAMESTATE_H

#include <Ogre.h>
#include <MyGUI.h>
#include <OIS\OIS.h>

#include <MainSystem.h>
#include <IState.h>
#include "IGameObjectsListener.h"
#include "MyGameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class PlayGameState: public JGC::IState, public IGameObjectsListener
{
private:
	bool isDebug;

	MyGameObject *mPlayer;

	Ogre::ManualObject *mGridManualObject;
	Ogre::SceneNode *mGridSceneNode;

	int mEnemyCount;
	int mBulletsCount;

	std::list<MyGameObject*> mUnits;
	std::list<MyGameObject*> mBullets;

	std::list<MyGameObject*> mForDelete;

public:
	PlayGameState();
	~PlayGameState();

	virtual void prepareState();
	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);

	void setPlayer(Ogre::Vector2 xPos);
	void addEnemy(Ogre::Vector2 xPos);
	virtual void addBullet(short xObjectString, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);

};

#endif

