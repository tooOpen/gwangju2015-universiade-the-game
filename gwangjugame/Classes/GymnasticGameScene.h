/*
 * GymnasticGameScene.h
 *
 *  Created on: 2014. 9. 22.
 *      Author: pc
 */

#ifndef GYMNASTICGAMESCENE_H_
#define GYMNASTICGAMESCENE_H_

#include "cocos2d.h"
#include "manager/AudioManager.h"
#include "HallofFame.h"
#include <time.h>
using namespace cocos2d;
class GymnasticGameScene : public cocos2d::CCLayerColor
{
private:
	int _standTimeValue;
	int _state;
	int _deadCount;
	CCSprite* _gymback;
	CCSprite* _bar;
	CCSprite* _player;
	CCSprite* _result;
	CCLabelTTF* _standTime;
	CCLabelTTF* _timeTex;
	CCMenuItemImage* _rightBtn;
	CCMenuItemImage* _leftBtn;
	CCMenu* _rightMenu;
	CCMenu* _leftMenu;
public:
    virtual bool init();
    void gymnasticControlCallBack(CCObject* pSender);
    static CCScene* scene();
    void standTime(float f);
    void keyBackClicked();
    void balanceinterruption(float f);
    CREATE_FUNC(GymnasticGameScene);
};

#endif /* GYMNASTICGAMESCENE_H_ */
