/*
 * MainmenuScene.h
 *
 *  Created on: 2014. 9. 16.
 *      Author: pc
 */

#ifndef MAINMENUSCENE_H_
#define MAINMENUSCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "manager/AudioManager.h"
#include "RunnerGameScene.h"
#include "ShootingGameScene.h"
#include "GymnasticGameScene.h"
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;


class MainmenuScene :public CCLayer{
public:
	MainmenuScene();
	virtual ~MainmenuScene();

	virtual bool init();
			static CCScene* scene();
			int _state; //0-menu 1-map 2-store 3-option
			int _volume;

			JniMethodInfo t;

			CREATE_FUNC(MainmenuScene);
			CCSprite* _optionBack;
			CCSprite* _spymap;
			CCSprite* _menuBack;
			CCSprite* _helpScene;

			CCMenuItemImage* _runningItem;
			CCMenuItemImage* _gameoptionItem;
			CCMenuItemImage* _shootingItem;
			CCMenuItemImage* _gymnasticItem;
			CCMenuItemImage* _helpItem;
			CCMenu* _gameMenu;



			CCLabelTTF* _volumeSet;

			extension::CCControlSlider* _volumeSlider;
			virtual void keyBackClicked();	//adroid backkey
			void gameMenuClick(CCObject* pSender);
			void sliderValuechange(CCObject* sender,extension::CCControlEvent controlEvent);
};


#endif /* MAINMENUSCENE_H_ */
