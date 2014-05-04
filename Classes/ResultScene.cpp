//
//  ResultScene.cpp
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#include "VisibleRect.h"
#include "BattleScene.h"
#include "ResultScene.h"
#include "AdUtil.h"

int ResultScene::flag = 0;

CCScene *ResultScene::scene()
{
    CCScene *wrapper = CCScene::create();
    wrapper->addChild(ResultScene::create());
    return wrapper;
}

bool ResultScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor *layerColor = CCLayerColor::create(ccc4(126,187,248, 255));
    layerColor->setContentSize(winSize);
    addChild(layerColor);
    
    CCSprite *no1 = CCSprite::create("win.png");
    no1->setScale(winSize.width/640);
    no1->setPosition(VisibleRect::center()+ccp(0, 100));
    CCLabelTTF *winLabel = CCLabelTTF::create("", "Arial", 150);
    winLabel->setColor(ccWHITE);
    winLabel->setPosition(no1->getPosition()-ccp(0,300));
    addChild(no1);
    
    if (flag==0) {
        winLabel->setString("红方胜利");
    }else{
        winLabel->setString("绿方胜利");
    }
    addChild(winLabel);
    winLabel->setScale(no1->getScale());
    CCCallFunc *restartFunc = CCCallFunc::create(this, callfunc_selector(ResultScene::__restart));
    runAction(CCSequence::create(CCDelayTime::create(10),restartFunc,NULL));
    AdUtil::showAds();
    return true;
}

void ResultScene::__restart()
{
    CCDirector::sharedDirector()->replaceScene(BattleScene::scene());
}