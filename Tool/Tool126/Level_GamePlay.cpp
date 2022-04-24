#include "stdafx.h"
#include "Level_GamePlay.h"
#include "GameInstance.h"

CLevel_GamePlay::CLevel_GamePlay(LPDIRECT3DDEVICE9 _pDevice)
	: CLevel(_pDevice)
{
}


HRESULT CLevel_GamePlay::NativeConstruct()
{
	if (!m_pGraphicDev)
		return E_FAIL;

	if (__super::NativeConstruct())
		return E_FAIL;

	CGameInstance* pIns = CGameInstance::Get_Instance();
	Safe_AddRef(pIns);

	if (FAILED(pIns->Add_Layer(LEVEL_GAMEPLAY, Engine::KEY_LEVEL_GAME,Engine::KEY_OBJECT_TEST, &_float3(10.f, 10.f, 10.f))))
	{
		Safe_Release(pIns);
		return E_FAIL;
	}
	Safe_Release(pIns);

	return S_OK;
}

void CLevel_GamePlay::Tick(_float _fDeltaTime)
{
	__super::Tick(_fDeltaTime);
}

HRESULT CLevel_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CLevel_GamePlay* CLevel_GamePlay::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLevel_GamePlay* pInstance = new CLevel_GamePlay(pDevice);
	if (FAILED(pInstance->NativeConstruct()))
	{
		Safe_Release(pInstance);
		MSGBOX(TEXT("Failed to Created : CLevel_GamePlay"));
		return nullptr;
	}
	return pInstance;
}

void CLevel_GamePlay::Free()
{
	__super::Free();
	cout << "[CLevel GamePlay Free]" << endl;
}