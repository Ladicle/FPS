#include "../header/Boss.h"

void Boss::move(Player* p, Effect* e, Sound* s)
{
	/*
	if(cnt<180){
		SetPosition(dx, dy, dz, GL_RELATIVE);
	}
	if(!flag && cnt==130){
		p->setHP(-10);
		s->Play();
		e->setAttackEffect(GetPosition());
	}if(cnt==200){
		g->UnregisterShape(this);
	}
	*/
	SetRotationY(0.04f);
	if(cnt%131==0){
		p->setHP(-10);
		s->Play();
		e->setAttackEffect(GetPosition());
	}
	++cnt;
}

void Boss::hitCheck(Gun* gun, Effect* e, Player* pl)
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
					pl->win();
				}
			}
		}
	}
}