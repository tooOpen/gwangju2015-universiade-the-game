/*
 * MainmenuScene.cpp
 *
 *  Created on: 2014. 9. 16.
 *      Author: pc
 */

#include "C:/cocos2d-x-2.2.3/cocos2d-x-2.2.3/projects/gwangjugame/Classes/MainmenuScene.h"

using namespace extension;

CCScene* MainmenuScene::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainmenuScene *layer = MainmenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainmenuScene::init() {
	this->setKeypadEnabled(true);
	AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
	_volume = CCUserDefault::sharedUserDefault()->getIntegerForKey("SFXvolume",
			10);
	_state = 0;

	_helpScene = CCSprite::create("menuScene/images/helpScene.jpg");
	_helpScene->setPosition(ccp(640,360));
	_helpScene->setVisible(false);
		this->addChild(_helpScene, 10);

	_menuBack = CCSprite::create("menuScene/images/menuBack.jpg");
	_menuBack->setPosition(ccp(640,360));
	this->addChild(_menuBack, 0);

	_optionBack = CCSprite::create("menuScene/images/optionBack.jpg");
	_optionBack->setPosition(ccp(640,360));
	_optionBack->setVisible(false);
	this->addChild(_optionBack, 0);

	_shootingItem = CCMenuItemImage::create("menuScene/images/shootingicon.png",
			"menuScene/images/shootingiconSelected.png", this,
			menu_selector(MainmenuScene::gameMenuClick));
	_shootingItem->setPosition(ccp(180,400));
	_shootingItem->setTag(1);

	_gameoptionItem = CCMenuItemImage::create(
			"menuScene/images/settingicon.png",
			"menuScene/images/settingiconSelected.png", this,
			menu_selector(MainmenuScene::gameMenuClick));
	_gameoptionItem->setTag(2);
	_gameoptionItem->setPosition(ccp(1100,50));

	_gymnasticItem = CCMenuItemImage::create(
			"menuScene/images/gymnasticicon.png",
			"menuScene/images/gymnasticiconSelected.png", this,
			menu_selector(MainmenuScene::gameMenuClick));
	_gymnasticItem->setTag(3);
	_gymnasticItem->setPosition(ccp(180,50));

	_runningItem = CCMenuItemImage::create("menuScene/images/runningicon.png",
			"menuScene/images/runningiconSelected.png", this,
			menu_selector(MainmenuScene::gameMenuClick));
	_runningItem->setTag(4);
	_runningItem->setPosition(ccp(1100,400));


	_helpItem = CCMenuItemImage::create("menuScene/images/helpBtn.png",
				"menuScene/images/helpBtnDown.png", this,
				menu_selector(MainmenuScene::gameMenuClick));
	_helpItem->setTag(5);
	_helpItem->setPosition(ccp(880,-40));

	_gameMenu = CCMenu::create(_shootingItem, _gymnasticItem, _gameoptionItem,
			_runningItem,_helpItem, NULL);

	_gameMenu->setPosition(ccp(0,130));
	_gameMenu->retain();
	this->addChild(_gameMenu, 2);

	_volumeSlider = CCControlSlider::create("menuScene/images/sliderTrack2.png",
			"menuScene/images/sliderProgress2.png",
			"menuScene/images/sliderThumb.png");
	_volumeSlider->setMinimumValue(0.0f);
	_volumeSlider->setMaximumValue(10.0f);

	_volumeSlider->setValue(_volume); ////////////////
	_volumeSlider->setPosition(ccp(680,320));
	_volumeSlider->addTargetWithActionForControlEvents(this,
			cccontrol_selector(MainmenuScene::sliderValuechange),
			CCControlEventValueChanged);
	_volumeSlider->setScale(3.0f);
	_volumeSlider->retain();

	_volumeSet = CCLabelTTF::create("SFX Volume", "fonts/darkforest.ttf", 100);
	_volumeSet->setColor(ccc3(0, 0, 0));
	_volumeSet->setPosition(ccp(650,410));
	_volumeSet->setVisible(false);
	_volumeSet->retain();
	this->addChild(_volumeSet, 4);

	return true;

}
void MainmenuScene::gameMenuClick(CCObject* pSender) { // 게임메뉴 클릭 시
	AudioManager::getAudioManager()->stopSound();
	AudioManager::getAudioManager()->playEffectAudio(SOUND_CLICK);
	CCMenuItem *item = (CCMenuItem*) pSender;
	int tag = item->getTag();
	if (tag == 1) //shooting btn
			{
		CCScene* pScene = ShootingGameScene::scene();
		CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.5f,pScene));
	} else if (tag == 2) // option btn
			{
		_gameMenu->setEnabled(false);
		_gameMenu->setVisible(false);
		_optionBack->setVisible(true);
		_state = 2;
		this->addChild(_volumeSlider, 3);
		_volumeSet->setVisible(true);
	} else if (tag == 3) // not decided btn
			{
		CCScene* pScene = GymnasticGameScene::scene();
		CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.5f,pScene));
	} else if (tag == 4) // running btn
			{

		CCScene* pScene = RunnerGameScene::scene();
		CCDirector::sharedDirector()->pushScene(CCTransitionFadeBL::create(0.5f,pScene));
	}
	else
	{
		_state = 3;
		_helpScene->setVisible(true);
	}
}
void MainmenuScene::sliderValuechange(CCObject* sender,
		CCControlEvent controlEvent) {
	CCControlSlider* pSlider = (CCControlSlider*) sender;
	_volume = pSlider->getValue();
}

void MainmenuScene::keyBackClicked() {

	if(_state ==2) //설정화면일 시
	{
		AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("SFXvolume",
				_volume);
		AudioManager::getAudioManager()->setSFXvolume(_volume);
		this->removeChild(_volumeSlider);
		_volumeSet->setVisible(false);
		_optionBack->setVisible(false);
		_gameMenu->setEnabled(true);
		_gameMenu->setVisible(true);
		_state = 0;
	}else if(_state==3)
		{
		AudioManager::getAudioManager()->playSound(SOUND_MENUAUDIO);
		_helpScene->setVisible(false);
				_state = 0;
		}
	else{
		if (JniHelper::getStaticMethodInfo(t, "com/gwangu/game/gwangjugame",
				"callDialog", "()V")) {
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
}

MainmenuScene::MainmenuScene() {
	// TODO Auto-generated constructor stub

}

MainmenuScene::~MainmenuScene() {
	// TODO Auto-generated destructor stub
}

