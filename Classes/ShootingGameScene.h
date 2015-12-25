/*
 * ShootingGameScene.h
 *
 *  Created on: 2014. 9. 20.
 *      Author: pc
 */

#ifndef SHOOTINGGAMESCENE_H_
#define SHOOTINGGAMESCENE_H_

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include "math.h"
#include "manager/AudioManager.h"
#include "HallofFame.h"
using namespace cocos2d;


class ShootingGameScene : public cocos2d::CCLayerColor
{
private:
	 JniMethodInfo t;
	 int term;
	 int _state;
	 int leftshot;
	 int _deadCount;
	 int _totallScore;
	 int _readyCount;
	 CCSprite* _target;
	 CCSprite* _bulletmark;
	 CCSprite* _aim;
	 CCSprite* _scoretex;
	 CCSprite* _result;
	 CCMenuItemImage* _shootBtn;
	 CCMenu* _shootMenu;
	 CCLabelTTF* _score;
	 CCLabelTTF* _leftShot;
	 CCLabelTTF* _shotTex;
public:

	 virtual bool init();
	 void shootClick(CCObject* pSender);
    static CCScene* scene();
    CREATE_FUNC(ShootingGameScene);
    ~ShootingGameScene();
    virtual void onEnter();
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    CCSize winsize;
    void keyBackClicked();
    void balanceinterruption(float f);
};

#endif /* SHOOTINGGAMESCENE_H_ */
