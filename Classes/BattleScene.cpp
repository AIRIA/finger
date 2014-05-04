//
//  BattleScene.cpp
//  finger
//
//  Created by AIRIA on 14-5-4.
//
//

#include "BattleScene.h"
#include "BaseLayer.h"
#include "VisibleRect.h"
#include "BaseSprite.h"
#include "ResultScene.h"
#include "AdUtil.h"

enum{
    kStartLabel,
    kStartSprite,
    kStartNode,
    kGrayLayer,
    kOrangeLayer
} NodeTag;

CCScene *BattleScene::scene()
{
    AdUtil::showAds();
    CCScene *wrapper = CCScene::create();
    wrapper->addChild(BattleScene::create());
    return wrapper;
}

bool BattleScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    BaseLayer *grayLayer = BaseLayer::create(ccc4(74,179,88, 255),winSize);
    BaseLayer *orangeLayer = BaseLayer::create(ccc4(240,55,46, 255), winSize);
    grayLayer->ignoreAnchorPointForPosition(false);
    orangeLayer->ignoreAnchorPointForPosition(false);
    grayLayer->setAnchorPoint(ccp(0.5f, 0.0f));
    orangeLayer->setAnchorPoint(ccp(0.5f, 1.0f));
    grayLayer->setPosition(VisibleRect::center());
    orangeLayer->setPosition(VisibleRect::center());
    addChild(grayLayer);
    grayLayer->setTag(kGrayLayer);
    orangeLayer->setTag(kOrangeLayer);
    addChild(orangeLayer);
    orangeLayer->setTarget(this, menu_selector(BattleScene::__layerTouch));
    grayLayer->setTarget(this, menu_selector(BattleScene::__layerTouch));
    
    CCNode *startNode = CCNode::create();
    startNode->setPosition(VisibleRect::center());
    BaseSprite *start = BaseSprite::create("rect.png");
    CCSprite *innerRect = CCSprite::createWithTexture(start->getTexture());
    start->setColor(ccBLACK);
    startNode->setScale(winSize.width/640);
    startNode->addChild(start);
    startNode->addChild(innerRect);
    innerRect->setTag(kStartSprite);
    innerRect->setScale(0.9f);
    addChild(startNode);
    startNode->setTag(kStartNode);
    
    CCLabelTTF *startLabel = CCLabelTTF::create("点击开始", "Arial", 70, CCSizeMake(180,200),kCCTextAlignmentCenter);
    startLabel->setColor(ccBLACK);
    startLabel->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
    startNode->addChild(startLabel);
    startLabel->setTag(kStartLabel);
    start->setTargetBegan(this, menu_selector(BattleScene::__startGame));
    return true;
}

void BattleScene::__startGame(cocos2d::CCObject *pSender)
{
    CCNode *startNode = getChildByTag(kStartNode);
    CCLabelTTF *label = (CCLabelTTF*)startNode->getChildByTag(kStartLabel);
    label->setFontSize(120);
    label->setString("3");
    BaseSprite *bs = (BaseSprite*)pSender;
    bs->setTouchEnabled(false);
    schedule(schedule_selector(BattleScene::__delayCounter), 1.0f);
}

void BattleScene::__delayCounter(float delta)
{
    static int second = 2;
    CCNode *startNode = getChildByTag(kStartNode);
    CCLabelTTF *label = (CCLabelTTF*)startNode->getChildByTag(kStartLabel);
    if(second==0){
        CCSprite *startSpr = (CCSprite*)startNode->getChildByTag(kStartSprite);
        startSpr->setColor(ccGREEN);
        label->setFontSize(80);
        label->setString("GO");
        unschedule(schedule_selector(BattleScene::__delayCounter));
        CCCallFunc *delayCall = CCCallFunc::create(this, callfunc_selector(BattleScene::__realStart));
        startNode->runAction(CCSequence::create(CCDelayTime::create(0.5f),delayCall,NULL));
        second = 2;
        return;
    }
    char time[5];
    sprintf(time, "%d",second);
    label->setString(time);
    second--;
}

void BattleScene::__realStart()
{
    CCNode *startNode = getChildByTag(kStartNode);
    CCActionInterval *rotate = CCRotateBy::create(0.5f, 360);
    CCActionInterval *scale = CCScaleTo::create(0.5f, 0);
    CCCallFunc *rmSelf = CCCallFunc::create(this, callfunc_selector(BattleScene::__rmStartHandler));
    CCSpawn *hide = CCSpawn::create(rotate,scale,NULL);
    startNode->runAction(CCSequence::create(hide,rmSelf,NULL));
}

void BattleScene::__rmStartHandler()
{
    CCNode *startNode = getChildByTag(kStartNode);
    startNode->removeFromParent();
    BaseLayer *gray = (BaseLayer*)getChildByTag(kGrayLayer);
    BaseLayer *orange = (BaseLayer*)getChildByTag(kOrangeLayer);
    gray->setTouchEnabled(true);
    orange->setTouchEnabled(true);
}

void BattleScene::__layerTouch(cocos2d::CCObject *pSender)
{
    int nt = ((CCNode*)pSender)->getTag();
    CCNode *gray = getChildByTag(kGrayLayer);
    CCNode *orange = getChildByTag(kOrangeLayer);
    CCNode *node = getChildByTag(nt);
    float posY = node->getPositionY();
    switch (nt) {
        case kGrayLayer:
        {
            float targetPos = posY-20;
            gray->setPositionY(targetPos);
            orange->setPositionY(targetPos);
            if (targetPos<=0) {
                ResultScene::flag = 1;
                CCDirector::sharedDirector()->replaceScene(ResultScene::scene());
            }
        }
            break;
        case kOrangeLayer:
        {
            float targetPos = posY+20;

            gray->setPositionY(targetPos);
            orange->setPositionY(targetPos);
            if (targetPos>=CCDirector::sharedDirector()->getWinSize().height) {
                ResultScene::flag = 0;
                CCDirector::sharedDirector()->replaceScene(ResultScene::scene());
            }
        }
            break;
        default:
            break;
    }
}
