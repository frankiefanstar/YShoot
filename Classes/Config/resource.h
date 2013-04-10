/*
 * resource.h
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

//记录游戏状态
enum GameState {
	NOT_START,
	START,
	GAME_OVER,
};


//Node的Tag值
enum NodeTag {
	//背景图片
	BACK_LAYER1 = 10,
	BACK_LAYER2 = 11,
	BACK_LAYER3 = 12,

	//精灵类
	TAG_HERO = 1001,
	TAG_ENEMY = 1000,
	TAG_ENEMY_BULLET = 900,  //Enemy bullet
	TAG_HERO_BULLET = 901,

	//expolode
	//TAG_EXPLODE=9999,

};

enum speed {
	SPEED_HERO_X = 5,
	SPEED_HERO_Y = 4,

};

//纵深
enum NodeOrder {
	ORDER_MENU_BACKGROUND_PIC = 0,  //背景图片
	ORDER_HERO = 3000, //Hero
	ORDER_ENEMY = 1000,  //enemy
	ORDER_BULLET =3000,	//Bullet
	ORDER_MENU = 1,   //Menu
	ORDER_BACKGROUND = -10,

	ORDER_EXPLODE = 9999,
};


//--------------------------------------------------字符串值
//菜单项
static const char s_menu_start[] = "Start";
static const char s_menu_end[] = "End";
static const char s_menu_set[] = "Setting";
static const char s_menu_about[] = "About";
static const char s_menu_pause[] = "Pause";
static const char s_menu_resume[] = "Resume";

//--------------------------------------------------Audio
// 背景音乐
static const char s_audio_1[] = "xx.mp3";

//--------------------------------------------------图片
//Hero图片
static const char s_hero[] = "plane.png";
//Bullet图片 （多种）
static const char s_bullet_type1[] = "aa.png";
//敌人图片
static const char s_enemy[] = "bb.png";


//effect images
static const char s_explosion[]         = "explosion.png";
static const char s_explode1[]          = "explode1.jpg";
static const char s_explode2[]          = "explode2.jpg";
static const char s_explode3[]          = "explode3.jpg";


//plist
static const char s_Enemy_plist[]       = "Enemy.plist";
static const char s_explosion_plist[]   = "explosion.plist";
static const char s_bullet_plist[]      = "bullet.plist";





#endif /* RESOURCE_H_ */
