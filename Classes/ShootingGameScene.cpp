/*
 * ShootingGameScene.cpp
 *
 *  Created on: 2014. 9. 20.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/gwangjugame/Classes/ShootingGameScene.h"
USING_NS_CC;

const static int tenPoint = 30;
const static int ninePoint = 80;
const static int eightPoint = 120;
const static int sevenPoint = 170;
const static int sixPoint = 210;
const static int fivePoint = 260;
const static int fourPoint = 310;
const static int threePoint = 360;

const int centerX = 640;
const int centerY = 360;

#define FIX_POS(_pos,_min,_max) \
	if(_pos<_min) \
	_pos = _min; \
    else if(_pos>_max) \
    _pos = _max; \

CCScene* ShootingGameScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ShootingGameScene *layer = ShootingGameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ShootingGameScene::init() {
	this->setKeypadEnabled(true);
	if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
		return false;
	}
	AudioManager::getAudioManager()->playSound(SOUND_SHOTBACK);
	leftshot = 5;
	_state = 0;
	_readyCount = 0;
	_totallScore = 0;
	winsize = CCDirector::sharedDirector()->getWinSize();

	_target = CCSprite::create("shootinggameScene/images/target.jpg");
	_target->setPosition(ccp(640,360));
	this->addChild(_target, 3);

	_bulletmark = CCSprite::create("shootinggameScene/images/bulletmark.png");
	_bulletmark->setPosition(ccp(640,360));
	_bulletmark->setVisible(false);
	this->addChild(_bulletmark, 6);

	_scoretex = CCSprite::create("shootinggameScene/images/score.png");
	_scoretex->setPosition(ccp(1110,650));
	this->addChild(_scoretex, 3);

	_aim = CCSprite::create("shootinggameScene/images/aim.png");
	_aim->setPosition(ccp(640,360));
	this->addChild(_aim, 5);
	_aim->retain();

	_shootBtn = CCMenuItemImage::create("shootinggameScene/images/shootBtn.png",
			"shootinggameScene/images/shootBtnDown.png", this,
			menu_selector(ShootingGameScene::shootClick));

	_shootMenu = CCMenu::create(_shootBtn, NULL);
	_shootMenu->setPosition(ccp(1130,250));
	this->addChild(_shootMenu, 3);

	_score = CCLabelTTF::create(CCString::createWithFormat("%d", _totallScore)->getCString(), "fonts/SF Collegiate.ttf", 200);
	_score->setPosition(ccp(1110,500));
	_score->setColor(ccc3(0, 0, 0));
		this->addChild(_score, 3);

	_leftShot = CCLabelTTF::create(CCString::createWithFormat("%d", leftshot)->getCString(), "fonts/SF Collegiate.ttf", 200);
	_leftShot->setPosition(ccp(60,300));
	_leftShot->setColor(ccc3(0, 0, 0));
	this->addChild(_leftShot, 3);

	_shotTex = CCLabelTTF::create("SHOT", "fonts/SF Collegiate.ttf", 70);
	_shotTex->setPosition(ccp(190,260));
	_shotTex->setColor(ccc3(84, 84, 84));
	this->addChild(_shotTex, 3);
	this->schedule(schedule_selector(ShootingGameScene::balanceinterruption),0.1f);
	return true;
}
ShootingGameScene::~ShootingGameScene(void) {
	_aim->release();
}

void ShootingGameScene::onEnter() {
	CCLayer::onEnter();
	setAccelerometerEnabled(true);
}

void ShootingGameScene::didAccelerate(CCAcceleration* pAccelerationValue) {
	CCDirector* pDir = CCDirector::sharedDirector();
	if (_aim == NULL)
		return;
	CCSize aimsize = _aim->getContentSize();

	CCPoint aimNow = _aim->getPosition();
	CCPoint aimTemp = pDir->convertToUI(aimNow);

	aimTemp.x += pAccelerationValue->x * 50.0f;
	aimTemp.y -= pAccelerationValue->y * 50.0f;//9.81f;

	CCPoint aimNext = pDir->convertToGL(aimTemp);
	FIX_POS(aimNext.x,(aimsize.width/2.0),(winsize.width  - aimsize.width/2.0f));
	FIX_POS(aimNext.y,(aimsize.height/2.0),(winsize.height  - aimsize.height/2.0f));

	_aim->setPosition(aimNext);
}
void ShootingGameScene::shootClick(CCObject* pSender) {
	AudioManager::getAudioManager()->playEffectAudio(SOUND_SHOT);
	_state = 2;
	_shootMenu->setEnabled(false);
	_shootBtn->setNormalImage(CCSprite::create("shootinggameScene/images/shootBtnUnabled.png"));

	CCPoint aimPos = _aim->getPosition();
	_bulletmark->setPosition(ccp(aimPos.x,aimPos.y));
	_bulletmark->setVisible(true);
	int radian = (int) sqrt(pow((aimPos.x - centerX), 2) + pow((aimPos.y - centerY), 2));
	if (radian < tenPoint) {
			//CCLog("tenPoint");
			_totallScore+=10;
		} else if (radian < ninePoint) {
			//CCLog("ninePoint");
			_totallScore+=9;
		} else if (radian < eightPoint) {
			//CCLog("eightPoint");
			_totallScore+=8;
		} else if (radian < sevenPoint) {
			//CCLog("sevenPoint");
			_totallScore+=7;
		} else if (radian < sixPoint) {
			//CCLog("sixPoint");
			_totallScore+=6;
		} else if (radian < fivePoint) {
			//CCLog("fivePoint");
			_totallScore+=5;
		} else if (radian < fourPoint) {
			//CCLog("fourPoint");
			_totallScore+=4;
		} else if (radian < threePoint) {
			//CCLog("threePoint");
			_totallScore+=3;
		}

	_leftShot->setString(
			CCString::createWithFormat("%d", --leftshot)->getCString());
	_score->setString(CCString::createWithFormat("%d", _totallScore)->getCString());

	if (leftshot == 0) {
		AudioManager::getAudioManager()->stopSound();
		AudioManager::getAudioManager()->playEffectAudio(SOUND_RESULT);
			_state = 3;
			_shootMenu->setEnabled(false);
			CCString temp;
			if (_totallScore > 45)
				temp = "common/images/perfect.png";
			else if (_totallScore > 35)
				temp = "common/images/good.png";
			else
				temp = "common/images/bad.png";

			_result = CCSprite::create(temp.getCString());
			_result->setPosition(ccp(640,360));
			_result->setOpacity(0);
			this->addChild(_result, 7);
			CCActionInterval* myAction = CCFadeIn::create(1.5);
			_result->runAction(myAction);
		}
}

void ShootingGameScene::balanceinterruption(float f) {
	if(_state == 3)
	{
		setAccelerometerEnabled(false);
		if (_deadCount > 30) {
					this->unschedule(schedule_selector(ShootingGameScene::balanceinterruption));
					standtimeE = _totallScore;
					type = 2;
					CCScene* pScene = HallofFame::scene();
					CCDirector::sharedDirector()->replaceScene(
							CCTransitionPageTurn::create(0.5f, pScene, false));
				} else
					_deadCount++;
	}else if(_state ==2)
	{
		if(_readyCount >20)
		{
			_bulletmark->setVisible(false);
			_shootBtn->setNormalImage(CCSprite::create("shootinggameScene/images/shootBtn.png"));
			_shootMenu->setEnabled(true);
			_readyCount = 0;
			_state = 1;
		}
		else
			_readyCount++;
	}
	else
	{
	int randvalueX = rand() % 70 + 1;
	float plusminusX = CCRANDOM_MINUS1_1();
	randvalueX = (int) randvalueX * plusminusX;

	int randvalueY = rand() % 70 + 1;
	float plusminusY = CCRANDOM_MINUS1_1();
	randvalueY = (int) randvalueY * plusminusY;

	_aim->setPosition(ccp(_aim->getPositionX()+randvalueX,_aim->getPositionY()+randvalueY));
	}
}


void ShootingGameScene::keyBackClicked() {
	AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
	CCDirector::sharedDirector()->popScene();
}

