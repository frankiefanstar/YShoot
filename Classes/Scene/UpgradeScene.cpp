/*
 * UpgradeScene.cpp
 *
 *  Created on: 2013-3-25
 *      Author: rescue01
 */

#include "UpgradeScene.h"
#include <limits>

//using namespace CocosDenshion;

CCMenu *menu;

CCScene* UpgradeScene::scene() {
	CCScene* scene = CCScene::create();
	UpgradeScene* layer = UpgradeScene::create();

	scene->addChild(layer);
	return scene;

}

bool UpgradeScene::init() {

	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
		return false;
	}

//	if(!CCLayer::init()) {
//		return false;
//	}

// 开启触控
	setTouchEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuItemImage *img = CCMenuItemImage::create("Night-Vision_01.png",
			"Night-Vision_01.png");
	img->setAnchorPoint(ccp(0.5, 0.5));
	img->setPosition(ccp(winSize.width/2, winSize.height/2));

	menu = CCMenu::create(img, NULL);
	menu->setAnchorPoint(ccp(0.5, 0.5));
	menu->setPosition(CCPointZero);
	addChild(menu, 1, 10);

	return true;
}

void UpgradeScene::registerWithTouchDispatcher() {

	// NDK编译，需加上头 #include <limits>
	// 优先级数字设为最小，那么具有最高优先级，最后参数设为true，则触摸会被这里吞掉，下面的层不会接收到触摸事件
	CCLog("register with touch dispatcher....");
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( this, (std::numeric_limits<int>::min()), true);
	CCLayer::registerWithTouchDispatcher();

}

//按一下 就 返回继续游戏
//TODO 存档

bool UpgradeScene::ccTouchBegan(CCTouch* touch, CCEvent* event) {

	CCLog("CC touch begin");
	// 因为回调调不到了，所以resume写在了这里
//	CCRect rect = menu->getChildByTag(10)->boundingBox();
//	if (rect.containsPoint(touch->getLocation())) {
//		CCLog("touch play");
	removeFromParent();
		CCDirector::sharedDirector()->resume();
//        SimpleAudioEngine::sharedEngine()->resumeAllEffects();
//        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//		removeFromParent();
//	}
	return true;

}

void UpgradeScene::ccTouchMoved(CCTouch* touch, CCEvent* event) {

}

void UpgradeScene::ccTouchEnded(CCTouch* touch, CCEvent* event) {

}

//    void doPause();
void UpgradeScene::doResume(CCObject *pSender) {

}
