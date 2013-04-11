/*
 * Config.cpp
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#include "Config/Config.h"
#include <cocos2d.h>
#include <string>
using namespace std;

static Config* g_config;  //单例的config

CCArray *play_bullet;
CCArray *enemy_bullet;
CCArray *enemy_items;


Config* Config::sharedConfig() {
	if(!g_config) {
		g_config = new Config();
		return g_config;
	}
	return g_config;
}

Config::Config(): m_scoreValue(0),m_life(1),m_isAudioOn(true) {
	CCAssert(g_config == NULL, "Attempted to allocate a second instance of a singleton.");

	m_isAudioOn = true;

	play_bullet = CCArray::create();
	play_bullet->retain();
	enemy_bullet = CCArray::create();
	enemy_bullet->retain();
	enemy_items = CCArray::create();
	enemy_items->retain();
	//
	string temp_showType = "Repeat";
	string temp_enemy = "enemy.png";
	string temp_bullet = "bullet.png";
	//------------------------------------------
	    EnemyInfo temp;
	    temp.showType = "Repeat";
	    temp.showTime = 2;
	    temp.types[1] = 1;
	    temp.types[2] = 2;
	    m_enemies.push_back(temp);

	    temp.showTime = 5;
	    temp.types[0] = 3;
	    temp.types[1] = 4;
	    temp.types[2] = 5;
	    m_enemies.push_back(temp);

	    EnemyType enemyType;
	    enemyType.type = 0;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 1;
	    enemyType.moveType = 0;
	    enemyType.scoreValue = 15;
	    m_enemyTypes.push_back(enemyType);

	    enemyType.type = 1;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 2;
	    enemyType.moveType = 0;
	    enemyType.scoreValue = 40;
	    m_enemyTypes.push_back(enemyType);

	    enemyType.type = 2 ;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 4;
	    enemyType.moveType = 2;
	    enemyType.scoreValue = 60;
	    m_enemyTypes.push_back(enemyType);

	    enemyType.type = 3;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 6;
	    enemyType.moveType = 3;
	    enemyType.scoreValue = 80;
	    m_enemyTypes.push_back(enemyType);

	    enemyType.type = 4;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 10;
	    enemyType.moveType = 2;
	    enemyType.scoreValue = 150;
	    m_enemyTypes.push_back(enemyType);

	    enemyType.type = 5;
	    enemyType.textureName = temp_enemy;
	    enemyType.bulletType = temp_bullet;
	    enemyType.hp = 15;
	    enemyType.moveType = 2;
	    enemyType.scoreValue = 200;
	    m_enemyTypes.push_back(enemyType);
}

Config::~Config() {
	play_bullet->release();
	enemy_bullet->release();
	enemy_items->release();
	enemy_items = NULL;
	play_bullet = NULL;
	enemy_bullet = NULL;
//	CCLOG("release config");
}

vector<EnemyInfo> Config::getEnemies()
{
    return m_enemies;
}

vector<EnemyType> Config::getEnemyType()
{
    return m_enemyTypes;
}



//CCArray* Config::getPlayBullet() {
//	return play_bullet;
//}
//
//CCArray* Config::getEnemyBullet() {
//	return enemy_bullet;
//}
//
//CCArray* Config::getEnemyItems() {
//	return enemy_items;
//}


int Config::getLifeCount() {
	//初始化 life 数量为3
	return m_life;
}

void Config::updateLifeCount() {
	m_life--;
}

void Config::setScoreValue(int v) {
	m_scoreValue += v;
}


int Config::getScoreValue() {
	return m_scoreValue;
}

bool Config::getAudioState() {
	return m_isAudioOn;
}
