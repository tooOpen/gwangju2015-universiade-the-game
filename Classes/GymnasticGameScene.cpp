/*
 * GymnasticGameScene.cpp
 *
 *  Created on: 2014. 9. 22.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/gwangjugame/Classes/GymnasticGameScene.h"
USING_NS_CC;

CCScene* GymnasticGameScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GymnasticGameScene *layer = GymnasticGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GymnasticGameScene::init() {
	this->setKeypadEnabled(true);
	srand((unsigned)time(NULL));
	if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
		return false;
	}
	AudioManager::getAudioManager()->playSound(SOUND_GYMBACK);
	_standTimeValue = 0;
	_state = 0;
	_deadCount = 0;
	_gymback = CCSprite::create("gymnasticgameScene/images/gymback.jpg");
	_gymback->setPosition(ccp(640,360));
	this->addChild(_gymback, 0);

	_bar = CCSprite::create("gymnasticgameScene/images/bar.png");
	_bar->setPosition(ccp(640,100));
	this->addChild(_bar, 1);

	_player = CCSprite::create("gymnasticgameScene/images/gymner.png");
	_player->setAnchorPoint(ccp(0.5f,0.0f));
	_player->setPosition(ccp(640,120));

	//_player->setRotationX(30.0f);
	//_player->setRotationY(30.0f);
//	_player->setRotation(30.0f);
	CCLog("angle is %f",_player->getRotation());
	this->addChild(_player, 2);

	_rightBtn = CCMenuItemImage::create(
			"gymnasticgameScene/images/rightbtn.png",
			"gymnasticgameScene/images/rightbtnDown.png", this,
			menu_selector(GymnasticGameScene::gymnasticControlCallBack));
	_rightBtn->setTag(1);

	_leftBtn = CCMenuItemImage::create("gymnasticgameScene/images/leftbtn.png",
			"gymnasticgameScene/images/leftbtnDown.png", this,
			menu_selector(GymnasticGameScene::gymnasticControlCallBack));
	_leftBtn->setTag(2);

	_leftMenu = CCMenu::create( _leftBtn, NULL);
	_leftMenu->setPosition(ccp(170,200));
	this->addChild(_leftMenu, 3);

	_rightMenu = CCMenu::create(_rightBtn, NULL);
	_rightMenu->setPosition(ccp(1110,200));
	this->addChild(_rightMenu, 3);

	_standTime = CCLabelTTF::create("00:00", "fonts/darkforest.ttf", 100);
	_standTime->setColor(ccc3(0, 0, 0));
	_standTime->setAnchorPoint(ccp(0,0.5));
	_standTime->setPosition(ccp(20,600));
	this->addChild(_standTime, 4);
	_timeTex = CCLabelTTF::create("TIME", "fonts/darkforest.ttf", 100);
	_timeTex->setColor(ccc3(0, 0, 0));
	_timeTex->setAnchorPoint(ccp(0,0.5));
	_timeTex->setPosition(ccp(40,680));
	this->addChild(_timeTex, 4);
	this->schedule(schedule_selector(GymnasticGameScene::standTime),1.0f);
	this->schedule(schedule_selector(GymnasticGameScene::balanceinterruption),0.1f);
	return true;
}

void GymnasticGameScene::gymnasticControlCallBack(CCObject* pSender) {
	CCMenuItem *item = (CCMenuItem*) pSender;
		int tag = item->getTag();
		if(tag==1)
		{
			_player->setRotation(_player->getRotation()+5);
		}else
		{
			_player->setRotation(_player->getRotation()-5);
		}
}

void GymnasticGameScene::balanceinterruption(float f) {
	int randvalue = rand()%20+1;
	float plusminus = CCRANDOM_MINUS1_1();
	randvalue = (int)randvalue*plusminus;
	_player->setRotation(_player->getRotation()+randvalue);

	if(_player->getRotation()>45||_player->getRotation()<-45)
	{
		AudioManager::getAudioManager()->stopSound();
		AudioManager::getAudioManager()->playEffectAudio(SOUND_RESULT);
		this->unschedule(schedule_selector(GymnasticGameScene::balanceinterruption));
		_state = 3;
		_rightMenu->setEnabled(false);
		_leftMenu->setEnabled(false);
		CCString temp;
		if (_standTimeValue > 50)
			temp = "common/images/perfect.png";
		else if (_standTimeValue > 25)
			temp = "common/images/good.png";
		else
			temp = "common/images/bad.png";

		_result = CCSprite::create(temp.getCString());
				_result->setPosition(ccp(640,360));
				_result->setOpacity(0);
				this->addChild(_result, 6);
		CCActionInterval* myAction = CCFadeIn::create(1.5);
		_result->runAction(myAction);
	}
}


void GymnasticGameScene::standTime(float f) {

	if (_state == 3) {

		if (_deadCount > 3) {
			this->unschedule(schedule_selector(GymnasticGameScene::standTime));
			standtimeE = _standTimeValue;
			type = 3;
			CCScene* pScene = HallofFame::scene();
			CCDirector::sharedDirector()->replaceScene(
					CCTransitionPageTurn::create(0.5f, pScene, false));
		} else
			_deadCount++;
	} else {
		_standTimeValue++;
		int minute = _standTimeValue / 60;
		int seconds = _standTimeValue % 60;
		_standTime->setString(
				CCString::createWithFormat("%02d:%02d", minute, seconds)->getCString());
	}
}

void GymnasticGameScene::keyBackClicked()
{
	AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
	CCDirector::sharedDirector()->popScene();
}
