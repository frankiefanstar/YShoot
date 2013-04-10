/*
 * GameManager.h
 *
 *  Created on: Mar 7, 2013
 *      Author: rescue01
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <cocos2d.h>
#include "Config/Config.h"
#include "Scene/GameLayer.h"

USING_NS_CC;


class GameManager {
private:
	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemyType;
	CCLayer *m_gameLayer;

public:
	GameManager(CCLayer* gameLayer);
//	GameManager();
	virtual ~GameManager();

    void loadLevelResource(int dt);
    void addEnemyToGameLayer(int type);
    void repeatAction(CCNode *pSender);
    void removeSprite(CCSprite* pSender);
};

#endif /* GAMEMANAGER_H_ */
