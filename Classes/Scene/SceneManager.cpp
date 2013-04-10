/*
 * SceneManager.cpp
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#include "SceneManager.h"
//各个场景
#include "MenuScene.h"
#include "GameLayer.h"
#include "AboutScene.h"
#include "GameOver.h"

void SceneManager::loadScene(SceneType type) {

	switch (type) {
	case GAME_SCENE:
		CCLog("GO TO GAME SCENE");
//		CCDirector::sharedDirector()->replaceScene(
//				CCTransitionMoveInR::create(1.2f, GameLayer::scene()));
		CCDirector::sharedDirector()->replaceScene(
				CCTransitionPageTurn::create(1.2f, GameLayer::scene(), false));
		break;
	case ABOUT_SCENE:
		CCLog("About Scene");
		CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1.2, AboutScene::scene()));
		break;
	case EXIT:
		CCLog("exit");
		CCDirector::sharedDirector()->end();
		break;

	case SETTING:
		CCLog("go to setting scene");
		//
		break;

	case HOME:
		CCLog("back to home");
		CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
		break;
	case GAMEOVER:
		CCLog("go to Game Over Scene..................");
		CCDirector::sharedDirector()->replaceScene(
				CCTransitionFade::create(1.2f, GameOver::scene()));
		break;

	default:
		CCLog("Can not find any Scene.....................");
		break;
	}

}
