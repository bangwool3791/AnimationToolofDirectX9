#include "stdafx.h"
#include "Loader.h"
#include "GameInstance.h"
#include "Level_Loading.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(LEVEL eNextLevel, LPDIRECT3DDEVICE9 pDevice)
	:CLevel(pDevice)
	, m_eNextLevel(eNextLevel)
{
}

HRESULT CLevel_Loading::NativeConstruct()
{
	if (__super::NativeConstruct())
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Tick(_float fDeltaTime)
{
	__super::Tick(fDeltaTime);

	CGameInstance* pIns = CGameInstance::Get_Instance();
	Safe_AddRef(pIns);

	switch (m_eNextLevel)
	{
	case LEVEL_GAMEPLAY:
		//Something to add ProtoType Object to referred GamePlay		
		if (FAILED(pIns->Add_ProtoTypeObject(Engine::KEY_OBJECT_TEST, CTest::Create(m_pGraphicDev))))
		{
			Safe_Release(pIns);
			MSGBOX(TEXT("CTest 객체 추가 실패 "));
		}

		if (FAILED(pIns->Open_Level(m_eNextLevel, CLevel_GamePlay::Create(m_pGraphicDev))))
		{
			MSGBOX(TEXT("Failed to Create : CLevel Logo in CLevel GamePlay"));
		}
		break;
	}

	Safe_Release(pIns);
}

HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LEVEL eNextLevel, LPDIRECT3DDEVICE9 pDevice)
{
	CLevel_Loading * pInstance = new CLevel_Loading(eNextLevel, pDevice);
	Safe_AddRef(pInstance);

	if (FAILED(pInstance->NativeConstruct()))
	{
		Safe_Release(pInstance);
		Safe_Release(pInstance);
		MSGBOX(TEXT("Failed to Create : CLevelLoading"))
	}

	Safe_Release(pInstance);
	return pInstance;
}

void CLevel_Loading::Free()
{
	cout << "[CLevel_Loading Free]" << endl;
	__super::Free();
}
