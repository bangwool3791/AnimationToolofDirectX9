#include "stdafx.h"
#include "LevelManager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CLevel_Manager)

CLevel_Manager::CLevel_Manager()
{
}

HRESULT CLevel_Manager::NativeConstruct()
{
	if(0 > m_eNextLevel)
		return E_FAIL;

	if(!m_pCurrentLevel)
		return E_FAIL;

	//if (FAILED(m_pCurrentLevel->NativeConstruct()))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Manager::Open_Level(_uint eNextLevel, CLevel* pLevel)
{
	cout << "입력 레벨 : " << eNextLevel << endl;
	cout << "이전 레벨 : " << m_eNextLevel << endl;
	if (m_pCurrentLevel)
	{
		cout << "이전 레벨 포인터 삭제 " << endl;
		Safe_Release(m_pCurrentLevel);

		CGameInstance * pGameInstance = CGameInstance::Get_Instance();
		pGameInstance->Clear(m_eNextLevel);
	}

	m_eNextLevel = eNextLevel;

	m_pCurrentLevel = pLevel;

	if (FAILED(NativeConstruct()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Manager::Tick(_float fDeltaTime)
{
	if (!m_pCurrentLevel)
		return;

	m_pCurrentLevel->Tick(fDeltaTime);
}

HRESULT CLevel_Manager::Render()
{
	if(!m_pCurrentLevel)
		return E_FAIL;

	if (FAILED(m_pCurrentLevel->Render()))
		return E_FAIL;

	return S_OK;
}

void CLevel_Manager::Free()
{
	if (!m_pCurrentLevel)
	{
		MSGBOX(TEXT("Failed to Free in CLevel_Manager"));
		return;
	}

	Safe_Release(m_pCurrentLevel);
}