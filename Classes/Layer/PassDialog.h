/*
 * PassDialog.h
 *
 *  Created on: 2013-4-11
 *      Author: rescue01
 */

#ifndef PASSDIALOG_H_
#define PASSDIALOG_H_

#include <cocos2d.h>
#include "DialogLayer.h"
USING_NS_CC;

/*
 * 弹出通关对话框
 *
 */

class PassDialog : public DialogLayer{

public:
    virtual bool onInitDialog();

    CREATE_FUNC(PassDialog);

public:
    /** 确认和退出按钮 */
    void okMenuItemCallback(CCObject *obj);
    void cancelMenuItemCallback(CCObject *obj);

};

#endif /* PASSDIALOG_H_ */
