/*
 * Hero.cpp
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#include "Hero.h"
#include "Bullet.h"
#include "Config/Config.h"
#include "Effect/Effect.h"


Hero::Hero() {
	m_speed = 220;
	m_bulletSpeed = 900;  //FIXME 子弹速度
	m_HP = 50;  //生命值
	m_bulletTypeValue = 1;
//			m_bulletPowerValue(1);
//			m_throwBombing(false);
	m_canBeAttack = true;
////			m_isThrowBomb(false);
	m_zOder = 3000;
//			m_maxBulletPowerValue(4);
	m_appearPosition = ccp(160, 60);  //出现的位置
//			m_hurtColorLife(0);
	m_active = true;    //初始化后处于active 状态

}

Hero::~Hero() {

}

bool Hero::init()
{
    // super init first
    if ( !CCSprite::init() )
    {
        return false;
    }

    // init life
    CCTexture2D * heroTextureCache = CCTextureCache::sharedTextureCache()->addImage(s_hero);
    CCRect rec = CCRectMake(0, 0, 96, 96);
    this->initWithTexture(heroTextureCache,  rec);

    this->setPosition(m_appearPosition);
//
//
//    // set frame
//    CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(shipTextureCache, CCRectMake(0, 0, 60, 38));
//    CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(shipTextureCache, CCRectMake(60, 0, 60, 38));
//
//    CCArray *animFrames = CCArray::create();
//    animFrames->addObject(frame0);
//    animFrames->addObject(frame1);
//
//    // ship animate
//    // 这个方法有差异
//    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
//    CCAnimate *animate = CCAnimate::create(animation);
//    this->runAction(CCRepeatForever::create(animate));
//
    // 子弹发射
    this->schedule(schedule_selector(Hero::shoot), 0.15);
    this->schedule(schedule_selector(Hero::smartMove), 1);
//
//    // revive effect
//    this->m_canBeAttack = false;
//    CCSprite *ghostSprite = CCSprite::createWithTexture(shipTextureCache, CCRectMake(0, 45, 60, 38));
//    ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
//    ghostSprite->setBlendFunc(cbl);
//    ghostSprite->setScale(8);
//    ghostSprite->setPosition(ccp(this->getContentSize().width / 2, 12));
//    this->addChild(ghostSprite, 3000, 99999);
//    ghostSprite->runAction(CCScaleTo::create(0.5, 1, 1));
//
//    // 闪烁动画
//    CCBlink *blinks = CCBlink::create(3, 9);
//
//    // 回调，攻击使能
//    // 带执行者回调，谁执行Action传谁。这里是this执行的动作，所以传的就是this
//    CCCallFuncN *makeBeAttack = CCCallFuncN::create(this, callfuncN_selector(Ship::makeAttack));
//
//    this->runAction(CCSequence::create(CCDelayTime::create(0.5), blinks, makeBeAttack, NULL));

    return true;

}


//每周期检测
void Hero::update(float dt)
{

    if (m_HP <= 0) {
        m_active = false;
    }

}


//产生碰撞
void Hero::makeAttack(CCNode * pSender)
{
//    CCLog("pSend tag %d",pSender->getTag());
    this->m_canBeAttack = true;
    this->setVisible(true);
    pSender->removeChildByTag(99999);
    CCLog("make Attack !");

}


void Hero::shoot(float dt)
{

	int offset = 13;
	CCPoint position = this->getPosition();
	CCSize contentSize = this->getContentSize();
	Bullet * bullet_a = Bullet::create(3, "bullet.png", 1);
//    Bullet *bullet_a = new Bullet(3, "bullet.png", 1);
	if (bullet_a) {
		//FIXME
//        bullet_a->autorelease();
		//添加到hero bullet列表中
		play_bullet->addObject(bullet_a);
		this->getParent()->addChild(bullet_a, bullet_a->m_zorder,
				TAG_HERO_BULLET);
		bullet_a->setPosition(
				ccp(position.x + offset, position.y + 3 + contentSize.height * 0.3));

			} else {
				delete bullet_a;
				bullet_a = 0;
			}

}

//hp自我减少1
void Hero::hurt()
{
    if (m_canBeAttack) {
        CCLog("under fire!");
        m_HP--;
        //TODO 被袭击之后颜色变化
//        this->setColor(ccc3(255, 0, 0));
    }

}


//
void Hero::destroy()
{
    CCLOG("destroy one Hero");
    //生命数量减少1
    //FIXME
    Config::sharedConfig()->updateLifeCount();

//    CCLOG("life count is %d",Config::sharedConfig()->getLifeCount());

//    Effect *effect = Effect::create();
//
//    effect->explode(this->getParent(), this->getPosition());
//
//    this->removeFromParent();

    if (Config::sharedConfig()->getAudioState()){
    	//TODO 播放音效
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(s_shipDestroyEffect);
    }
}


//FIXME 修改 collideRect
CCRect Hero::collideRect()
{
    CCPoint pos = getPosition();
    CCSize cs = getContentSize();

    return CCRectMake(pos.x - cs.width / 2 , pos.y - cs.height / 2, cs.width, cs.height / 2);
}


bool Hero::isActive()
{
	if(m_HP<=0) {
		m_active = 	false;
	}
    return m_active;
}


// Hero智能移动
void Hero::smartMove( ) {
	CCPoint location = this->getPosition();
	float x = location.x;
	float y = location.y;
	float delta_x ;
	float delta_y;
	float isPlus = CCRANDOM_0_1();
//	CCLog("random %f", isPlus);
	if(isPlus>=0.5) {
		delta_x = 10*CCRANDOM_0_1();
		delta_y = 10*CCRANDOM_0_1();
	}else {
		 delta_x = -10*CCRANDOM_0_1();
		 delta_y = -10*CCRANDOM_0_1();
	}

	this->setPosition(ccp(x+delta_x, y+ delta_y));


}

int Hero::getZoder()
{
    return m_zOder;
}


int Hero::getHP() {
	if(m_active) {
		return m_HP;
	}else
		return 0;
}

void Hero::explode() {

}
