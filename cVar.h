#pragma once
#include "includes.h"

bool SetBulletLine = false;

#define POS(y) 13+20*y

enum Color : D3DCOLOR
{
	WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
	RED = D3DCOLOR_ARGB(255, 88, 50, 140),
	GREEN = D3DCOLOR_ARGB(255, 000, 255, 000),
	BLUE = D3DCOLOR_ARGB(255, 000, 000, 255),
	BLACK = D3DCOLOR_ARGB(255, 000, 000, 000),
	PURPLE = D3DCOLOR_ARGB(255, 125, 000, 255),
	GREY = D3DCOLOR_ARGB(255, 255, 255, 255),
	YELLOW = D3DCOLOR_ARGB(255, 255, 255, 000),
	ORANGE = D3DCOLOR_ARGB(255, 255, 165, 000),
	DEEPSKYBLUE = D3DCOLOR_ARGB(255, 30, 144, 255),
	CHOCOLATE2 = D3DCOLOR_ARGB(255, 238, 118, 33),
	GOLD2 = D3DCOLOR_ARGB(255, 238, 201, 0),
};

#define	 KingGradBox		D3DCOLOR_ARGB(10, 0, 0, 0)
#define	 KingWhite			D3DCOLOR_ARGB(255, 255, 255, 255)
#define	 KingBlack			D3DCOLOR_ARGB(240, 000, 000, 000)
#define	 KingGray			D3DCOLOR_ARGB(255, 255, 255, 255)
#define	 KingDark			D3DCOLOR_ARGB(255, 0, 0, 0)
#define	 KingDark2			D3DCOLOR_ARGB(225, 0, 0, 0)
#define	 KingBlue			D3DCOLOR_ARGB(255, 73, 124, 174)
#define	 KingRed			D3DCOLOR_ARGB(255, 88, 50, 140)
#define	 KingOrange			D3DCOLOR_ARGB(255, 88, 50, 140)
#define  ÅsoneBlackBox      D3DCOLOR_ARGB(210, 12, 14, 17)
#define  EsoneBlackBorder   D3DCOLOR_ARGB(180, 000, 000, 000)
#define  GREENDSIFD         D3DCOLOR_ARGB(255, 000, 255, 000)
#define  DSFBLUE            D3DCOLOR_ARGB(255, 000, 000, 255)
#define  DUSHDSSDI          D3DCOLOR_ARGB(255, 000, 000, 000)
#define  krassssnui         D3DCOLOR_ARGB(215, 255, 000, 000)
#define  transparent        D3DCOLOR_ARGB(0, 0, 0, 0, 0)

#define  Sinui 0xFF0000
#define  KingLime 0x00FF00
#define  Gray 0x808080
#define  DimGrey 0x696969
#define  Krasnui 0x0000FF
#define  Zelenou 0x00ff00
#define  Beloi 0xD0D0D0
#define  Yoyl 0x008080
#define  Shornyi 0x000000
#define  Krash 0xFF0000
#define  Gren 0x00FF00


const char* AimType[2] = { "vector", "fast" };
const char* AimShot[2] = { "on LKM", "auto" };
const char* DamagerShot[2] = { "on Q", "auto" };
const char* Damage[6] = { "x1", "x2", "x5", "x10", "x15", "x20" };
const char* RateFire[3] = { "1000", "3000", "5000" };
const char* BonePart[2] = { "Head", "Body" };
const char* SILUETS[6] = { "OFF", "Red", "Green", "Yellow", "Blue", "By health" };

typedef std::wstring WStr;
bool Menu_Weapon, Menu_ESP, Menu_AIMS, Menu_Player;
bool SHOW2;

class cFun
{
public:
	int aim, aimtype, aimshot, fov, wallshot, bwall, head, checkfov, damager, damagershot;
	int recoil, spread, unlim, fknife, sway, shutter, rateoffire, rateoffireV, damageV;
	int autoshot, delaya;
	int sillhouete, fovrender;
	int antiflash, climb, mines, rotate, jiraffe;
}Hack;
