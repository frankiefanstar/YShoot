/*
 * Bullet.h
 *
 *  Created on: 2013-3-2
 *      Author: rescue01
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "AdvanceSprite.h"
//#include "Config/Config.h"

class Bullet: public AdvanceSprite {

private:
	float m_velocityx;
	float m_velocityy;
	int m_power;
	int m_Hp;
	int m_attackMode;
	int m_parentType;

public:
	bool m_active;
	int m_zorder;

	Bullet();
	~Bullet();
	static Bullet* create(int speed, const char* weapon, int attackMode);
	virtual bool bulletInit(int speed, const char *weapon, int attackMode);

	virtual void update(float dt);

	virtual void hurt();
	virtual void destroy();
	void explode();
	virtual CCRect collideRect();
	virtual bool isActive();

	void removeExplode(CCNode *pSender);

	CREATE_FUNC(Bullet);

};

#endif /* BULLET_H_ */
