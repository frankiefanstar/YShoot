/*
 * GameLayer.cpp
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#include "GameLayer.h"
#include "Entity/Bullet.h"
#include "MenuScene.h"
#include "UpgradeScene.h"
#include <sstream>
#include "Config/resource.h"
#include "Layer/PopLayer.h"
#include "Layer/PopDialog.h"
#include "Layer/PassDialog.h"

GameLayer::GameLayer() {
	m_time = 0;
	m_hero = NULL;
	m_tempScore = 0;
	//m_time(0),m_ship(NULL),m_backSky(NULL),m_backSkyHeight(0),m_backSkyRe(NULL),m_backTileMap(NULL),m_backTileMapHeight(0),m_backTileMapRe(NULL),m_isBackSkyReload(false),m_isBackTileReload(false),m_lbScore(NULL),m_lifeCount(NULL),
//	    m_tempScore(0)
}

GameLayer::~GameLayer() {
	if (gameManager) {
		delete gameManager;
	}

	play_bullet->release();
	enemy_bullet->release();
	enemy_items->release();
}

CCScene* GameLayer::scene() {
	CCScene *scene = CCScene::create();

	GameLayer *layer = GameLayer::create();

	scene->addChild(layer);
	return scene;
}

bool GameLayer::init() {

	if (!CCLayer::init()) {
		return false;
	}
	// 开启触摸
	this->setTouchEnabled(true);

	play_bullet = CCArray::create();
	play_bullet->retain();
	enemy_bullet = CCArray::create();
	enemy_bullet->retain();
	enemy_items = CCArray::create();
	enemy_items->retain();

	//保证config初始化
//	Config::sharedConfig()->init();

	m_state = statePlaying;  //设置游戏状态为开始

	winSize = CCDirector::sharedDirector()->getWinSize();
	m_screenRec = CCRectMake(0, 0, winSize.width, winSize.height + 10);

	//初始化背景
	initBackground();

	initMenu();
	initUI();

	//生成Hero
	m_hero = Hero::create();
//	 m_hero->retain();
	addChild(m_hero, m_hero->getZOrder(), TAG_HERO);

	//---------------TODO 生成敌人------------------------

	gameManager = new GameManager(this);

	// 自动每周期调 内部的update函数
//	 schedule(schedule_selector(GameLayer::updateTime), 1);
	scheduleUpdate();
	schedule(schedule_selector(GameLayer::updateEnemy), 1);

	//TODO 每周期更新UI

	//TODO 加Music

	return true;
}

//没周期更新 检查
void GameLayer::update(float dt) {
	if (m_state == statePlaying) {
		checkIsCollide();
		removeInactiveUnit(dt);
		updateGameState();   //更新游戏状态,Hero的生命数量 判断是否GameOver
		updateUI(); //更新Score 和 生命条数
		checkIsUpgrade();
	}

}

void GameLayer::initBackground() {
	m_background = CCSprite::create("back_back.jpg");
	m_background->retain();
	m_background->setAnchorPoint(ccp(0, 0));
	m_background->setPosition(ccp(0,0));
	m_backgroundHeight = m_background->getContentSize().height;
	m_backgroundReload = false;  //标志位

	this->addChild(m_background, ORDER_BACKGROUND);

	//每周期update
	schedule(schedule_selector(GameLayer:: movingBackground), 1);
}

void GameLayer::movingBackground() {

	m_background->runAction(CCMoveBy::create(1, ccp(0, -48)));
	m_backgroundHeight -= 48;

	if(m_backgroundHeight <= winSize.height) {
		if(!m_backgroundReload) {
			m_backgroundRe = CCSprite::create("back_back.jpg");
			m_backgroundRe->retain();
			m_backgroundRe->setAnchorPoint(ccp(0, 0));
			addChild(m_backgroundRe, ORDER_BACKGROUND);
			m_backgroundRe->setPosition(ccp(0, winSize.height));
			m_backgroundReload = true;
		}
		m_backgroundRe->runAction(CCMoveBy::create(3, ccp(0, -48)));
	}

	if(m_backgroundHeight <= 0 ) {
		m_backgroundHeight = winSize.height;
		this->removeChild(m_background, true);
		m_background = m_backgroundRe;
		m_backgroundRe = NULL;
		m_backgroundReload = false;
	}

}

//初始化游戏中的菜单项
void GameLayer::initMenu() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemFont::setFontName("monaco.ttf");
	CCMenuItemFont::setFontSize(40);
	CCMenuItemFont* pause = CCMenuItemFont::create("Pause", this,
			menu_selector(GameLayer::doPause));
	pause->setAnchorPoint(ccp(0, 0));
	pause->setPosition(
			ccp((winSize.width - pause->getContentSize().width),(winSize.height/2 + 100)));

	CCMenuItemFont* resume = CCMenuItemFont::create("Resume", this,
			menu_selector(GameLayer::doResume));
	resume->setAnchorPoint(ccp(0, 0));
	resume->setPosition(
			ccp((winSize.width - resume->getContentSize().width),(winSize.height/2 )));

	CCMenuItemFont* back = CCMenuItemFont::create("Back", this,
			menu_selector(GameLayer::doBackHome));
	back->setAnchorPoint(ccp(0, 0));
	back->setPosition(
			ccp((winSize.width - back->getContentSize().width),(winSize.height/2 - 100 )));
	CCMenu* gameMenu = CCMenu::create(pause, resume, back, NULL);
	gameMenu->setPosition(CCPointZero);
	this->addChild(gameMenu, 1);

}

void GameLayer::initUI() {
	//Init HP
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_hpShow = CCLabelTTF::create("HP: 0", "monaco.ttf", 35);
	m_hpShow->setAnchorPoint(ccp(0, 0));
	m_hpShow->setPosition(ccp((0),(winSize.height/2 +100)));
	this->addChild(m_hpShow, 1);
	//init Energy
	m_energyShow = CCLabelTTF::create("Score: 0", "monaco.ttf", 35);
	m_energyShow->setAnchorPoint(ccp(0, 0));
	m_energyShow->setPosition(ccp((0),(winSize.height/2 -0-50)));
	this->addChild(m_energyShow, 1);
}

//更新系统时间 可以整合
void GameLayer::updateTime() {
	m_time++;
}

//每周期更新时间以及enemy
void GameLayer::updateEnemy() {
	if (m_state == statePlaying) {
		//根据时间来load enemy
		m_time++;
		gameManager->loadLevelResource(m_time);
	}
}

// 每个周期检测碰撞
void GameLayer::checkIsCollide() {
	CCObject *units;
	CCObject *bullets;
	CCObject *enemybs;

	//Hero的子弹
	CCARRAY_FOREACH(enemy_items, units) {
		AdvanceSprite *enemy = dynamic_cast<AdvanceSprite*>(units);
		CCARRAY_FOREACH(play_bullet, bullets) {
			AdvanceSprite *bullet = dynamic_cast<AdvanceSprite*>(bullets);
			//检查 enemy是否和hero的子弹相撞
			if (isCollision(enemy, bullet)) {
				enemy->hurt();
				bullet->explode();  //Hero的子弹若有碰撞 产生效果
				bullet->hurt();

			}

		}
		if (isCollision(enemy, m_hero)) {
			if (m_hero->isActive()) {
				enemy->hurt();
				m_hero->hurt();
			}
		}
	}

	//敌人的子弹
	CCARRAY_FOREACH(enemy_bullet, enemybs) {
		AdvanceSprite *enemyb = dynamic_cast<AdvanceSprite*>(enemybs);
		if (enemyb) {
			if (isCollision(enemyb, m_hero)) {
				if (m_hero->isActive()) {
					enemyb->hurt();
					m_hero->hurt();
				}
			}

		}
	}

	//------------------------------判断是否超出屏幕
	//敌人
	CCARRAY_FOREACH(enemy_items, units) {
		AdvanceSprite *enemy = dynamic_cast<AdvanceSprite*>(units);
		//敌人超出屏幕
		if (!(m_screenRec.intersectsRect(enemy->boundingBox()))) {
			enemy->destroy();
		}
	}

	//hero的子弹
	CCARRAY_FOREACH(play_bullet, bullets) {
		AdvanceSprite* bullet = dynamic_cast<AdvanceSprite*>(bullets);
		if (!(m_screenRec.intersectsRect(bullet->boundingBox()))) {
			bullet->destroy();
		}
	}

	// enemy bullet
	CCARRAY_FOREACH(enemy_bullet, enemybs) {
		AdvanceSprite *enemyb = dynamic_cast<AdvanceSprite*>(enemybs);
		if (!m_screenRec.intersectsRect(enemyb->boundingBox())) {
			enemyb->destroy();
		}
	}

}

//判断两实体是否相撞
bool GameLayer::isCollision(AdvanceSprite* a, AdvanceSprite* b) {
	if (!a || !b) {
		return false;
	}
	CCRect rect_a = a->collideRect();
	CCRect rect_b = b->collideRect();
	if (rect_a.intersectsRect(rect_b)) {
		return true;
	}
	return false;
}

void GameLayer::removeInactiveUnit(float dt) {
	CCArray *children = this->getChildren();
	for (int i = 0; i < children->count(); ++i) {
		CCSprite *selChild = dynamic_cast<CCSprite*>(children->objectAtIndex(i));
		if (selChild) {
			//FIXME  Child 是否需要 update,因为初始化的时候我已经设置过update了
//            selChild->update(dt);  //根据HP 检测自己是否active
			int tag = selChild->getTag();
			if ((tag == TAG_ENEMY_BULLET) || (tag == TAG_HERO_BULLET)
					|| (tag == TAG_ENEMY)) {
				//如果生命值小于0 则销毁
				if (!((AdvanceSprite*) selChild)->isActive()) {
					((AdvanceSprite*) selChild)->destroy();
				}
			}
		}
	}

	if (m_hero) {
		if (!m_hero->isActive()) {
			m_hero->destroy();  //config 中 life 数目 --
			m_hero = NULL;
		}
	}
}

void GameLayer::updateGameState() {
	if (Config::sharedConfig()->getLifeCount() > 0) {
//		CCLog("我还有命 %d %d",Config::sharedConfig()->getLifeCount(), 1);
		if (!m_hero) {
			//TODO 增加一些衔接的东西
			m_hero = Hero::create();
			this->addChild(m_hero, m_hero->getZoder(), 1001);
		}

	}
	//如果没有命了  就Game Over
	else if (Config::sharedConfig()->getLifeCount() <= 0) {
		CCLog("update Game State... Game to be over");
		m_state = stateGameOver;
		m_hero = NULL;
		CCCallFunc *gameOver = CCCallFunc::create(this,
				callfunc_selector(GameLayer::gameOver));
		this->runAction(
				CCSequence::create(CCDelayTime::create(0.4), gameOver, NULL));
	}
}

//检查是否闯关成功
void GameLayer::checkIsUpgrade() {
	//检查游戏状态
	if (m_state == statePlaying) {
		//查看分数
		int score = m_tempScore;
		if (score >= 100) {

			doUpgrade();
		}
		//TODO 跳出升级成功画面(军衔 )

	}
}

void GameLayer::updateUI() {
	if (m_tempScore < Config::sharedConfig()->getScoreValue()) {
		m_tempScore += 5;
//	        CCLog("Now Score: %d", m_tempScore);
	}
	if (m_hero) {
		char temp_hp[20];
		char s1[] = "HP:";
		sprintf(temp_hp, "%d", m_hero->getHP());
		m_hpShow->setString(strcat(s1, temp_hp));
//		CCLog("Now Hp: %d", getHero()->getHP());

		char temp_score[20];
		char s2[] = "Score:";
		sprintf(temp_score, "%d", m_tempScore);
		m_energyShow->setString(strcat(s2, temp_score));
//		CCLog("Now Hp: %d", getHero()->getHP());
	}

}

void GameLayer::onEnter() {
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCLayer::onEnter();
}

void GameLayer::onExit() {
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

//注册
//void GameLayer::registerWithTouchDispatcher() {
////	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

bool GameLayer::ccTouchBegan(CCTouch *touch, CCEvent *event) {
//    CCLog("touch began!");
	return true;
}

void GameLayer::ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
	if ((m_state == statePlaying) && m_hero) {
		CCPoint pos = touch->getDelta();
		CCPoint currentPos = m_hero->getPosition();
		currentPos = ccpAdd(currentPos, pos);
		currentPos = ccpClamp(currentPos, CCPointZero,
				ccp(winSize.width, winSize.height));
		m_hero->setPosition(currentPos);
	}

}

void GameLayer::ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event) {
//    CCLog("touch end!");
}

//游戏结束
void GameLayer::gameOver() {
	CCScene * scene = GameOver::scene();
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFade::create(1.2, scene));
}

//暂停游戏
void GameLayer::doPause(CCObject *pSender) {
	CCDirector::sharedDirector()->pause();
//    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//    PauseLayer *pauseLayer = PauseLayer::create();
//    addChild(pauseLayer,9999);
}

void GameLayer::doUpgrade() {


	if(shouldPop == false) {
	CCDirector::sharedDirector()->pause();

//	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(mControlsMenu);
//    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
//    CCScene *upgradeeLayer = UpgradeScene::scene();
//    addChild(upgradeeLayer,9999);
//    CCDirector::sharedDirector()->replaceScene(PopLayer::scene());
//    CCDirector::sharedDirector()->replaceScene(PopDialog::scene());
//	CCLayerColor* layer = PopDialog::create();
//	this->addChild(layer, 100000);



	CCLayerColor* layer = PassDialog::create();
	this->addChild(layer, 9999);
	shouldPop = true;
	}


}

//恢复游戏
void GameLayer::doResume() {
	CCDirector::sharedDirector()->resume();
}

//回到首页
void GameLayer::doBackHome() {
	CCDirector::sharedDirector()->replaceScene(MenuScene::scene());
}

Hero* GameLayer::getHero() {
	return m_hero;
}

void GameLayer::doResumeGame() {
	CCDirector::sharedDirector()->resume();
}
