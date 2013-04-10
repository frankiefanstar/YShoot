/*
 * NewMenuScene.h
 *
 *  Created on: 2012-9-15
 *      Author: arch
 */

#ifndef MENUSCENE_H_
#define MENUSCENE_H_

#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include <string.h>

using namespace std;


using namespace cocos2d;
using namespace CocosDenshion;


class MenuScene : public cocos2d::CCLayer
{
private:

	void initBackground();
    void initMenu();


public:
    virtual bool init();
    static cocos2d::CCScene* scene();

    void menuCloseCallback(CCObject* pSender);
    void menuAboutCallback(CCObject* pSender);
    void menuGameCallback(CCObject* pSender);
    void menuSetCallback(CCObject* pSender);
    void menuGameOverCallback(CCObject* pSender);

    CREATE_FUNC(MenuScene);


};

#endif /* NEWMENUSCENE_H_ */
