/*
 * Enemy.cpp
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#include "Enemy.h"
#include "Config/resource.h"

Enemy::Enemy() {
	m_active = true;
	m_speed = 200;
	m_bulletSpeed = -200;
	m_HP = 1;
	m_bulletPowerValure = 1;
	m_moveType = 0;
	m_scoreValue = 200;
	m_zOrder = ORDER_ENEMY;
	m_delayTime = 1 + 1.2*CCRANDOM_0_1();
	m_attackMode = 1;

}

Enemy::~Enemy() {

}

/**自己的create函数，因为要带参数，那个子弹类也可以这么写*/
Enemy* Enemy::create(EnemyType type)
{
    Enemy *pRet = new Enemy();
    if (pRet && pRet->enemyInit(type)) {
    	//FIXME
//        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Enemy::enemyInit(EnemyType type)
{
    if ( !CCSprite::init() )
    {
        return false;
    }

    m_HP = type.hp;
    m_moveType = type.moveType;
    m_scoreValue = type.scoreValue;
	CCTexture2D * enemytexture = CCTextureCache::sharedTextureCache()->addImage("life.png");
	this->initWithTexture(enemytexture);
//    this->initWithSpriteFrameName(type.textureName.c_str());
    this->schedule(schedule_selector(Enemy::shoot),this->m_delayTime);

    return true;
}

void Enemy::update(float dt)
{
    if (m_HP < 0) {
        m_active = false;
    }
}


void Enemy::shoot()
{
    CCPoint pos = this->getPosition();
    //TODO  改变子弹的类型具体

    Bullet * bullet = Bullet::create(200, "bullet.png" , 1);
    if(bullet) {
    //FIXME
////    bullet->autorelease();
		enemy_bullet->addObject(bullet);
		bullet->setPosition(ccp(pos.x, pos.y - getContentSize().height * 0.2));
		getParent()->addChild(bullet, m_zOrder, TAG_ENEMY_BULLET);
    }
}

void Enemy::hurt()
{
    m_HP--;
}

void Enemy::destroy()
{

    // 更新分数
    Config::sharedConfig()->setScoreValue(m_scoreValue );

    // 爆炸特效和闪光特效
//    Effect *effect = Effect::create();

//    effect->explode(this->getParent(), getPosition());
//
//    effect->spark(this->getPosition(),this->getParent(), 1.2, 0.7);

    // 敌机爆炸，从敌机数组删除
    enemy_items->removeObject(this);

    // 删除精灵
    this->removeFromParent();
//    CCLog("Enemy is destroyed");

    // 声音
//    if (Config::sharedConfig()->getAudioState()) {
//        SimpleAudioEngine::sharedEngine()->playEffect(s_explodeEffect);
//    }
}

CCRect Enemy::collideRect()
{
    CCSize size = getContentSize();
    CCPoint pos = getPosition();

    return CCRectMake(pos.x - size.width / 2, pos.y - size.height / 4, size.width, size.height / 2);
}

int Enemy::getMoveType()
{
    return m_moveType;
}

bool Enemy::isActive()
{
	if(m_HP<=0) {
		m_active = false;
	}
    return  m_active;
}

void Enemy::sharedEnemy()
{
	//TODO  enemy 开场特效www
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_Enemy_plist, s_enemy);
}

void Enemy::explode() {

}

