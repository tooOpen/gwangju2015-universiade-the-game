/*
 * HallofFame.h
 *
 *  Created on: 2014. 9. 19.
 *      Author: pc
 */
#ifndef HALLOFFAME_H_
#define HALLOFFAME_H_

#include "cocos2d.h"
#include "manager/AudioManager.h"
using namespace cocos2d;
extern int standtimeE;
extern int type; //1 run. 2. shot. 3 gym
class HallofFame : public cocos2d::CCLayerColor
{
private:
	int runArr[3];
	int shotArr[3];
	int gymArr[3];

	 CCSprite* _fameText;

	 CCSprite* _stand1;
	 CCSprite* _stand2;
	 CCSprite* _stand3;
	 CCSprite* _fameback;

	 CCLabelTTF* _runfirst;
	 CCLabelTTF* _runsecond;
	 CCLabelTTF* _runthird;

	 CCLabelTTF* _shotfirst;
	 CCLabelTTF* _shotsecond;
	 CCLabelTTF* _shotthird;

	 CCLabelTTF* _gymfirst;
	 CCLabelTTF* _gymsecond;
	 CCLabelTTF* _gymthird;


	 CCSprite* _runpicto;
	 CCSprite* _shotpicto;
	 CCSprite* _gympicto;

	 CCMenuItemImage* _homeBtn;
	 CCMenuItemImage* _quitBtn;

	 CCMenu* _hallMenu;
public:
    virtual bool init();
    static CCScene* scene();
	void hallofFameClick(CCObject* pSender);
    CREATE_FUNC(HallofFame);
};

#endif /* HALLOFFAME_H_ */
