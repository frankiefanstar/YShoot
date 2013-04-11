/*
 * PauseLayer.h
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#ifndef PAUSELAYER_H_
#define PAUSELAYER_H_

#include <cocos2d.h>
#include "DialogLayer.h"
USING_NS_CC;

class PauseLayer : public DialogLayer{

public:
    virtual bool onInitDialog();
    CREATE_FUNC(PauseLayer);

public:
    /** 确认和退出按钮 */
    void okMenuItemCallback(CCObject *obj);
    void exitMenuItemCallback(CCObject *obj);

};

#endif /* PAUSELAYER_H_ */
