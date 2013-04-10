/*
 * Bullet.cpp
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#include "Bullet.h"
#include <string>
#include "Config/Config.h"
#include "Config/resource.h"
#include "Effect/Effect.h"
using namespace std;


Bullet::Bullet() {
	m_active = true;
	m_velocityx = 0;
	m_velocityy = 20000;
	m_Hp = 1;
	m_zorder = ORDER_BULLET;
	m_power = 1;
}

Bullet::~Bullet() {

}


//初始化作用
bool Bullet::bulletInit(int speed, const char *weapon, int attackMode) {
	// super init first
	if (!CCSprite::init()) {
		return false;
	}


	m_velocityy = -speed;
    m_attackMode = attackMode;

//      CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_bullet_plist);
//      this->initWithSpriteFrameName(weapon);
	CCTexture2D * bullettexture =
			CCTextureCache::sharedTextureCache()->addImage(weapon);
	this->initWithTexture(bullettexture);
//      ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
//      this->setBlendFunc(cbl);

	//每周期循环更新位置
	this->schedule(schedule_selector(Bullet::update), 0.1);

	return true;

}


Bullet* Bullet::create(int speed, const char *weapon, int attackMode)
{

	Bullet *pRet = new Bullet();
	    if (pRet && pRet->bulletInit(speed, weapon, attackMode)) {
	    	//FIXME
//	        pRet->autorelease();
	        return pRet;
	    }
	    else
	    {
	        delete pRet;
	        pRet = NULL;
	        return NULL;
	    }

}

void Bullet::update(float dt) {
	CCPoint position = this->getPosition();
	m_velocityy = -800;
	position.x -= m_velocityx * dt;
	position.y -= m_velocityy * dt;
	setPosition(position);

	if (m_Hp <= 0) {
		m_active = false;
	}
}


void Bullet::hurt() {
	m_Hp--;
}

//
void Bullet::explode() {
	// 子弹爆炸特效
    CCSprite *explode = CCSprite::create("hit.jpg");
    ccBlendFunc cb = {GL_SRC_ALPHA, GL_ONE };
    explode->setBlendFunc(cb);
    explode->setPosition(this->getPosition());
    explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.9);
    getParent()->addChild(explode, ORDER_EXPLODE);
    CCCallFuncN *removeExplode =  CCCallFuncN::create(explode, callfuncN_selector(Bullet::removeExplode));
    explode->runAction(CCScaleBy::create(0.3, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.3), removeExplode, NULL));

}


void Bullet::destroy() {



    //remove bullet from array and parent
	play_bullet->removeObject(this);
	enemy_bullet->removeObject(this);

    this->removeFromParent();
//    CCLog("Bullet is destroyed");

}

void Bullet::removeExplode(CCNode *pSender) {
	pSender->removeFromParent();
}

bool Bullet::isActive() {
	if(m_Hp<=0) {
		m_active = false;
	}

	return m_active;
}

//FIXME 真实的Rect 多少 不确定
CCRect Bullet::collideRect() {
	CCPoint pos = this->getPosition();
//	return CCRectMake(pos.x - 3, pos.y - 3, 6, 6);
	return CCRectMake(pos.x - this->getContentSize().width/2, pos.y-this->getContentSize().height/2, this->getContentSize().width, this->getContentSize().height);
}
