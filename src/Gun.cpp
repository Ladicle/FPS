#include "../header/Gun.h"

void Gun::setARSG(ARSG* _g)
{
	g=_g;
}

void Gun::setARSS(ARSS* _s)
{
	s=_s;
}

void Gun::DefaultPosition(float x, float y, float z)
{
	dx=x;
	dy=y;
	dz=z;

	SetPosition(x, y, z, GL_ABSOLUTE);
}

bool Gun::getShotState(void)
{
	if(flag){
		return true;
	}
	return false;
}

float Gun::getShotPoint(void)
{
	return p3.x*5;
}

void Gun::move(BitPlane* hitArea)
{
	getCG(&gx, &gy, &pixel, hitArea);

	switch(state){
	case ACTIVE:
		if(pixel>600){
			state = INACTIVE;
		}
		flag=false;
		break;
	case INACTIVE:
		if(pixel<600){
			state = ACTIVE;
			flag=true;
			shot.Play();
		}else{
			p2.x = (float)gx;
			p2.y = (float)gy;
			g->Convert2Dto3D(&p3, p2);
			SetPosition(p3.x*4, dy, dz, GL_ABSOLUTE);
		}
		break;
	default:
		break;
	}
}

