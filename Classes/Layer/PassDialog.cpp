/*
 * PassDialog.cpp
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#include "PassDialog.h"
#include "Scene/GameLayer.h"


bool PassDialog::onInitDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *label = CCLabelTTF::create("Are you sure exit?", "", 64);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label);

    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(PassDialog::okMenuItemCallback));
    okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));

    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(PassDialog::cancelMenuItemCallback));
    cancelMenuItem->setPosition(ccp(winSize.width / 2 + 100, winSize.height / 2 - 50));

    pushMenu(okMenuItem);
    pushMenu(cancelMenuItem);

    setColor(ccc3(255,0,0));
    setOpacity(128);

    return true;
}

void PassDialog::okMenuItemCallback(CCObject *obj)
{
	CCLog("ok menu press down....");
//    CCDirector::sharedDirector()->end();
//	 removeFromParentAndCleanup(true);
//	 this->getParent()->removeChild(this);
	CCDirector::sharedDirector()->resume();
	removeFromParent();

}

void PassDialog::cancelMenuItemCallback(CCObject *obj)
{

	CCLog("cancel menu press down....");
//	((GameLayer*) (this->getParent()))->doResumeGame();
//	removeFromParent();
//	CCDirector::sharedDirector()->resume();
//    removeFromParentAndCleanup(true);
//    CCDirector::sharedDirector()->resume();

}
