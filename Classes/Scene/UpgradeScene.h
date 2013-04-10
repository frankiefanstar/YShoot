/*
 * UpgradeScene.h
 *
 *  Created on: 2013-3-25
 *      Author: rescue01
 */

#ifndef UPGRADESCENE_H_
#define UPGRADESCENE_H_
#include <cocos2d.h>
USING_NS_CC;


class UpgradeScene : public CCLayerColor{
public:
	virtual bool init();
	static CCScene* scene();
	virtual void registerWithTouchDispatcher();

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	//    void doPause();
	void doResume(CCObject *pSender);CREATE_FUNC(UpgradeScene);

};

#endif /* UPGRADESCENE_H_ */
