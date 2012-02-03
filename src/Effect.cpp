#include "../header/Effect.h"

void Effect::setShotEffect(D3DXVECTOR3 p)
{
	shott=0;
	shot.SetPosition(p.x, p.y, p.z);
}

void Effect::setAttackEffect(D3DXVECTOR3 p)
{
	atkt=0;
	atk.SetPosition(p.x, p.y, p.z);
}

void Effect::addEffect()
{
	if(shott!=10){
		++shott;
		if(shott==10)
			shot.SetPosition(0.0f, 100.0f, 0.0f);
	}
	if(atkt!=10){
		++atkt;
		if(atkt==10)
			atk.SetPosition(0.0f, 100.0f, 0.0f);
	}
}

void Effect::reSet()
{
	g->UnregisterShape(&shot);
	g->UnregisterShape(&atk);
	g->RegisterShape(&shot);
	g->RegisterShape(&atk);
}