#include "stdafx.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CGameInstance)

CGameInstance::CGameInstance()  
	: m_pTimer_Manager(CTimer_Manager::Get_Instance())
, m_pGraphicDev(CGraphic_Device::Get_Instance())
, m_pLevelManager(CLevel_Manager::Get_Instance())
, m_pObjectManager(CObject_Manager::Get_Instance())
, m_pComponentManager(CComponent_Manager::Get_Instance())
{
	Safe_AddRef(m_pTimer_Manager);
	Safe_AddRef(m_pGraphicDev);
	Safe_AddRef(m_pLevelManager);
	Safe_AddRef(m_pObjectManager);
	Safe_AddRef(m_pComponentManager);
}

HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInstance, _uint iLayerIndex, const GRAPHIC_DEVICE_DESC& _stGpDev, LPDIRECT3DDEVICE9* _ppDevice)
{
	if (!m_pGraphicDev)
	{
		MSGBOX(TEXT("Grapic Device is Null"));
		return E_FAIL;
	}
	if (FAILED(m_pGraphicDev->InitDevice(_stGpDev, _ppDevice)))
	{
		MSGBOX(TEXT("Failed to InitDevice"));
		return E_FAIL;
	}

	if (!m_pObjectManager)
	{
		MSGBOX(TEXT("ObjectMgr is Null"));
		return E_FAIL;
	}

	/* 입력장치 초기화. */
	//if (FAILED(m_pInput_Device->Initialize_Input_Device(hInstance, g_hWnd)))
	//	return E_FAIL;

	//각 매니져들의 예약.
	if (FAILED(m_pObjectManager->ReserveLayer(iLayerIndex)))
	{
		MSGBOX(TEXT("Failed to Reserve Layer"));
		return E_FAIL;
	}

	if (!m_pComponentManager)
	{
		MSGBOX(TEXT("m_pComponentManager is Null"));
		return E_FAIL;
	}

	if (FAILED(m_pComponentManager->Reserve_ComponentMgr(iLayerIndex)))
	{
		MSGBOX(TEXT("Failed to Reserve ComponentManager"));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGameInstance::Add_Timer(const _tchar* pTimerTag)
{
	if (!m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(pTimerTag);
}

 _float CGameInstance::Compute_TimeDelta(const _tchar* pTimerTag)
{
	if (!m_pTimer_Manager)
		return 0.0f;

	return m_pTimer_Manager->Compute_DeltaTime(pTimerTag);
}

void CGameInstance::Tick_Engine(_float fDeltaTime)
{
	if (m_pLevelManager)
		m_pLevelManager->Tick(fDeltaTime);

	if (m_pObjectManager)
	{
		m_pObjectManager->Tick(fDeltaTime);
		m_pObjectManager->Late_Tick(fDeltaTime);
	}
}

HRESULT CGameInstance::Render_Engine()
{
	if (!m_pLevelManager)
		return E_FAIL;

	if (FAILED(m_pLevelManager->Render()))
		return E_FAIL;

	return S_OK;
}
void	CGameInstance::RenderBegin()
{
	m_pGraphicDev->Render_Begin();
}
void	CGameInstance::RenderEnd(HWND hWnd)
{
	m_pGraphicDev->Render_End(hWnd);
}

HRESULT CGameInstance::Open_Level(_uint eNextLevel, CLevel* pLevel)
{
	if (FAILED(m_pLevelManager->Open_Level(eNextLevel, pLevel)))
		return E_FAIL;

	return S_OK;
}

HRESULT CGameInstance::Add_Layer(_uint _iLayerIndex, const _tchar* _LayerTag, const _tchar* _ProtoTypeTag, void* _pArg)
{
	if (!m_pObjectManager)
		return E_FAIL;

	return m_pObjectManager->Add_Layer(_iLayerIndex, _LayerTag, _ProtoTypeTag, _pArg);
}

 HRESULT CGameInstance::Add_ProtoTypeObject(const _tchar* ProtoTypeTag, CGameObject* _pObject)
{
	if (!m_pObjectManager)
		return E_FAIL;

	return m_pObjectManager->Add_ProtoObject(ProtoTypeTag, _pObject);
}

CComponent* CGameInstance::Clone_ComponentObject(_uint _iLayerIndex, const _tchar* _pTag, void* _pArg)
{
	if (NULL == m_pComponentManager)
		return nullptr;

	return m_pComponentManager->Clone(_iLayerIndex, _pTag, _pArg);
}

void CGameInstance::Clear(_uint iLayerIndex)
{
	m_pObjectManager->Clear(iLayerIndex);
}

void CGameInstance::Free() 
{
	cout << "[CGameInstance Free]" << endl;
	Safe_Release(m_pObjectManager);
	Safe_Release(m_pComponentManager);
	Safe_Release(m_pGraphicDev);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pLevelManager);
}

void CGameInstance::Release_Engine()
{
	CGameInstance::Get_Instance()->Destroy_Instance();

	CLevel_Manager::Get_Instance()->Destroy_Instance();

	CObject_Manager::Get_Instance()->Destroy_Instance();

	CComponent_Manager::Get_Instance()->Destroy_Instance();

	CTimer_Manager::Get_Instance()->Destroy_Instance();

	CGraphic_Device::Get_Instance()->Destroy_Instance();

}

