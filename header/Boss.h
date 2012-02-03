#ifndef _BOSS_
#define _BOSS_

#include "Enemy.h"
#include "Player.h"

class Boss : public Enemy
{
private:
	float dx, dy, dz;

public:
	Boss():Enemy(0, 0){};
	Boss(float x, float y, float z):Enemy(8, 0.5f){
		setSize(2.0f);
		SetPosition(x, y, z);
	}

	void move(Player* p, Effect* e, Sound* s);
	void hitCheck(Gun* gun, Effect* e, Player* pl);
};

#endif