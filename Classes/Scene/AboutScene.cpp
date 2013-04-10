#include <cocos2d.h>
#include "AboutScene.h"
#include "MenuScene.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene* AboutScene::scene()
{
    CCScene* scene = CCScene::create();
    AboutScene* layer = AboutScene::create();

    scene->addChild(layer);
    return scene;
}

bool AboutScene::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }

    //--------------------------
    //加入简介和图片

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCTexture2D *imageCache = CCTextureCache::sharedTextureCache()->addImage("Night-Vision_01.png");
//        CCSprite *title = CCSprite::createWithTexture(imageCache, CCRectMake(0, 36, 100, 34));
        CCSprite *title = CCSprite::createWithTexture(imageCache );
        title->setPosition(ccp(winSize.width/2, winSize.height/2 +200));
        addChild(title);

        CCLabelTTF *about = CCLabelTTF::create( " I am jasonllinux. \n  \n jasonllinux@gmail.com", "Monaco", 35, CCSizeMake(winSize.width * 0.85, 320), kCCTextAlignmentCenter);
//
        about->setPosition(ccp(winSize.width / 2, winSize.height / 2 -200));
        about->setAnchorPoint(ccp(0.5, 0.5));
        addChild(about);
//
        CCMenuItemImage* goBack = CCMenuItemImage::create("rrow.png","rrow.png", this, menu_selector(AboutScene::menuBackCallback));
//        CCMenuItemImage* image = CCMenuItemImage::cre
//        CCLabelBMFont *backLb = CCLabelBMFont::create("Go Back");
//        CCMenuItemLabel *goBack = CCMenuItemLabel::create(backLb, this, menu_selector(AboutScene::menuBackCallback));
//        goBack->setScale(0.6);
//        CCActionInterval *fadeIn = CCFadeTo::create(1, 80);
//        CCActionInterval *fadeOut = CCFadeTo::create(1, 255);
//        CCEaseSineInOut *ease1 = CCEaseSineInOut::create(fadeIn);
//        CCEaseSineInOut *ease2 = CCEaseSineInOut::create(fadeOut);
//        CCFiniteTimeAction *seq = CCSequence::create(ease1, ease2, NULL);
//        // 参数必须要强转，不然ndk编译不过
//        goBack->runAction(CCRepeatForever::create((CCActionInterval*)seq));

        CCMenu *menu = CCMenu::create(goBack, NULL);
        menu->setPosition(winSize.width / 2, 70);
        addChild(menu);

    return true;

}


void AboutScene::menuBackCallback(CCObject* pSender)
{

	CCScene *scene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));

}



