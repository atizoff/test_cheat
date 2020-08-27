#include "vmt.h"
#include "cClasses.h"
#include "includes.h"
#include "cFunction.h"
#include "cGameHook.h"
#include "cDraw.h"
#include "cVar.h"
#include "cMenu.h"
#include "cAmmoHack.h"

bool creting = false;
BOOL open = true;

typedef HRESULT(WINAPI* m_pPresentHook)(IDirect3DDevice9*, CONST RECT*, CONST RECT*, HWND, CONST RGNDATA*);
m_pPresentHook PresentHook;

typedef HRESULT(WINAPI* m_pRayTraceHook)(PVOID pvoid, SRWIParams* drinfo, const char* pNameTag, __int64 i);
m_pRayTraceHook RayTraceHook;

typedef INT(WINAPI* m_pUpdate)(ISystem*, INT, INT);
m_pUpdate pUpdate;

VMTHookManager* VmtHookRWI = new VMTHookManager;
VMTHookManager* VmtHook = new VMTHookManager;
VMTHookManager* VmtUpdate = new VMTHookManager;


INT WINAPI pRayTraceHook(PVOID pvoid, SRWIParams* drinfo, const char* pNameTag, __int64 i)
{
	if (drinfo)
		if (drinfo->objtypes == 799)
			if (WALLSHOT)
				drinfo->objtypes = 16;

	return RayTraceHook(pvoid, drinfo, pNameTag, i);
}

INT APIENTRY Update(ISystem* pSystem, INT iInfo, INT iPause)
{
	if (GetAsyncKeyState(VK_HOME) & 1) { open = !open; }

	request();

	return pUpdate(pSystem, iInfo, iPause);
}

HRESULT WINAPI pPresentHook(IDirect3DDevice9* m_pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{

	while (!m_pDevice)
		m_pDevice = m_pDevice;

	if (!creting)
	{
		D3DXCreateLine(m_pDevice, &pLine);
		D3DXCreateFontW(m_pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_MODERN, L"Trebuchet MS", &pFont);
		m_pDevice->GetViewport(&Viewport);
		ScreenWidth = Viewport.Width;
		ScreenHeight = Viewport.Height;
		ScreenCenterX = (ScreenWidth / 2);
		ScreenCenterY = (ScreenHeight / 2);


		creting = true;
	}
	if (!pFont || !pLine)
	{
		pLine->OnLostDevice();
		pFont->OnLostDevice();
	}
	else
	{
		if (open) menu(m_pDevice);

		pLine->OnLostDevice();
		pLine->OnResetDevice();
		pFont->OnLostDevice();
		pFont->OnResetDevice();
	}
	//D3DReset();

	if (GetAsyncKeyState(VK_NUMPAD9))
	{
		VmtHook->UnHook();
		VmtHookRWI->UnHook();
		VmtUpdate->UnHook();
	}

	return PresentHook(m_pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserv)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hInstance);


		VmtHook->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->pRenderer->GetDirectDevice());
		PresentHook = (m_pPresentHook)VmtHook->dwHookMethod((DWORD64)pPresentHook, 17);

		VmtHookRWI->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->pPhysicalWorld);
		RayTraceHook = (m_pRayTraceHook)VmtHookRWI->dwHookMethod((DWORD64)pRayTraceHook, 35);

		VmtUpdate->bInitialize((PDWORD64*)SSystemGlobalEnvironment::Singleton()->pSystem);
		pUpdate = (m_pUpdate)VmtUpdate->dwHookMethod((DWORD64)Update, 4);

		Beep(500, 300);

		return TRUE;

		break;
	case DLL_PROCESS_DETACH:

		VmtHook->UnHook();
		VmtHookRWI->UnHook();
		VmtUpdate->UnHook();

		FreeLibraryAndExitThread(hInstance, EXIT_SUCCESS);

		return TRUE;
		break;
	}

	return FALSE;
}