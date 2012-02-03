#ifndef _BATMAN_
#define _BATMAN_

#include "Enemy.h"

class Batman : public Enemy
{
private:
	float dx, dy, dz, roll;

public:
	Batman():Enemy(0, 0){};
	Batman(float x, float y, float z, float _dx, float _dy, float _dz, float _roll):Enemy(1, 0.3f){
		dx=_dx;
		dy=_dy;
		dz=_dz;
		roll=_roll;
		SetPosition(x, y, z);
		SetRotationX(0.05f);
		setSize(1.5f);
	}

	void move(Player* p, Effect* e, Sound* s);
};

#endif