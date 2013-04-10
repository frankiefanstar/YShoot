/*
 * SetScene.cpp
 *
 *  Created on: 2013-3-25
 *      Author: rescue01
 */

#include "SetScene.h"
#include "SceneManager.h"

SetScene::SetScene() {

}


CCScene* SetScene::scene() {
    CCScene* scene = CCScene::create();
    SetScene* layer = SetScene::create();

    scene->addChild(layer);
    return scene;
}


bool SetScene::init() {
	if (!CCLayer::init()) {
		return false;
	}

	//TODO 加内容
	//title "Setting "

	//设置声音

	//设置难度


	return true;
}



void SetScene::menuBackCallback(CCObject* pSender) {
	//跳转到首页
	SceneManager::loadScene(HOME);
}

