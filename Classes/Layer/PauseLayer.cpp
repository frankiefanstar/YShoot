/*
 * PauseLayer.cpp
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#include "PauseLayer.h"

bool PauseLayer::onInitDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    //TODO  增加图片和按钮

//    CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "", 64);
//    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
//    this->addChild(label);
//
//    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(PassDialog::okMenuItemCallback));
//    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
//
//    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(PassDialog::cancelMenuItemCallback));
//    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));
//
//    pushMenu(okMenuItem);
//    pushMenu(cancelMenuItem);
//
//    setColor(ccc3(255,0,0));
//    setOpacity(128);

    return true;
}

void PauseLayer::okMenuItemCallback(CCObject *obj)
{

	CCDirector::sharedDirector()->resume();
	//TODO resume music

	removeFromParent();

}

void PauseLayer::exitMenuItemCallback(CCObject *obj)
{

	CCLog("cancel menu press down....");
}
