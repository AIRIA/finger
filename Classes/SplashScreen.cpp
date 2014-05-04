//
//  SplashScreen.cpp
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#include "SplashScreen.h"
#include "VisibleRect.h"
#include "BattleScene.h"

CCScene *SplashScreen::scene()
{
    CCScene *wrapperScene = CCScene::create();
    wrapperScene->addChild(SplashScreen::create());
    return wrapperScene;
}

bool SplashScreen::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *logo = CCSprite::create("logo.png");
    logo->setOpacity(0);
    logo->setPosition(VisibleRect::center());
    CCSprite *splash = CCSprite::create("splash.png");
    CCSize splashSize = splash->getContentSize();
    splash->setOpacity(0);
    splash->setPosition(VisibleRect::center());
    CCActionInterval *fadeIn = CCFadeIn::create(0.5f);
    CCCallFunc *loadHandler = CCCallFunc::create(this, callfunc_selector(SplashScreen::__loadAssets));
    CCActionInterval *delayAct = CCDelayTime::create(1.0f);
    CCActionInterval *fadeOut = CCFadeOut::create(0.5f);
    CCCallFunc *startHandler = CCCallFunc::create(this, callfunc_selector(SplashScreen::__startGame));
    CCSequence *splashSeq = CCSequence::create(fadeIn,loadHandler,delayAct,fadeOut,startHandler,NULL);
    addChild(splash);
    addChild(logo);
    splash->setScaleX(winSize.width/splashSize.width);
    logo->setScale(winSize.width/splashSize.width);
    splash->setScaleY(winSize.height/splashSize.height);
    logo->runAction(splashSeq);
    splash->runAction((CCActionInterval*)fadeIn->copy());
    return true;
}

void SplashScreen::__loadAssets()
{
    
}

void SplashScreen::__startGame()
{
    CCDirector::sharedDirector()->replaceScene(BattleScene::scene());
}