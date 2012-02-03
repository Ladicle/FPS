#pragma once
#include "../header/arstest.h"
#include "../../include/ars.h"
#include "../../include/WindowManager.h"
#include "../../include/d3dx9math.h"
#include <windows.h>
#include <tchar.h>
#include "../header/Player.h"
#include "../header/Gun.h"
#include "../header/Batman.h"
#include "../header/Bone.h"
#include "../header/Boss.h"
#define D3D_DEBUG_INFO
#define Threshold 5
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BAT 10
#define BONE 5
void subtract_maskf(BitPlane* mask, BitPlane* result, BitPlane* bg, BitPlane* src, DWORD border);
unsigned int sizex, sizey, depth;

UINT MainLoop(WindowManager *winmgr)
{
	//window setting
	Window window;
	winmgr->RegisterWindow(&window);
	ARSG g(window.hWnd, WINDOW_WIDTH, WINDOW_HEIGHT, true);
	ARSI *keyIn = window.GetInputHandler();
	ARSS s;
	Sound bgm, badend, atk;
	s.CreateSoundBuffer(&atk, L"../sound/atk.wav");
	s.CreateSoundBuffer(&bgm, L"../sound/bgm.wav");
	s.CreateSoundBuffer(&badend, L"../sound/fadein.wav");

	//Texture
	Texture board;
	Texture bg;
	Texture mask;
	Texture gameover;
	Texture clear;

	//BitPlane
	BitPlane source;
	BitPlane stored;
	BitPlane hitArea;
	BitPlane bitmask;

	//Light
	Light light;
	g.CreateLight(&light);
	light.SetLightIntensity(10);

	//Camera
	ARSD d;
	d.Init();
	d.AttachCam(0);
	d.BindBitPlane(&source);
	d.StartGraph();
	while (!source.GetPointer());
	source.GetSize(&sizex, &sizey, &depth);
	source.CopyTo(&stored);

	//background
	g.CreateTexture(&bg, L"../img/bgbg.jpg");
	bg.SetDrawMode(true);
	g.CreateTexture(&mask, L"../img/mask.jpg");
	mask.SetDrawMode(true);
	mask.GetBitData(&bitmask);
	g.CreateTexture(&board, sizex, sizey);
	board.SetDrawMode(true);
	Mesh f;
	g.CreateMesh(&f, L"../model/f4.x");
	float scale=25.0f;
	f.SetScale(scale, scale, scale, GL_ABSOLUTE);
	f.SetPosition(45.0f, -4.0f, 65.0f, GL_ABSOLUTE);
	f.SetRotationY(1.57f);
	g.CreateTexture(&gameover, L"../img/gameover.jpg");
	gameover.SetDrawMode(true);
	g.CreateTexture(&clear, L"../img/clear.PNG");
	gameover.SetDrawMode(true);

	//gun
	Gun gun(&g, &s, L"gun2.x", L"../sound/gun2.wav");
	gun.DefaultPosition(0.0f, -1.2f, -17.0f);
	gun.SetRotation(-0.1f, 3.14f, 0.0f, GL_ROTXYZ, GL_ABSOLUTE);

	//enemy
	int i, j;
	Batman bats[BAT];
	for(i=0,j=-1; i<BAT; ++i,j*=-1){
		new(bats+i)Batman(j*3.0f, 5.0f, 25.0f, j*-1*0.02f, -0.03f, -0.25f, j*-1*0.04f);
		bats[i].setting(&g, L"../model/bat.x");
	}
	Bone bons[BONE];
	for(i=0; i<BONE; ++i){
		new(bons+i)Bone(i*2, -4.8f, 20.0f, 0.0f, 0.01f, -0.25f);
		bons[i].setting(&g, L"../model/bone.x");
	}
	Boss boss(0.0f, -8.0f, 5.0f);
	boss.setSize(3.0f);
	boss.setting(&g, L"../model/teki.x");

	//add
	g.RegisterLight(&light);
	g.RegisterShape(&bg);
	g.RegisterShape(&f);
	for(i=0; i<BAT; ++i)
		g.RegisterShape(&bats[i]);
	g.RegisterShape(&board);
	g.RegisterShape(&gun);
	Effect e(&g);
	Player p(&g);

	enum {START, BAD, SCARLE, ARMER, BOSS, GAMEOVER, END};
	int state = START;
	unsigned int cnt=0;
	j=0;
	bgm.Play(true);
	while (!winmgr->WaitingForTermination()){
		if (keyIn->GetKeyTrig('A'))
			source.CopyTo(&stored);
		if (keyIn->GetKeyTrig('Q')) break;
		
		subtract_maskf(&bitmask, &hitArea,&stored,&source,0x50505050);
		gun.move(&hitArea);

		switch(state){
		case START:
			if(cnt==20){
				cnt=0;
				state=BAD;
			}
			break;
		case BAD:
			if(cnt<400)
				f.SetPosition(-0.004f, 0.0f, -0.05f, GL_RELATIVE);
			else if(cnt<410)
				f.SetPosition(-0.01f, 0.0f, -0.15f, GL_RELATIVE);
			else if(cnt<420){
				f.SetRotationY(-0.157f);
				f.SetPosition(-9.0f, 0.0f, -1.7f, GL_RELATIVE);
			}else if(cnt<565){
				f.SetRotationY(-0.001f);
				f.SetPosition(-0.04f, 0.0f, -0.14f, GL_RELATIVE);
			}else if(cnt<745){
				f.SetRotationY(0.001f);
				f.SetPosition(0.0f, 0.0f, -0.15f, GL_RELATIVE);
			}else if(cnt<770){
				f.SetRotationY(0.052f);
				f.SetPosition(1.5f, 0.0f, 0.72f, GL_RELATIVE);
			}else if(cnt==771){
				cnt=0;
				j=0;
				state=SCARLE;
				for(i=0; i<BONE; ++i)
					g.RegisterShape(&bons[i]);
				e.reSet();
			}
			break;
		case SCARLE:
			if(cnt<45){
				f.SetPosition(0.0f, 0.0f, 0.31f, GL_RELATIVE);
			}else if(cnt == 201){
				cnt=0;
				j=0;
				state=ARMER;
				for(i=0; i<BONE; ++i)
					g.UnregisterShape(&bons[i]);
					
			}
			break;

		case ARMER:
			if(cnt<20){
				f.SetRotationY(0.055f);
				f.SetPosition(1.5f, 0.0f, 0.72f, GL_RELATIVE);
			}else if(cnt<100){
				f.SetRotationY(0.005f);
				f.SetPosition(0.12f, 0.0f, -0.16f, GL_RELATIVE);
			}else if(cnt<210){
				f.SetPosition(0.0f, 0.0f, -0.175f, GL_RELATIVE);
			}else if(cnt<220){
				f.SetRotationY(-0.055f);
				f.SetPosition(-0.1f, 0.0f, -0.2f, GL_RELATIVE);
			}else if(cnt<370){
				f.SetRotationY(0.003f);
				f.SetPosition(0.0f, 0.0f, -0.12f, GL_RELATIVE);
			}
			if(p.getWin()){
				state=BOSS;
			}
			if(cnt==360){
				g.RegisterShape(&boss);
				e.reSet();
			}
			if(cnt>370){
				boss.move(&p, &e, &atk);
				boss.hitCheck(&gun, &e, &p);
			}
			break;
		case BOSS:
			bgm.Stop();
			g.RegisterShape(&clear);
			state=END;
			break;
		case GAMEOVER:
			bgm.Stop();
			badend.Play();
			g.RegisterShape(&gameover);
			state=END;
			break;
		default:
				break;
		}

		if(state==START || state==BAD){
			if(j<BAT && cnt%61==0)
				++j;
			for(i=0; i<j; ++i){
				bats[i].move(&p, &e, &atk);
				bats[i].hitCheck(&gun, &e);
			}
		}
		
		if(state==SCARLE){
			if(j<BONE && cnt%61==0)
				++j;
			for(i=0; i<j; ++i){
				bons[i].move(&p, &e, &atk);
				bons[i].hitCheck(&gun, &e);
			}
		}
		
		e.addEffect();
		if(p.checkHP())
			state=GAMEOVER;
		board.SetBitData(&hitArea);
		g.Draw();
		++cnt;
	}
	d.StopGraph();
	return 0;
}

inline void subtract_maskf(BitPlane* mask, BitPlane* result, BitPlane* backgrnd, BitPlane* src, DWORD border)
{
	diffBitPlane(result,backgrnd,src,border);
	andBitPlane(result, mask, result, 0x10101010);
	monochrome(result,result);
	createmaskf(result,result,border);
	maskFilter(result,src,result);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WindowManager program(hInstance, &MainLoop);
#ifdef DEBUG
	MessageBox(NULL,L"OK?",TEXT(APPNAME), NULL);
#endif
	return 0;
}
