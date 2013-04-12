/*
 * DialogLayer.cpp
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#include "DialogLayer.h"


DialogLayer::DialogLayer(): mMenu(NULL), mMenuItemArray(NULL), mTouchedMenu(false)
{
}

DialogLayer::~DialogLayer()
{
}

bool DialogLayer::init()
{
    bool bRet = false;

    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
//        CC_BREAK_IF(!CCLayerColor::create(ccc4(0, 0, 0, 125)));
//        CC_BREAK_IF(!CCLayerColor::create(ccc4(0, 0, 0, 125)));
//        CCLayerColor::setOpacity(128);  //设置不透明程度

        onInitDialog();
        initMenu();

        bRet = true;
    } while (0);

    return bRet;
}


void DialogLayer::pushMenu(CCMenuItem *pMenuItem)
{
    if (!mMenuItemArray) {
        mMenuItemArray = CCArray::create();
    }

    mMenuItemArray->addObject(pMenuItem);
}

bool DialogLayer::initMenu()
{
    if (mMenuItemArray && mMenuItemArray->count() > 0) {
        if (!mMenu) {
            mMenu = CCMenu::createWithArray(mMenuItemArray);
            mMenu->setPosition(CCPointZero);
            addChild(mMenu);
        }
    }
    return true;
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();

    // 屏蔽所有priority比自己大的消息
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
//    CCLayer::registerWithTouchDispatcher();
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
//    CCDirector::sharedDirector()->resume();
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // 因为拦截了所有消息(包括按钮) 所以需要将消息手动传给模态对话框上的按钮
//	CCDirector::sharedDirector()->resume();
//	removeFromParentAndCleanup(true);
    if (mMenu) {
        mTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
    }

    return true;
}

void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchMoved(pTouch, pEvent);
        }
    }
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchEnded(pTouch, pEvent);
        }
        mTouchedMenu = false;
    }
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (mTouchedMenu) {
        if (mMenu) {
            mMenu->ccTouchEnded(pTouch, pEvent);
        }
        mTouchedMenu = false;
    }
}
