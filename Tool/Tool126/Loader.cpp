#include "stdafx.h"
#include "Loader.h"
#include <process.h>

CLoader::CLoader(LEVEL _eNextLevel, LPDIRECT3DDEVICE9 _pDevice)
	: m_eNextLevel(_eNextLevel)
, m_pGraphicDev(_pDevice)
{
	Safe_AddRef(m_pGraphicDev);
}

_uint WINAPI EntryFunction(void * arg)
{
	CLoader * pInstance = static_cast<CLoader*>(arg);
	Safe_AddRef(pInstance);
	EnterCriticalSection(&(pInstance->Get_CriticalSection()));
	_uint iProgressCnt = 0;
	switch (pInstance->Get_Level())
	{
	case LEVEL_LOGO:
		iProgressCnt = pInstance->Loading_Logo();
		break;
	case LEVEL_GAMEPLAY:
		iProgressCnt = pInstance->Loading_GamePlay();
		break;
	}
	LeaveCriticalSection(&(pInstance->Get_CriticalSection()));
	Safe_Release(pInstance);

	return iProgressCnt;
}

HRESULT CLoader::NativeConstruct()
{
	InitializeCriticalSection(&m_stCriticalSection);

	m_hThread =  (HANDLE)_beginthreadex(nullptr, 0, EntryFunction, this, CREATE_SUSPENDED, nullptr);
	cout << "스레드 생성" << endl;
	if (!m_hThread)
		return E_FAIL;

	ResumeThread(m_hThread);
	cout << "스레드 시작" << endl;
	return S_OK;
}

CLoader* CLoader::Create(LEVEL _eNextLevel, LPDIRECT3DDEVICE9 _pDevice)
{
	CLoader * pInstance = new CLoader(_eNextLevel, _pDevice);
	Safe_AddRef(pInstance);
	if (!pInstance)
		return NULL;

	if (FAILED(pInstance->NativeConstruct()))
	{
		Safe_Release(pInstance);
		MSGBOX(TEXT("Failed to Create : CLoader"))
		return NULL;
	}
	Safe_Release(pInstance);
	return pInstance;
}

void CLoader::Free()
{
	cout << "CLoader Free" << endl;
	WaitForSingleObject(m_hThread, INFINITE);
	//리턴문에 의해서 쓰레드를 종료하므로 _exitthreadex 자동 호출ㄴ
	Safe_Release(m_pGraphicDev);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);;
}
