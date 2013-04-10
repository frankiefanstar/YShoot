/*
 * SetScene.h
 *
 *  Created on: 2013-3-25
 *      Author: rescue01
 */

#ifndef SETSCENE_H_
#define SETSCENE_H_


#include <cocos2d.h>
USING_NS_CC;

class SetScene  : public CCLayer{

public:
	SetScene();

    virtual bool init();

    static CCScene* scene();

    void menuBackCallback(CCObject* pSender);

    CREATE_FUNC(SetScene);

};


#endif /* SETSCENE_H_ */
