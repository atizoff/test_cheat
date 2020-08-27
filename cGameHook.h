#pragma once
#include <iostream>
#include "cClasses.h"
#include "cTools.h"
#include "cVar.h"
#include <Windows.h>
#ifdef _WIN64
#define _pdword        PDWORD64
#define _dword        DWORD64
#else
#define _pdword        PDWORD
#define _dword        DWORD
#endif


typedef void(WINAPI* m_SVH)(IGameRules*, HitInfo*);
m_SVH RequestServerHit;
void WINAPI ServerHit(IGameRules* pGameRules, HitInfo* pHitInfo);

class HitHook
{
public:
	void Init()
	{
		PDWORD64* pGameRules = (PDWORD64*)IGameFramework::Singleton()->GetIGameRules();
		if (pGameRules == m_pGameRules)
		{
			return;
		}

		if (m_pGameRules && m_pdwNewVMT)
		{
			*m_pGameRules = m_pdwOldVMT;
			delete[] m_pdwNewVMT;
		}

		m_pGameRules = NULL;
		m_pdwOldVMT = NULL;

		if (!pGameRules) return;

		m_pGameRules = pGameRules;

		m_pdwOldVMT = *m_pGameRules;
		if (!m_pdwOldVMT) return;

		DWORD64 dwVMTSize = 0;
		for (; m_pdwOldVMT[dwVMTSize]; ++dwVMTSize)
		{
			if (IsBadCodePtr((FARPROC)m_pdwOldVMT[dwVMTSize]))
			{
				break;
			}
		}

		m_pdwNewVMT = new DWORD64[dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64) * dwVMTSize);

		*m_pGameRules = m_pdwNewVMT;

		RequestServerHit = (m_SVH)(m_pdwOldVMT[156]);//access_denied_access_coins

		m_pdwNewVMT[156] = (DWORD64)ServerHit;
	}

	DWORD m_dwDamageMult = 1;

private:
	PDWORD64* m_pGameRules = NULL;
	PDWORD64 m_pdwOldVMT = NULL;
	PDWORD64 m_pdwNewVMT = NULL;
};

HitHook hHit;

//

void __stdcall ServerHit(IGameRules* pGameRules, HitInfo* pHitInfo)
{

	//pHitInfo->bServer = true;

	//if (Hack.head)
	//{
		//if (BONE)
			//pHitInfo->partId = 13;
		//else
			//pHitInfo->partId = 1;
	//}
	//if (Hack.bwall)
	//{
		//pHitInfo->material = rand();
		//pHitInfo->projectileId = rand();
	//}

	if (Hack.damageV > 1)
	{
		for (int i = 0; i < hHit.m_dwDamageMult; ++i)
		{
			RequestServerHit(pGameRules, pHitInfo);
		}
	}
	else
	{
		RequestServerHit(pGameRules, pHitInfo);
	}
}