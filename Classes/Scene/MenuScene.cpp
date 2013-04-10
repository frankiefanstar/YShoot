
#include "MenuScene.h"

#include "SceneManager.h"
#include "AboutScene.h"
#include "GameLayer.h"


CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();

    MenuScene *layer = MenuScene::create();

    scene->addChild(layer);
    return scene;
}


bool MenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    //------Background
    this->initBackground();
    this->initMenu();

    //------Logo
//    string s;
//    string s;


    //-------Menu
//    string

// NEW GAME
//    CCSprite* newGameNormal = CCSprite::create("s_menu1.png", CCRectMake(0, 0, 126*2, 33*2));
//    CCSprite* newGameSelected = CCSprite::create("s_menu1.png", CCRectMake(0, 33*2, 126*2, 33*2));
//    CCSprite* newGameDisabled = CCSprite::create("s_menu1.png", CCRectMake(0, 33*2*2, 126*2, 33*2));
//
//
//    CCMenuItemSprite* newGame = CCMenuItemSprite::create(newGameNormal,
//    		newGameSelected,
//    		newGameDisabled,
//    		this, menu_selector(MenuScene::menuGameCallback));
////SET MENU
//    CCSprite* gameSettingNormal = CCSprite::create("s_menu1.png", CCRectMake(126*2,0,126*2,33*2));
//    CCSprite* gameSettingSelected = CCSprite::create("s_menu1.png",CCRectMake(126*2,33*2,126*2,33*2));
//    CCSprite* gameSettingDisabled = CCSprite::create("s_menu1.png",CCRectMake(126*2,33*2*2,126*2,33*2));
//    CCMenuItemSprite* gameSetting = CCMenuItemSprite::create(gameSettingNormal,
//    		gameSettingSelected,
//    		gameSettingDisabled,
//    		this, menu_selector(MenuScene::menuGameCallback));
////ABOUT MENU
//    CCSprite* aboutNormal = CCSprite::create("s_menu1.png", CCRectMake(126*2*2,0,126*2,33*2));
//    CCSprite* aboutSelected = CCSprite::create("s_menu1.png", CCRectMake(126*2*2,33*2,126*2,33*2));
//    CCSprite* aboutDisabled = CCSprite::create("s_menu1.png", CCRectMake(126*2*2,33*2*2,126*2,33*2));
//    CCMenuItemSprite* about = CCMenuItemSprite::create(aboutNormal,
//    		aboutSelected,
//    		aboutDisabled,
//    		this,menu_selector(MenuScene::menuAboutCallback));
//
//    //TODO 其他类似自己设定
//    CCMenu* menu = CCMenu::create(newGame, gameSetting, about, NULL);
//
//    menu->alignItemsVerticallyWithPadding(30); //垂直间隔
//    this->addChild(menu, 1, 2);
//    menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 80));


//Set font size
//
//    int delta = 200;
//
//
//    //进入游戏
//    CCMenuItemFont *start = CCMenuItemFont::create("Start", this, menu_selector(MenuScene::menuGameCallback));
//    start->setPosition(size.width/2, size.height/2 +delta);
//
//    //退出游戏
//    CCMenuItemFont *exit = CCMenuItemFont::create("Exit", this, menu_selector(MenuScene::menuCloseCallback));
//    exit->setPosition(size.width/2, size.height/2 - 2*delta);
//
//    //关于
//    CCMenuItemFont *about = CCMenuItemFont::create("About", this, menu_selector(MenuScene::menuAboutCallback));
//    about->setPosition(size.width/2, size.height/2 );
//
//    //设置
//     CCMenuItemFont *set = CCMenuItemFont::create("Setting", this, menu_selector(MenuScene::menuCloseCallback));
//     set->setPosition(size.width/2, size.height/2 -delta);
//
//    //总菜单
//    CCMenu* menu = CCMenu::create(start, exit, about, set, NULL);
//    menu->setPosition(CCPointZero);
//    this->addChild(menu, 1);




    return true;
}


void MenuScene::initBackground() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* pSprite = CCSprite::create("logo.png");
    pSprite->setPosition( ccp(winSize.width/2, winSize.height/2) );
    this->addChild(pSprite, 0);
}

void MenuScene::initMenu() {

		    //进入游戏
//	CCMenuItemLabel* test = CCMenuItemLabel::
	CCMenuItemFont::setFontSize(70);
	CCMenuItemFont::setFontName("monaco.ttf");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int delta = 160;

	CCLabelTTF* label = CCLabelTTF::create("Start", "monaco.ttf", 70);
	ccColor3B color = ccc3(255, 255, 255);
	label->setColor(color);
	CCMenuItemLabel* test = CCMenuItemLabel::create(label, this, menu_selector(MenuScene::menuGameCallback));
	//Start
//	CCMenuItemFont *startMenu = CCMenuItemFont::create("Start", this,
//			menu_selector(MenuScene::menuGameCallback));
//	startMenu->setAnchorPoint(ccp(0.5, 0.5));
	test->setPosition(ccp(winSize.width/2, winSize.height/2+delta));


	//Setting
	CCMenuItemFont *setMenu = CCMenuItemFont::create("Setting", this,
			menu_selector(MenuScene::menuCloseCallback));
	setMenu->setAnchorPoint(ccp(0.5, 0.5));
	setMenu->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	CCMenuItemFont *aboutMenu = CCMenuItemFont::create("About", this,
			menu_selector(MenuScene::menuAboutCallback));
	aboutMenu->setAnchorPoint(ccp(0.5, 0.5));
	aboutMenu->setPosition(ccp(winSize.width / 2, winSize.height / 2-delta));

//	//    //退出游戏
//	CCMenuItemFont *exitMenu = CCMenuItemFont::create("Exit", this,
//			menu_selector(MenuScene::menuCloseCallback));
//	exitMenu->setAnchorPoint(ccp(0.5, 0.5));
//	exitMenu->setPosition(ccp(winSize.width/2, winSize.height/2-2*delta ));

	CCMenuItemImage* exitImg = CCMenuItemImage::create("delete.png","delete.png", this, menu_selector(MenuScene::menuCloseCallback));
	CCSize exitSize = exitImg->getContentSize();
	exitImg->setAnchorPoint(ccp(0.5, 0.5));
	exitImg->setPosition(ccp(winSize.width-exitSize.width/2-10, exitSize.height/2+10));
	//

	CCMenu* menu = CCMenu::create(test, setMenu, aboutMenu, exitImg, NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu, 1);
}



void MenuScene::menuCloseCallback(CCObject* pSender)
{
	CCLog("close*************************");
    CCDirector::sharedDirector()->end();
    SceneManager::loadScene(EXIT);

}


void MenuScene::menuAboutCallback(CCObject* pSender)
{
	CCLog("Go to about scene");
	SceneManager::loadScene(ABOUT_SCENE);  //暂时测试 GameOver

}

void MenuScene::menuGameCallback(CCObject* pSender)
{
	CCLog("Game Start........");
	SceneManager::loadScene(GAME_SCENE);

}

void MenuScene::menuSetCallback(CCObject* pSender)
{
	SceneManager::loadScene(SETTING);
}

void MenuScene::menuGameOverCallback(CCObject* pSender) {
	SceneManager::loadScene(GAMEOVER);
}
