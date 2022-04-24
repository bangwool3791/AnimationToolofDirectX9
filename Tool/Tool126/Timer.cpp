#include "stdafx.h"
#include "Timer.h"

using namespace Engine;

CTimer::CTimer():m_fTimeDelta(0.f)
{
	ZeroMemory(&m_CurrentTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OriginTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CTimer* CTimer::Create()
{
	CTimer *pInstance = new CTimer;

	if(FAILED(pInstance->NativeConstruct()))
	{
		MSGBOX(L"Failed to Create CTimer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTimer::Free()
{
	
}