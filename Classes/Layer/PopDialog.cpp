/*
 * PopDialog.cpp
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#include "PopDialog.h"

CCScene* PopDialog::scene() {
    CCScene *scene = CCScene::create();
    CCLayerColor* layer = PopDialog::create();
    scene->addChild(layer);

    return scene;
}

bool PopDialog::init() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemImage *mPlayButton = CCMenuItemImage::create("heart1.png", "iheart1.png", "heart1.png");
//    mPlayButton->setTarget(this, menu_selector(PopDialog::backCallback));
//    mPlayButton->setTarget(this);
    mPlayButton->setPosition(ccp(200, 300));

    CCMenu *playButtonMenu = CCMenu::create(mPlayButton, NULL);
//    playButtonMenu->setPosition( ccp(winSize.width * 0.5, winSize.height * 0.4) );
    playButtonMenu->setPosition(CCPointZero);
    this->addChild(playButtonMenu, 1);

    setTouchEnabled(true);

    create(ccc4(0,0,0,170), winSize.width, winSize.height);

    return true;
}

void PopDialog::onEnter() {
	CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-1, true);
}

void PopDialog::onExit() {

}

//void PopDialog::registerWithTouchDispatcher() {
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

bool PopDialog::ccTouchBegan(CCTouch *touch, CCEvent *event) {

    return true;
}


void PopDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {

}

void PopDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {

}

void PopDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {

}





