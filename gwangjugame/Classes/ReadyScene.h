/*
 * MainMenuScene.h
 *
 *  Created on: 2014. 1. 27.
 *       Author: bsh
 */

#ifndef READYSCENE_H_
#define READYSCENE_H_
#include "cocos2d.h"

#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;

class ReadyScene :public CCLayer {
public:
	ReadyScene();
	virtual ~ReadyScene();

	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(ReadyScene);
	JniMethodInfo t;		//JNI 메소드 정보 변수
	CCSprite* _background;  //배경 스프라이트
	CCSprite* _title;		//타이틀 스프라이트
	CCSprite* _gametitle;		//게임타이틀
	CCMenuItemImage* _menuGamePlay; 		//게임시작 메뉴아이템

	CCAnimation *_backanimation;
	CCAnimate *_backanimate;
	CCMenu* _startMenu;		//게임시작 메뉴
	bool btnvisible;
	void btnTerm(float f);
	virtual void keyBackClicked();					//안드로이드 백 버튼 재 정의
	void menuGamePlayCallBack(CCObject* pSender);	//게임시작 메뉴 선택 시 호출되는 콜백 함수
};

#endif /* READYSCENE_H_ */
