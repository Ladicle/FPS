#ifndef _BONE_
#define _BONE_

#include "Enemy.h"

class Bone : public Enemy
{
private:
	float dx, dy, dz;

public:
	Bone():Enemy(0, 0){};
	Bone(float x, float y, float z, float _dx, float _dy, float _dz):Enemy(1, 0.5f){
		dx=_dx;
		dy=_dy;
		dz=_dz;
		setSize(2.0f);
		SetPosition(x, y, z);
	}

	void move(Player* p, Effect* e, Sound* s);
};

#endif