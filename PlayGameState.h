#ifndef PLAYGAMESTATE_H
#define PLAYGAMESTATE_H

#include <Ogre.h>
#include <MyGUI.h>
#include <OIS\OIS.h>

#include "iCore.h"
#include "iState.h"
#include "iGameObjectsListener.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class PlayGameState: public iState, public iGameObjectsListener
{
private:
	bool isDebug;

	iCore *mCore;

	GameObject *mPlayer;

	Ogre::ManualObject *mGridManualObject;
	Ogre::SceneNode *mGridSceneNode;

	int mEnemyCount;
	int mBulletsCount;

	std::list<GameObject*> mUnits;
	std::list<GameObject*> mBullets;

	std::list<GameObject*> mForDelete;

public:
	PlayGameState(iCore *xCore);
	~PlayGameState();

	virtual void enter();
	virtual void exit();

	virtual void needUpdate(const Ogre::FrameEvent& evt);
	virtual	void mouseMoved(const OIS::MouseEvent& e);
	virtual void mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual void mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id);
	virtual	void keyPressed(const OIS::KeyEvent& e);
	virtual void keyReleased(const OIS::KeyEvent& e);
	virtual void buttonClick(MyGUI::WidgetPtr xSender);

	void setPlayer(Ogre::Vector2 xPos);
	void addEnemy(Ogre::Vector2 xPos);
	virtual void addBullet(short xObjectString, Ogre::Vector2 xPos, Ogre::Vector2 xDestination);

};

#endif

