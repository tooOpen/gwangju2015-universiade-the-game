/*
 * HallofFame.cpp
 *
 *  Created on: 2014. 9. 19.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/gwangjugame/Classes/HallofFame.h"

USING_NS_CC;
int standtimeE;
int type; //1 run. 2. shot. 3 gym

CCScene* HallofFame::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HallofFame *layer = HallofFame::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
void insertNew(int* arr,int newbie)
 {
	if (arr[0] <= newbie) {
		arr[2] = arr[1];
		arr[1] = arr[0];
		arr[0] = newbie;
	} else if (arr[1] <= newbie) {
		arr[2] = arr[1];
		arr[1] = newbie;
	} else if (arr[2] <= newbie) {
		arr[2] = newbie;
	}
}
// on "init" you need to initialize your instance
bool HallofFame::init() {
	this->setKeypadEnabled(true);
	if (!CCLayerColor::initWithColor(ccc4(255, 255, 255, 255))) {
		return false;
	}
	AudioManager::getAudioManager()->playSound(SOUND_HALL);
	runArr[3] ={0,};
	shotArr[3]={0,};
	gymArr[3]={0,};

	runArr[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("runFrist",0);
	runArr[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("runSecond",0);
	runArr[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("runThird",0);

	shotArr[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("shotFrist",0);
	shotArr[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("shotSecond",0);
	shotArr[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("shotThird",0);

	gymArr[0] = CCUserDefault::sharedUserDefault()->getIntegerForKey("gymFrist",0);
	gymArr[1] = CCUserDefault::sharedUserDefault()->getIntegerForKey("gymSecond",0);
	gymArr[2] = CCUserDefault::sharedUserDefault()->getIntegerForKey("gymThird",0);


	if(type == 1)
	insertNew(runArr,standtimeE);
	else if(type == 2)
	insertNew(shotArr,standtimeE);
	else
	insertNew(gymArr,standtimeE);

	_runfirst = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", runArr[0]/60, runArr[0]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_runfirst->setColor(ccc3(255, 0, 0));
	_runfirst->setAnchorPoint(ccp(0,0.5));
	_runfirst->setPosition(ccp(210,350));
	this->addChild(_runfirst, 4);

	_runsecond = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", runArr[1]/60, runArr[1]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_runsecond->setColor(ccc3(0, 0, 0));
	_runsecond->setAnchorPoint(ccp(0,0.5));
	_runsecond->setPosition(ccp(210,200));
	this->addChild(_runsecond, 4);

	_runthird = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", runArr[2]/60, runArr[2]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_runthird->setColor(ccc3(0, 0, 0));
	_runthird->setAnchorPoint(ccp(0,0.5));
	_runthird->setPosition(ccp(210,40));
	this->addChild(_runthird, 4);

	_shotfirst = CCLabelTTF::create(CCString::createWithFormat("%4d", shotArr[0])->getCString(),
			"fonts/darkforest.ttf", 100);
	_shotfirst->setColor(ccc3(255, 0, 0));
	_shotfirst->setAnchorPoint(ccp(0,0.5));
	_shotfirst->setPosition(ccp(630,350));
	this->addChild(_shotfirst, 4);

	_shotsecond = CCLabelTTF::create(CCString::createWithFormat("%4d", shotArr[1])->getCString(),
			"fonts/darkforest.ttf", 100);
	_shotsecond->setColor(ccc3(0, 0, 0));
	_shotsecond->setAnchorPoint(ccp(0,0.5));
	_shotsecond->setPosition(ccp(630,200));
	this->addChild(_shotsecond, 4);

	_shotthird= CCLabelTTF::create(CCString::createWithFormat("%4d", shotArr[2])->getCString(),
			"fonts/darkforest.ttf", 100);
	_shotthird->setColor(ccc3(0, 0, 0));
	_shotthird->setAnchorPoint(ccp(0,0.5));
	_shotthird->setPosition(ccp(630,40));
	this->addChild(_shotthird, 4);

	_gymfirst = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", gymArr[0]/60, gymArr[0]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_gymfirst->setColor(ccc3(255, 0, 0));
	_gymfirst->setAnchorPoint(ccp(0,0.5));
	_gymfirst->setPosition(ccp(1050,350));
	this->addChild(_gymfirst, 4);

	_gymsecond = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", gymArr[1]/60, gymArr[1]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_gymsecond->setColor(ccc3(0, 0, 0));
	_gymsecond->setAnchorPoint(ccp(0,0.5));
	_gymsecond->setPosition(ccp(1050,200));
	this->addChild(_gymsecond, 4);

	_gymthird = CCLabelTTF::create(CCString::createWithFormat("%02d:%02d", gymArr[2]/60, gymArr[2]%60)->getCString(),
			"fonts/darkforest.ttf", 100);
	_gymthird->setColor(ccc3(0, 0, 0));
	_gymthird->setAnchorPoint(ccp(0,0.5));
	_gymthird->setPosition(ccp(1050,40));
	this->addChild(_gymthird, 4);



	_fameback = CCSprite::create("wintable/images/fameback.jpg");
	_fameback->setPosition(ccp(640, 360));
	this->addChild(_fameback, 0);


	_fameText = CCSprite::create("wintable/images/afaf.png");
	_fameText->setPosition(ccp(640, 630));
	this->addChild(_fameText, 1);

	_stand1 = CCSprite::create("wintable/images/stand.png");
	_stand1->setPosition(ccp(125, 180));
	this->addChild(_stand1, 1);

	_stand2 = CCSprite::create("wintable/images/stand.png");
	_stand2->setPosition(ccp(550, 180));
	this->addChild(_stand2, 1);

	_stand3 = CCSprite::create("wintable/images/stand.png");
	_stand3->setPosition(ccp(970, 180));
	this->addChild(_stand3, 1);

	_runpicto = CCSprite::create("wintable/images/picrun.png");
	_runpicto->setPosition(ccp(310, 470));
	this->addChild(_runpicto, 1);

	_shotpicto = CCSprite::create("wintable/images/picshot.png");
	_shotpicto->setPosition(ccp(735, 470));
	this->addChild(_shotpicto, 1);

	_gympicto = CCSprite::create("wintable/images/picgym.png");
	_gympicto->setPosition(ccp(1150, 470));
	this->addChild(_gympicto, 1);

	_homeBtn = CCMenuItemImage::create(
				"wintable/images/homebtn.png",
				"wintable/images/homebtnDown.png", this,
				menu_selector(HallofFame::hallofFameClick));
	_homeBtn->setTag(1);
	_homeBtn->setPosition(ccp(-550,0));

	_quitBtn = CCMenuItemImage::create(
					"wintable/images/quitbtn.png",
					"wintable/images/quitbtnDown.png", this,
					menu_selector(HallofFame::hallofFameClick));
	_quitBtn->setTag(2);
	_quitBtn->setPosition(ccp(550,5));

	_hallMenu = CCMenu::create(_homeBtn,_quitBtn,NULL);
	_hallMenu->setPosition(ccp(640,650));
	this->addChild(_hallMenu , 5);
	return true;
}

void HallofFame::hallofFameClick(CCObject* pSender)
{
	CCMenuItem *item = (CCMenuItem*) pSender;
		int tag = item->getTag();

	CCUserDefault::sharedUserDefault()->setIntegerForKey("runFrist",runArr[0]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("runSecond",runArr[1]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("runThird",runArr[2]);

	CCUserDefault::sharedUserDefault()->setIntegerForKey("shotFrist", shotArr[0]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("shotSecond",shotArr[1]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("shotThird",shotArr[2]);

	CCUserDefault::sharedUserDefault()->setIntegerForKey("gymFrist",gymArr[0]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gymSecond",gymArr[1]);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gymThird",gymArr[2]);

	if(tag == 1)
	{
		AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
		CCDirector::sharedDirector()->popScene();
	}
	else
	{
		CCDirector::sharedDirector()->end();
	}
}

