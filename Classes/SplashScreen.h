//
//  SplashScreen.h
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#ifndef __finger__SplashScreen__
#define __finger__SplashScreen__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class SplashScreen:public CCLayer
{
private:
    void __loadAssets();
    void __startGame();
public:
    static CCScene *scene();
    CREATE_FUNC(SplashScreen);
    virtual bool init();
};

#endif /* defined(__finger__SplashScreen__) */
