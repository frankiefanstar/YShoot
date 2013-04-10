/*
 * GameManager.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: rescue01
 */

#include "GameManager.h"
#include "Entity/Enemy.h"

GameManager::GameManager(CCLayer* gameLayer) {
	CCAssert(gameLayer != NULL, "game layer must be non-null");
	//指向layer
	m_gameLayer = gameLayer;
	//初始化Enemy
	m_enemies = Config::sharedConfig()->getEnemies();
	m_enemyType = Config::sharedConfig()->getEnemyType();

}



GameManager::~GameManager() {

}

void GameManager::loadLevelResource(int dt) {
	//Vector 类型
	for (vector<EnemyInfo>::iterator iter = m_enemies.begin(); iter != m_enemies.end(); ++iter) {
		if (iter->showType == "Repeat") {  //重复出现类型
			if (dt % iter->showTime == 0 && dt%10==0) {
				// 数组长度
				for (int i = 0; i != 3; ++i) {
					addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
	}
}


//把敌人加到图层上
void GameManager::addEnemyToGameLayer(int type) {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    EnemyType enemyType = m_enemyType[type];
    Enemy * enemy = Enemy::create(enemyType);

    CCPoint enemyPos = ccp( 80 + (winSize.width - 160) * CCRANDOM_0_1(), winSize.height);
    CCSize eSize = enemy->getContentSize();
    enemy->setPosition(enemyPos);
//    CCLog("%s", "设置位置了");
//
    CCPoint offset; //= ((GameLayer*)m_gameLayer)->getShip()->getPosition();
    CCAction *tempAction; //= CCMoveTo::create(1, offset);
    CCMoveBy *a0;
    CCMoveBy *a1;
    CCCallFuncN *onComplete;

    switch (enemy->getMoveType()) {
        case 0:
            if (((GameLayer*)m_gameLayer)->getHero()) {
                offset = ((GameLayer*)m_gameLayer)->getHero()->getPosition();
            }else{
                offset = ccp(winSize.width / 2, 0);
            }
            tempAction = CCMoveTo::create(1, offset);
            break;

        case 1:
            offset = ccp(0, -winSize.height - eSize.height);
            tempAction = CCMoveBy::create(4, offset);
            break;

        case 2:
            offset = ccp(0, -100 - 200 * CCRANDOM_0_1());
            a0 = CCMoveBy::create(0.5, offset);
            a1 = CCMoveBy::create(1, ccp(-50 - 100 * CCRANDOM_0_1(), 0));

            onComplete =  CCCallFuncN::create(enemy, callfuncN_selector(GameManager::repeatAction));
            tempAction = CCSequence::create(a0, a1, onComplete, NULL);
            break;

        case 3:
            int newX = (enemyPos.x <= winSize.width / 2 ) ? 320 : - 320;
            a0 = CCMoveBy::create(4, ccp(newX, -240));
            a1 = CCMoveBy::create(4, ccp(-newX, -320));
            tempAction = CCSequence::create(a0, a1, NULL);
            break;

    }
//
    m_gameLayer->addChild(enemy,enemy->getZOrder(), 1000);
    enemy_items->addObject(enemy);
    enemy->runAction(tempAction);
}

//TODO 重复动作?
void GameManager::repeatAction(CCNode *pSender) {
	CCDelayTime *delay = CCDelayTime::create(1);
	CCMoveBy *mv = CCMoveBy::create(1, ccp(100 + 100 * CCRANDOM_0_1(), 0));
	CCFiniteTimeAction *seq = CCSequence::create(delay, mv, delay->copy(),
			mv->reverse(), NULL);
	pSender->runAction(CCRepeatForever::create((CCActionInterval*) seq));
}


void GameManager::removeSprite(CCSprite* pSender) {
	this->m_gameLayer->removeChild(pSender);
}
