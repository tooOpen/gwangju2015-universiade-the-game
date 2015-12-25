#ifndef __LOGOSCENE_H__
#define __LOGOSCENE_H__

#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
using namespace cocos2d;
class LogoScene : public cocos2d::CCLayerColor
{
private:
	 JniMethodInfo t;
	 int term;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    void logoterm(float f);
    CREATE_FUNC(LogoScene);
};

#endif // __LOGOSCENE_H__
