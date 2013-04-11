/*
 * DialogLayer.h
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#ifndef DIALOGLAYER_H_
#define DIALOGLAYER_H_

#include <cocos2d.h>
USING_NS_CC;

class DialogLayer: public CCLayerColor {

public:
    DialogLayer();
    virtual ~DialogLayer();

public:
    /** 初始化对话框 */
    virtual bool onInitDialog() = 0;

    /** 所有的菜单按钮压入到容器中 */
    void pushMenu(CCMenuItem *pMenu);

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

private:
    /** 初始化菜单 将菜单添加到模态对话框上*/
    bool initMenu();

private:
    CCMenu *mMenu;             // 模态对话框菜单
    CCArray *mMenuItemArray;   // 所有菜单
    bool mTouchedMenu;                  // 记录菜单点击

};

#endif /* DIALOGLAYER_H_ */
