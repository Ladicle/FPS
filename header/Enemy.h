#ifndef _ENEMY_
#define _ENEMY_

#include "arstest.h"
#include "Gun.h"
#include "Player.h"
#include "Effect.h"

class Enemy : public Mesh
{
protected:
	ARSG* g;

	int cnt, hp;
	float shot, atk;
	bool flag;
	D3DXVECTOR3 p;

public:
	Enemy(int HP, float _atk)
	{
		cnt=0;
		atk=_atk;
		hp = HP;
		flag=false;
	}

	void setting(ARSG* _g, wchar_t *mfn);
	void setARSG(ARSG* _g);
	void setSize(float zoom, coorType type=GL_ABSOLUTE);
	void hitCheck(Gun* gun, Effect* e);

	virtual void move(Player* p, Effect* e, Sound* s) = 0;
};

#endif