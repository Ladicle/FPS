#include "../header/Batman.h"

void Batman::move(Player* p, Effect* e, Sound *s)
{
	if(cnt<200){
		SetPosition(dx, dy, dz, GL_RELATIVE);
		SetRotationY(0.5f);
	}
	if(!flag && cnt==170){
		p->setHP(-5);
		s->Play();
		e->setAttackEffect(GetPosition());
	}
	if(cnt==230){
		g->UnregisterShape(this);
	}
	++cnt;
}