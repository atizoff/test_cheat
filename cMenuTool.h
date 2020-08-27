#pragma once
#include "includes.h"
#ifndef  _TOOLS_H_
#define _TOOLS_H_

struct cKeys
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];

typedef int(__stdcall* x_corben_detca)(int number);
x_corben_detca tx_corben_detca;

wchar_t dlldir[320];

class cTools
{
public:
	bool IsFocusWindow(wchar_t* ClassName, wchar_t* WindowName)
	{
		DWORD lProcessId = -2;
		DWORD processId = -1;

		HWND hWnd = FindWindowW(ClassName, WindowName);
		GetWindowThreadProcessId(hWnd, &processId);

		HWND foregroundWindow = GetForegroundWindow();
		GetWindowThreadProcessId(foregroundWindow, &lProcessId);
		return processId == lProcessId;
	}

	bool KeyPressed(int Key, DWORD dwTimeOut)
	{
		if (HIWORD(GetKeyState(Key)))
		{
			if (!kPressingKey[Key].bPressed || (kPressingKey[Key].dwStartTime && (kPressingKey[Key].dwStartTime + dwTimeOut) <= GetTickCount()))
			{
				kPressingKey[Key].bPressed = TRUE;
				if (dwTimeOut > NULL)kPressingKey[Key].dwStartTime = GetTickCount();
				return TRUE;
			}
		}
		else
			kPressingKey[Key].bPressed = FALSE;
		return FALSE;
	}

}*sTools;
#endif