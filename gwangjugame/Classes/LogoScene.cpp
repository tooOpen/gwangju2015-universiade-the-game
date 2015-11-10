#include "LogoScene.h"
#include "ReadyScene.h"
USING_NS_CC;

CCScene* LogoScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    LogoScene *layer = LogoScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LogoScene::init()
{
	this->setKeypadEnabled(true);
    if ( !CCLayerColor::initWithColor(ccc4(255,255,255,255)) )
    {
        return false;
    }
    term = 0;
    CCSprite* logo = CCSprite::create("logoScene/images/logo.png");
    logo->setPosition(ccp(640, 470));
    this->addChild(logo, 0);

    CCSprite* slogan = CCSprite::create("logoScene/images/slogan.png");
    slogan->setPosition(ccp(840, 100));
    this->addChild(slogan, 0);

    CCSprite* sk = CCSprite::create("logoScene/images/sk.png");
    sk->setPosition(ccp(440, 120));
    this->addChild(sk, 0);
    this->schedule(schedule_selector(LogoScene::logoterm),1.0f);

    return true;
}

void LogoScene::logoterm(float f)
{
	if(term>3)
	{
		CCScene* pScene = ReadyScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}

	term++;

}

