#pragma once
#include "includes.h"
#include "cClasses.h"

typedef int(WINAPI* m_pCustomAmmo)();
m_pCustomAmmo RequestCustomAmmo;
int WINAPI CustomAmmo(); //

class AmmoHook
{
public:
	void Init()
	{
		IActor* mIActor;
		IGameFramework::Singleton()->GetClientActor(&mIActor);

		PDWORD64* pIGameRules = (PDWORD64*)mIActor->GetCurrentItem();
		if (pIGameRules == m_pIGameRules)
		{
			return;
		}

		if (m_pIGameRules && m_pdwNewVMT)
		{
			*m_pIGameRules = m_pdwOldVMT;
			delete[] m_pdwNewVMT;
		}

		m_pIGameRules = NULL;
		m_pdwOldVMT = NULL;

		if (!pIGameRules) return;

		m_pIGameRules = pIGameRules;

		m_pdwOldVMT = *m_pIGameRules;
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

		*m_pIGameRules = m_pdwNewVMT;

		RequestCustomAmmo = (m_pCustomAmmo)(m_pdwOldVMT[568]);

		m_pdwNewVMT[568] = (DWORD64)CustomAmmo;
	}

private:
	PDWORD64* m_pIGameRules = NULL;
	PDWORD64 m_pdwOldVMT = NULL;
	PDWORD64 m_pdwNewVMT = NULL;
};
AmmoHook ammo;

int WINAPI CustomAmmo()
{
	void* result = nullptr;

	if (result == (void*)0x1411DBC60)
	{
		return 0;
	}

	return RequestCustomAmmo();
}