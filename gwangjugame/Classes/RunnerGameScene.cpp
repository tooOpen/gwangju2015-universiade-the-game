/*
 * RunnerGameScene.cpp
 *
 *  Created on: 2014. 9. 18.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/gwangjugame/Classes/RunnerGameScene.h"
#include "HallofFame.h"


CCScene* RunnerGameScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	RunnerGameScene *layer = RunnerGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool RunnerGameScene::init() {
	this->setKeypadEnabled(true);
	AudioManager::getAudioManager()->playSound(SOUND_RUNBACK);
	_scrollSpeed = 3;
	_state = 1;
	_slowCount = 0;
	_jumpCount = 0;
	_standTimeValue = 0;
	_deadCount = 0;
	_standTime = CCLabelTTF::create("TIME:00:00", "fonts/darkforest.ttf", 100);
	_standTime->setColor(ccc3(0, 0, 0));
	_standTime->setAnchorPoint(ccp(0,0.5));
	_standTime->setPosition(ccp(50,650));
	this->addChild(_standTime, 4);

	_runBtn = CCMenuItemImage::create("runnergameScene/images/runBtnUp.png",
			"runnergameScene/images/runBtnDown.png", this,
			menu_selector(RunnerGameScene::runnerControlCallBack));
	_runBtn->setTag(1);
	_runBtn->setPosition(ccp(30,0));
	_runBtn->setOpacity(200);

	_jumpBtn = CCMenuItemImage::create("runnergameScene/images/jumpBtnUp.png",
			"runnergameScene/images/jumpBtnDown.png", this,
			menu_selector(RunnerGameScene::runnerControlCallBack));
	_jumpBtn->setTag(2);
	_jumpBtn->setPosition(ccp(1050,0));
	_jumpBtn->setOpacity(200);

	_runControlMenu = CCMenu::create(_runBtn, NULL);
	_runControlMenu->setPosition(ccp(100,150));

	this->addChild(_runControlMenu, 4);

	_jumpControlMenu = CCMenu::create(_jumpBtn, NULL);
	_jumpControlMenu->setPosition(ccp(100,150));

	this->addChild(_jumpControlMenu, 4);

	_scrollBack1 = CCSprite::create("runnergameScene/images/runningBack.jpg");
	_scrollBack1->setAnchorPoint(ccp(1.0,0.5));
	_scrollBack1->setPosition(ccp(2560,360));
	this->addChild(_scrollBack1, 0);

	_scrollBack2 = CCSprite::create("runnergameScene/images/runningBack.jpg");
	_scrollBack2->setAnchorPoint(ccp(1.0,0.5));
	_scrollBack2->setPosition(ccp(5100,360));
	this->addChild(_scrollBack2, 0);

	int gap = 1280;
	_hurdle1 = CCSprite::create("runnergameScene/images/hurdle.png");
	gap += CCRANDOM_0_1() * 1000 + 700;
	_hurdle1->setPosition(ccp(gap,120));
	this->addChild(_hurdle1, 3);

	_hurdle2 = CCSprite::create("runnergameScene/images/hurdle.png");
	gap += CCRANDOM_0_1() * 1000 + 700;
	_hurdle2->setPosition(ccp(gap,120));
	this->addChild(_hurdle2, 3);

	_hurdle3 = CCSprite::create("runnergameScene/images/hurdle.png");
	gap += CCRANDOM_0_1() * 1000 + 700;
	_hurdle3->setPosition(ccp(gap,120));
	this->addChild(_hurdle3, 3);

	_hurdle4 = CCSprite::create("runnergameScene/images/hurdle.png");
	gap += CCRANDOM_0_1() * 1000 + 700;
	_hurdle4->setPosition(ccp(gap,120));
	this->addChild(_hurdle4, 3);

	_hurdle5 = CCSprite::create("runnergameScene/images/hurdle.png");
	gap += CCRANDOM_0_1() * 1000 + 700;
	_hurdle5->setPosition(ccp(gap,120));
	this->addChild(_hurdle5, 3);

	_track = CCSprite::create("runnergameScene/images/track.png");
	_track->setPosition(ccp(640,360));
	this->addChild(_track, 2);

	_runner = CCSprite::create("runnergameScene/images/runner1.png");
	_runner->setPosition(ccp(640,220));

	_runneranimation = CCAnimation::create();
	_runneranimation->setDelayPerUnit(0.2);

	_runneranimation->addSpriteFrameWithFileName(
			"runnergameScene/images/runner1.png");
	_runneranimation->addSpriteFrameWithFileName(
			"runnergameScene/images/runner2.png");
	_runneranimation->addSpriteFrameWithFileName(
			"runnergameScene/images/runner3.png");
	_runneranimation->addSpriteFrameWithFileName(
			"runnergameScene/images/runner4.png");

	_runneranimate = CCAnimate::create(_runneranimation);

	CCAction* rep = CCRepeatForever::create(_runneranimate);
	_runner->runAction(rep);
	this->addChild(_runner, 3);
	this->schedule(schedule_selector(RunnerGameScene::standTime), 1.0f);
	this->schedule(schedule_selector(RunnerGameScene::scrollUpdate));
	return true;
}

void RunnerGameScene::runnerControlCallBack(CCObject* pSender) {
	CCMenuItem *item = (CCMenuItem*) pSender;
	int tag = item->getTag();
	if (_state != 3) {
		if (tag == 1) {
			if (_scrollSpeed < 50)
				_scrollSpeed += 1;
		} else {
			AudioManager::getAudioManager()->playEffectAudio(SOUND_JUMP);
			_state = 2;
			CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(
					"runnergameScene/images/jump.png");
			_runner->pauseSchedulerAndActions();

			_runner->setTexture(tex);
			_runner->setTextureRect(
					CCRectMake(0,0,tex->getContentSize().width,tex->getContentSize().height));
		}
	}
}
void RunnerGameScene::standTime(float f) {
	CCLog("%d this is end", _state);
	if (_state == 3) {

		if (_deadCount > 3) {

			this->unschedule(schedule_selector(RunnerGameScene::standTime));
			standtimeE = _standTimeValue;
			type = 1;
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
				CCString::createWithFormat("Time:%02d:%02d", minute, seconds)->getCString());
	}
}
void RunnerGameScene::scrollUpdate(float f) {
	int hurdle1Spot = _hurdle1->boundingBox().getMidX();
	int hurdle2Spot = _hurdle2->boundingBox().getMidX();
	int hurdle3Spot = _hurdle3->boundingBox().getMidX();
	int hurdle4Spot = _hurdle4->boundingBox().getMidX();
	int hurdle5Spot = _hurdle5->boundingBox().getMidX();
	int runnerspot = _runner->boundingBox().getMidX();
	CCRect runnerRect(runnerspot, 230, 20, 20);

	if ((runnerRect.containsPoint(ccp(hurdle1Spot,230))
			|| runnerRect.containsPoint(ccp(hurdle2Spot,230))
			|| runnerRect.containsPoint(ccp(hurdle3Spot,230))
			|| runnerRect.containsPoint(ccp(hurdle4Spot,230))
			|| runnerRect.containsPoint(ccp(hurdle5Spot,230))) && _state == 1) {
		AudioManager::getAudioManager()->stopSound();
		AudioManager::getAudioManager()->playEffectAudio(SOUND_RESULT);
		this->unschedule(schedule_selector(RunnerGameScene::scrollUpdate));
		_state = 3;
		_runner->stopAllActions();
		_runControlMenu->setEnabled(false);
		_jumpControlMenu->setEnabled(false);
		CCTexture2D* tex = CCTextureCache::sharedTextureCache()->addImage(
				"runnergameScene/images/die.png");
		_runner->setTexture(tex);
		_runner->setTextureRect(
				CCRectMake(0,0,tex->getContentSize().width,tex->getContentSize().height));
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
		CCLog("%d this is end", _state);
	}
	if (_jumpCount > 30 - (_scrollSpeed / 2)) {
		_jumpCount = 0;
		_state = 1;
		_runner->resumeSchedulerAndActions();
	}
	if (_state == 2) {
		_jumpCount++;
	}
	if (_scrollBack1->getPositionX() <= 0) {
		_scrollBack1->setPosition(ccp(5100,360));
	} else if (_scrollBack2->getPositionX() <= 0) {
		_scrollBack2->setPosition(ccp(5100,360));
	}
	if (_hurdle5->getPositionX() < 40) {
		int gap = 1280;
		gap += CCRANDOM_0_1() * 1000 + 700;
		_hurdle1->setPositionX(gap);
		gap += CCRANDOM_0_1() * 1000 + 700;
		_hurdle2->setPositionX(gap);
		gap += CCRANDOM_0_1() * 1000 + 700;
		_hurdle3->setPositionX(gap);
		gap += CCRANDOM_0_1() * 1000 + 700;
		_hurdle4->setPositionX(gap);
		gap += CCRANDOM_0_1() * 1000 + 700;
		_hurdle5->setPositionX(gap);
	}
	_hurdle1->setPositionX(_hurdle1->getPositionX() - _scrollSpeed);
	_hurdle2->setPositionX(_hurdle2->getPositionX() - _scrollSpeed);
	_hurdle3->setPositionX(_hurdle3->getPositionX() - _scrollSpeed);
	_hurdle4->setPositionX(_hurdle4->getPositionX() - _scrollSpeed);
	_hurdle5->setPositionX(_hurdle5->getPositionX() - _scrollSpeed);

	_scrollBack1->setPositionX(_scrollBack1->getPositionX() - _scrollSpeed);
	_scrollBack2->setPositionX(_scrollBack2->getPositionX() - _scrollSpeed);
	if (_scrollSpeed > 3) {
		if (_slowCount > 30) {
			_slowCount = 0;
			_scrollSpeed -= 2;
		} else
			_slowCount++;
	}

}
void RunnerGameScene::keyBackClicked() {
	AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
	CCDirector::sharedDirector()->popScene();
}

RunnerGameScene::RunnerGameScene() {
	// TODO Auto-generated constructor stub

}

RunnerGameScene::~RunnerGameScene() {
	// TODO Auto-generated destructor stub
}

