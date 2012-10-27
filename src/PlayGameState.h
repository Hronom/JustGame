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
	MyGUI::VectorWidgetPtr mCurrentLayoutWidgets;
	Ogre::RaySceneQuery* mRaySceneQuery;

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

	virtual void injectUpdate(const float& xTimeSinceLastFrame);
	virtual	void injectMouseMoved(const OIS::MouseEvent& e);
	virtual void injectMousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void injectMouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void injectKeyPressed(const OIS::KeyEvent& e);
	virtual void injectKeyReleased(const OIS::KeyEvent& e);

	void setPlayer(Ogre::Vector2 xPos);
	void addEnemy(Ogre::Vector2 xPos);
	virtual void addBullet(short xObjectString, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);

};

#endif

