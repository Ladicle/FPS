#ifndef	_BATTLEEFFECT_
#define _BATTLEEFFECT_

#include "arstest.h"

class Effect
{
private:
	ARSG* g;
	Texture shot, atk;
	int shott, atkt;

public:
	Effect(ARSG* _g){
		g=_g;
		shott=0;
		atkt=0;
		g->CreateTexture(&shot, L"effect/5.png");
		g->RegisterShape(&shot);
		shot.SetPosition(0.0f, 100.0f, 0.0f);
		g->CreateTexture(&atk, L"effect/dmg.png");
		g->RegisterShape(&atk);
		atk.SetPosition(0.0f, 100.0f, 0.0f);
	}

	void setShotEffect(D3DXVECTOR3 p);
	void setAttackEffect(D3DXVECTOR3 p);
	void addEffect();
	void reSet();
};

#endif
