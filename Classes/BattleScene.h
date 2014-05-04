//
//  BattleScene.h
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#ifndef __finger__BattleScene__
#define __finger__BattleScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class BattleScene:public CCLayer
{
private:
    void __startGame(CCObject *pSender);
    void __delayCounter(float delta);
    void __realStart();
    void __layerTouch(CCObject *pSender);
    void __rmStartHandler();
public:
    static CCScene *scene();
    CREATE_FUNC(BattleScene);
    virtual bool init();
};

#endif /* defined(__finger__BattleScene__) */
