#ifndef _PLAYER_
#define _PLAYER_

#include "arstest.h"

class Player
{
private:
	ARSG *g;
	Texture hpbar[10];
	int hp, i, j;
	bool flag, boss;

public:
	Player(ARSG* _g)
	{
		g=_g;
		hp=100;
		flag=false;
		boss=false;
		for(i=0; i<10; ++i)
		{
			g->CreateTexture(&hpbar[i], L"hpbar.jpg");
			hpbar[i].SetDrawMode(true);
			hpbar[i].SetPosition(15.0f+21.0f*i, 10.0f, 0.0f);
			g->RegisterShape(&hpbar[i]);
		}
	}

	void win(void);
	bool getWin(void);
	void setHP(int dam);
	int getHP(void);
	bool checkHP(void);

};

#endif
