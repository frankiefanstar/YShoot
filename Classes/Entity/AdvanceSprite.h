/*
 * AdvanceSprite.h
 *
 *  Created on: 2012-11-4
 *      Author: arch
 */

#ifndef ADVANCESPRITE_H_
#define ADVANCESPRITE_H_

#include <cocos2d.h>
//using namespace cocos2d;
USING_NS_CC;


class CostomeKeyPadDelegae : public CCKeypadDelegate , public CCNode{

public:
    virtual void keyBackClicked();
};


class AdvanceSprite : public CCSprite
{
public:
	AdvanceSprite();

	virtual ~AdvanceSprite();

    virtual void destroy() = 0;
    virtual void hurt() = 0 ;
    virtual CCRect collideRect() = 0;
    virtual bool isActive() = 0;
    virtual  void explode() = 0;

private:

};

#endif /* ADVANCESPRITE_H_ */
