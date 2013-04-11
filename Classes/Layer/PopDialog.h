/*
 * PopDialog.h
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#ifndef POPDIALOG_H_
#define POPDIALOG_H_

#include <cocos2d.h>
USING_NS_CC;


class PopDialog : public CCLayerColor{

public:
	bool init();
	void initDialog();

	static CCScene* scene();
//	CREATE_FUNC(PopDialog);

	void onEnter();
	void onExit();

//	void registerWithTouchDispatcher();
//	bool ccTouchBegan(CCTouch *touch, CCEvent *event);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void okMenuItemCallback(CCObject *pSender);
	void cancelMenuItemCallback(CCObject *pSender);

private :
//	CCMenu* menu;


};

#endif /* POPDIALOG_H_ */
