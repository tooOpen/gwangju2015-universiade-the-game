/*
 * MainMenuScene.cpp
 *
 *  Created on: 2014. 1. 27.
 *       Author: bsh
 */
#include "ReadyScene.h"
#include "manager/AudioManager.h"
#include "MainmenuScene.h"
CCScene* ReadyScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ReadyScene *layer = ReadyScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

/*
 * 씬 초기화 함수
 */
bool ReadyScene::init() {
	if (!CCLayer::init()) {
		return false;
	}
	AudioManager::getAudioManager()->playSound(SOUND_READYAUDIO);
	btnvisible = true;
	this->setKeypadEnabled(true);
	_title = CCSprite::create("readyScene/images/readyLogo.png");
	_title->setPosition(ccp(640, 500));
	this->addChild(_title, 1);

	_gametitle = CCSprite::create("readyScene/images/gametitle.png");
	_gametitle->setPosition(ccp(940, 330));
	this->addChild(_gametitle, 2);

	_background = CCSprite::create("readyScene/images/back.jpg");
	_background->setPosition(ccp(640, 360));
	_background->setZOrder(0);

	_backanimation = CCAnimation::create();
	_backanimation->setDelayPerUnit(0.5);

	_backanimation->addSpriteFrameWithFileName("readyScene/images/back.jpg");
	_backanimation->addSpriteFrameWithFileName("readyScene/images/back2.jpg");
	_backanimation->addSpriteFrameWithFileName("readyScene/images/back3.jpg");
	_backanimation->addSpriteFrameWithFileName("readyScene/images/back4.jpg");
	_backanimation->addSpriteFrameWithFileName("readyScene/images/back5.jpg");

	_backanimate = CCAnimate::create(_backanimation);

	CCAction* rep = CCRepeatForever::create(_backanimate);
	_background->runAction(rep);
	this->addChild(_background, 0);


	_menuGamePlay = CCMenuItemImage::create(
					"readyScene/images/start.png",
					"readyScene/images/start.png", this,
					menu_selector(ReadyScene::menuGamePlayCallBack));
	_startMenu =CCMenu::create(_menuGamePlay,NULL);
	_startMenu->setPosition(ccp(640,100));
	this->addChild(_startMenu,3);
	 this->schedule(schedule_selector(ReadyScene::btnTerm),0.5f);
	return true;

}
void ReadyScene::btnTerm(float f)
{
	btnvisible = !btnvisible;
	if(btnvisible)
	_menuGamePlay->setNormalImage(CCSprite::create("readyScene/images/nothing.png"));
	else
	_menuGamePlay->setNormalImage(CCSprite::create("readyScene/images/start.png"));

}
void ReadyScene::keyBackClicked() {
	if (JniHelper::getStaticMethodInfo(t, "com/gwangu/game/gwangjugame",
			"callDialog", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

}

#ifdef __cplusplus
extern "C" {
#endif
void Java_com_gwangu_game_gwangjugame_exitGame(JNIEnv* env, jobject thisObj) {
	CCDirector::sharedDirector()->end();
}

#ifdef __cplusplus
}
#endif

/*
 * 게임 시작 메뉴 선택시 호출 되는 콜백 함수.
 */
void ReadyScene::menuGamePlayCallBack(CCObject* pSender) {
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	AudioManager::getAudioManager()->stopSound();
	this->unschedule(schedule_selector(ReadyScene::btnTerm));
	CCScene* pScene = MainmenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(.5f,pScene));
}

ReadyScene::ReadyScene() {
	// TODO Auto-generated constructor stub

}
/*
 * 소멸자 호출 시 java의 disConnect함수를 호출하여 기기와 연결 끊기
 */
ReadyScene::~ReadyScene() {

}

