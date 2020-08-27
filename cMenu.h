#include "includes.h"
#include "cVar.h"
#include "cDraw.h"


bool DMenu;

void menu(LPDIRECT3DDEVICE9 pDevice)
{	
	sDraw->normal(Menu_Weapon, pDevice);

	sDraw->DrawMenu(pDevice);

	sDraw->ButtonJ(x + 22.5 + 50, y + 90, "AIM", Menu_AIMS, pDevice);
	sDraw->ButtonJ(x + 22.5 + 200, y + 90, "VISUAL", Menu_ESP, pDevice);
	sDraw->ButtonJ(x + 22.5 + 350, y + 90, "MISC", Menu_Player, pDevice);

	if (Menu_AIMS)
	{
		sDraw->DrawMenu2(pDevice);
		sDraw->CheckJ(x + 80, y + 140, "AimBot", Hack.aim, pDevice);
		if (Hack.aim)
		{
			sDraw->Scroll(x + 48, y + 165, Hack.aimtype, AimType, 1, "type", pDevice);
			sDraw->Scroll(x + 48, y + 185, Hack.aimshot, AimShot, 1, "activate", pDevice);
			sDraw->CheckJ(x + 80, y + 205, "Check fov", Hack.checkfov, pDevice);
			if (Hack.checkfov)
			{
				sDraw->Text("fov", x + 71.5, y + 225, D3DCOLOR_ARGB(255, 190, 190, 190), DT_LEFT | DT_NOCLIP);
				sDraw->Scroll(x + 150, y + 229, 100, 8, 1, 360, Hack.fov, (LPSTR)"", (LPSTR)"", pDevice);
			}
			if (Hack.checkfov)
			{
				sDraw->CheckJ(x + 80, y + 249, "Wallshot", Hack.wallshot, pDevice);
				sDraw->CheckJ(x + 80, y + 269, "Bypass wallshot", Hack.bwall, pDevice);
				sDraw->CheckJ(x + 80, y + 289, "Only head", Hack.head, pDevice);
			}
			else
			{
				sDraw->CheckJ(x + 80, y + 225, "Wallshot", Hack.wallshot, pDevice);
				sDraw->CheckJ(x + 80, y + 245, "Bypass wallshot", Hack.bwall, pDevice);
				sDraw->CheckJ(x + 80, y + 265, "Only head", Hack.head, pDevice);
			}
		}
		sDraw->CheckJ(x + 335, y + 140, "Damager", Hack.damager, pDevice);
		if (Hack.damager)
		{
			Hack.aim = 0;
			Hack.wallshot = 1;
			Hack.bwall = 1;
			Hack.head = 0;
			sDraw->Scroll(x + 335 - 30, y + 165, Hack.damagershot, DamagerShot, 1, "activate", pDevice);
		}
	}

	if (Menu_ESP)
	{
		sDraw->DrawMenu2(pDevice);
		sDraw->CheckJ(x + 80, y + 140, "Sillhouete", Hack.sillhouete, pDevice);
		sDraw->CheckJ(x + 80, y + 160, "Show mines", Hack.mines, pDevice);

		sDraw->CheckJ(x + 335, y + 140, "Render FOV", Hack.fovrender, pDevice);
	}

	if (Menu_Player)
	{
		sDraw->DrawMenu2(pDevice);
		sDraw->CheckJ(x + 80, y + 140, "Anti Recoil", Hack.recoil, pDevice);
		sDraw->CheckJ(x + 80, y + 160, "Anti Spread", Hack.spread, pDevice);
		sDraw->CheckJ(x + 80, y + 180, "Anti Shutter", Hack.shutter, pDevice);
		sDraw->CheckJ(x + 80, y + 200, "Anti Sway", Hack.sway, pDevice);
		sDraw->CheckJ(x + 80, y + 220, "Unlimited Ammo", Hack.unlim, pDevice);
		sDraw->CheckJ(x + 80, y + 240, "Fast Knife", Hack.fknife, pDevice);
		sDraw->Text("Damage", x + 71.5, y + 260, D3DCOLOR_ARGB(255, 190, 190, 190), DT_LEFT | DT_NOCLIP);
		sDraw->Scroll(x + 150, y + 263, 100, 8, 1, 15, Hack.damageV, (LPSTR)"", (LPSTR)"x", pDevice);


		sDraw->CheckJ(x + 335, y + 140, "Solo Climb", Hack.climb, pDevice);
		sDraw->Text("Jirrafe [V]", x + 71.5 + 255, y + 160, D3DCOLOR_ARGB(255, 190, 190, 190), DT_LEFT | DT_NOCLIP);
		sDraw->Scroll2Tab(x + 150 + 185 + 80, y + 164, 100, 8, 1, 25, Hack.jiraffe, (LPSTR)"", (LPSTR)"m", pDevice);
	}

	//sDraw->Cursor(pDevice);
}