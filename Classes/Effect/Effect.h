/*
 * Effect.h
 *
 *  Created on: 2013-3-18
 *      Author: rescue01
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include <cocos2d.h>
USING_NS_CC;

class Effect : public CCNode
{

private:
    CCSprite *m_sprite;

public:
    Effect(void);
    ~Effect(void);

    //闪光
    void flareEffect(CCNode* parent, CCCallFunc* callback);

    //爆炸
    void explode(CCNode *parent, CCPoint pos);

    void spark(CCPoint pos, CCNode *parent, float scale, float duration);

    void killSprite(CCNode *pSender);



    static void sharedExplosion();
    static Effect* create();
};

#endif /* EFFECT_H_ */
