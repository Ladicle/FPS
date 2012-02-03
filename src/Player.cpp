#include "../header/Player.h"

void Player::setHP(int val)
{
	hp+=val;
	flag=true;
}

int Player::getHP(void)
{
	return hp;
}

bool Player::checkHP(void)
{
	if(flag){
		i=hp/10;
		for(j=0; j<i; ++j)
			hpbar[j].SetPosition(15.0f+21.0f*j, 10.0f, 0.0f);
		for(; j<10; ++j)
			hpbar[j].SetPosition(0.0f, -40.0f, 0.0f);
		flag=false;
		if(hp<=0)
			return true;
	}
	return false;
}

void Player::win(void){
	boss=true;
}

bool Player::getWin(void){
	return boss;
}