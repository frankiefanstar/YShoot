/*
 * PopLayer.h
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#ifndef POPLAYER_H_
#define POPLAYER_H_

#include <cocos2d.h>
USING_NS_CC;

/**
*  用于窗口跟主界面交互类
**/
class DialogDelegate {
public:
	virtual void clickClose(void) = 0;
};


class PopLayer : public CCLayer{
public:
//	PopLayer();
//	virtual ~PopLayer();

	static CCScene* scene();
	virtual bool init();

	CREATE_FUNC(PopLayer);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	/** 关闭按钮点击时间响应函数*/
	void menuCloseCallback(CCObject*);

	/** 窗口关闭响应函数*/
	void setDelegate(DialogDelegate* delegates);

private:
	CCLayerColor* child;
	DialogDelegate* dele;

};

#endif /* POPLAYER_H_ */
