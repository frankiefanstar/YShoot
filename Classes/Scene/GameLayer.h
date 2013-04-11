/*
 * GameLayer.h
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#ifndef GAMELAYER_H_
#define GAMELAYER_H_

#include <cocos2d.h>
#include "Entity/Hero.h"
#include "Manager/GameManager.h"
#include "GameOver.h"
#include "Config/Config.h"


USING_NS_CC;


enum State{
    statePlaying = 0,
    stateGameOver = 1,
};


class GameLayer : public CCLayer{
private :
	Hero* m_hero;
	CCSize winSize;
	CCRect m_screenRec;
	State m_state;
	int m_time; //游戏中的时间
	int m_tempScore;   //Score
	//编译错误
	class GameManager* gameManager;

	CCSprite* m_background;
	CCSprite* m_backgroundRe;
	float m_backgroundHeight;
	bool m_backgroundReload;
	//tmp UI Score
	CCLabelTTF *m_hpShow;
	CCLabelTTF *m_energyShow;

	bool shouldPop;

	void initBackground();  //初始化背景图片
	void movingBackground(); //每周期转背景
	void initMenu();
	void initUI();
	void updateEnemy();  //每周期更新enemy
	void updateTime();
	bool isCollision(AdvanceSprite *a, AdvanceSprite* b);
	void checkIsCollide();
	void removeInactiveUnit(float dt);
	void updateGameState();
	void updateUI();
	void checkIsUpgrade();
	void doUpgrade();
	void gameOver();
	void doPause(CCObject *pSender);
	void doResume();
	void doBackHome();
public:
	GameLayer();
	virtual ~GameLayer();
	static CCScene* scene();

	virtual bool init();
	virtual void update(float dt);
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void doResumeGame();
//	virtual void registerWithTouchDispatcher();
	Hero* getHero();
	CREATE_FUNC(GameLayer);



};

#endif /* GAMELAYER_H_ */
