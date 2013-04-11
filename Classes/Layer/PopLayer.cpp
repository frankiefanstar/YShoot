/*
 * PopLayer.cpp
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#include "PopLayer.h"
#include "Scene/GameLayer.h"

bool PopLayer::init() {
	bool doRet = false;
	do {
		setTouchEnabled(true);

		child = CCLayerColor::create(ccc4(0, 0, 0, 100));
		this->addChild(child);

		CCMenuItemImage *pCloseItem = CCMenuItemImage::create("heart1.png",
				"heart1.png", this,
				menu_selector(PopLayer::menuCloseCallback));
		CC_BREAK_IF(!pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(
				ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pMenu); // Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		doRet = true;
	} while (0);
	return doRet;
}


CCScene* PopLayer::scene() {
    CCScene *scene = CCScene::create();
    PopLayer *layer = PopLayer::create();
    scene->addChild(layer);

    return scene;
}

bool PopLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

    CCLog("--ccTouchBegan--Dilaog--");
    return true;
}

void PopLayer::onEnter()
{
    CCLayer::onEnter();
    /** 注册屏幕动作监听器*/
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this , 0 , true);
}

void PopLayer::onExit()
{
    CCLayer::onExit();
    /** 注销屏幕动作监听器*/
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

/**
*   点击关闭按钮
*   通知主界面弹出框已经关闭
**/
void PopLayer::menuCloseCallback(CCObject*)
{
//    dele->clickClose();
    /** 移除当前CCLayer*/
    CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
    CCDirector::sharedDirector()->resume();
    this->removeFromParent();
}

void PopLayer::setDelegate(DialogDelegate* delegates){
    dele = delegates;
}
