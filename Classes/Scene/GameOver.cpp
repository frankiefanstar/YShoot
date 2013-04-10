/*
 * GameOver.cpp
 *
 *  Created on: 2013-1-5
 *      Author: rescue01
 */

#include "GameOver.h"
#include "SceneManager.h"

using namespace cocos2d;

GameOver::GameOver() {

}

GameOver::~GameOver() {

}

CCScene* GameOver::scene() {
    CCScene *scene = CCScene::create();
    GameOver *layer = GameOver::create();
    scene->addChild(layer);

    return scene;
}



bool GameOver::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemFont::setFontSize(70);
	//显示Game Over
	CCLabelTTF* overLabel = CCLabelTTF::create("GameOver !!!", "Arial", 80);
	overLabel->setPosition(ccp(winSize.width/2, winSize.height/2 + 80 ));  //should ccp
	this->addChild(overLabel, 1);

	//显示 Share
	CCMenuItemFont *shareMenu = CCMenuItemFont::create("Share");  //TODO 回调函数
	shareMenu->setPosition(winSize.width/2, (winSize.height/2-60));

	//Back to Home Menu
	CCMenuItemFont *backToMenu = CCMenuItemFont::create("Back", this, menu_selector(GameOver::menuBackCallback));
	backToMenu->setPosition(winSize.width*0.7, (winSize.height*0.1));

	CCMenu* menu = CCMenu::create(shareMenu, backToMenu, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);
	//

	return true;
}





//返回到主菜单界面
void GameOver::menuBackCallback(CCObject* pSender) {
	SceneManager::loadScene(HOME);
}

