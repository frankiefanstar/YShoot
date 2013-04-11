/*
 * Config.h
 *
 *  Created on: 2012-9-16
 *      Author: arch
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <cocos2d.h>
#include <vector>

USING_NS_CC;
using namespace std;

//--------全局变量

extern CCArray *play_bullet;
extern CCArray *enemy_bullet;
extern CCArray *enemy_items;


//自定义的敌人信息
typedef struct Enemies
{
    string showType;
    int showTime;
    int types[3];
    Enemies()
    {
        showType = "Repeat";
        showTime = 0;
        types[0] = 0;
        types[1] = 0;
        types[2] = 0;
    }
}EnemyInfo;

//新定义的敌人类型
typedef struct {
    int type;
    string textureName;
    string bulletType;
    int hp;
    int moveType;
    int scoreValue;
}EnemyType;


class Config {
private :
	//单例模式
	Config();

	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemyTypes;
	int m_scoreValue;  //比分
	int m_life;   //生命值
	bool m_isAudioOn;  //是否开启音乐

	CCSize winSize;


public:
	virtual ~Config();

	//Enemy信息向量
	vector<EnemyInfo> getEnemies();
	vector<EnemyType> getEnemyType();


	//Constant Value
	const static int TAG_PLANE_SELF = 11;
	const static int TAG_PLANE_OTHER = 12;
	const static int TAG_BULLET = 13;

	static Config* sharedConfig();

//	void init();
	bool getConfig();

	//num of fires  敌机数量
	int getLifeCount();
	void updateLifeCount();
	void setScoreValue(int v);
	int getScoreValue();

	bool getAudioState();

};

#endif /* CONFIG_H_ */
