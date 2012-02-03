#include "../header/Bone.h"

void Bone::move(Player* p, Effect* e, Sound* s)
{
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
	++cnt;
}