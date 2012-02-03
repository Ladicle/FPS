#include "../header/Enemy.h"

void Enemy::setting(ARSG* _g, wchar_t *mfn)
{
	g=_g;
	g->CreateMesh(this, mfn);
}

void Enemy::setARSG(ARSG* _g)
{
	g=_g;
}

void Enemy::setSize(float zoom, coorType type)
{
	SetScale(zoom, zoom, zoom, type);
}

void Enemy::hitCheck(Gun* gun, Effect* e)
{
	if(!flag){
		if(gun->getShotState()){
			shot = gun->getShotPoint();
			p = GetPosition();
			if((shot>p.x-atk)&&(shot<p.x+atk)){
				--hp;
				if(hp<=0){
					SetPosition(0.0f, 0.0f, -20.0f, GL_ABSOLUTE);
					e->setShotEffect(p);
					flag=true;
				}
			}
		}
	}
}