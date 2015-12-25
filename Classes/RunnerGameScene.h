/*
 * RunnerGameScene.h
 *
 *  Created on: 2014. 9. 18.
 *      Author: pc
 */

#ifndef RUNNERGAMESCENE_H_
#define RUNNERGAMESCENE_H_

#include "cocos2d.h"
#include "RunnerGameScene.h"
#include "manager/AudioManager.h"
using namespace cocos2d;


class RunnerGameScene :public CCLayer{
public:
	RunnerGameScene();
	virtual ~RunnerGameScene();

	virtual bool init();
			static CCScene* scene();
			int _state; //0-menu 1-map 2-store 3-option
			int _scrollSpeed;
			int _slowCount;
			int _jumpCount;
			int _deadCount;
			int _standTimeValue;
			CCSprite* _scrollBack1;
			CCSprite* _scrollBack2;
			CCSprite* _track;
			CCSprite* _runner;

			CCSprite* _result;

			CCSprite* _hurdle1;
			CCSprite* _hurdle2;
			CCSprite* _hurdle3;
			CCSprite* _hurdle4;
			CCSprite* _hurdle5;

			CCLabelTTF* _standTime;

			CCMenuItemImage* _runBtn;
			CCMenuItemImage* _jumpBtn;
			CCMenu* _runControlMenu;
			CCMenu* _jumpControlMenu;
			CCAnimation *_runneranimation;
			CCAnimate *_runneranimate;
			CREATE_FUNC(RunnerGameScene);
			void standTime(float f);
			void scrollUpdate(float f);
			void runnerControlCallBack(CCObject* pSender);
			virtual void keyBackClicked();	//adroid backkey
};


#endif /* RUNNERGAMESCENE_H_ */
