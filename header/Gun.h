#ifndef _GUN_
#define _GUN_

#include "arstest.h"

class Gun : public Mesh
{
private:
	ARSG* g;
	ARSS* s;

	Sound shot;
	int pixel, state;
	bool flag;

	//Position
    D3DXVECTOR3 p3;
	VECTOR2D p2;
	int gx, gy;

	//DefaultPosition
	float dx, dy, dz;


public:
	static enum {ACTIVE, INACTIVE};

	Gun(ARSG* _g, ARSS* _s, wchar_t *mfn, wchar_t *sfn)
	{
		g=_g;
		s=_s;
		gx=0;
		gy=0;
		flag=false;
		state=ACTIVE;
		g->CreateMesh(this, mfn);
		s->CreateSoundBuffer(&shot, sfn);
	}

	void setARSG(ARSG* _g);
	void setARSS(ARSS* _s);
	void DefaultPosition(float x, float y, float z);

	bool getShotState(void);
	float getShotPoint(void);
	void move(BitPlane* hitArea);
};

#endif