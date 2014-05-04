//
//  ResultScene.h
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#ifndef __finger__ResultScene__
#define __finger__ResultScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class ResultScene:public CCLayer
{
private:
    void __restart();
public:
    static int flag;
    static CCScene *scene();
    virtual bool init();
    CREATE_FUNC(ResultScene);
};

#endif /* defined(__finger__ResultScene__) */
