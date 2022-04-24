#pragma once
#include "Base.h"
#include "GameObject.h"
#include "Timer_Manager.h"
#include "LevelManager.h"
#include "Graphic_Device.h"
#include "ComponentManager.h"
#include "ObjectManager.h"
#include "Input_Device.h"

class CGameInstance final : public CBase
{
DECLARE_SINGLETON(CGameInstance)
public :
	CGameInstance();
	virtual ~CGameInstance() = default;

public: 
	/* For.Timer_Manager */
	HRESULT Add_Timer(const _tchar* pTimerTag);
	_float CGameInstance::Compute_TimeDelta(const _tchar* pTimerTag);
	HRESULT CGameInstance::Initialize_Engine(HINSTANCE hInstance, _uint iLayerIndex, const GRAPHIC_DEVICE_DESC& _stGpDev, LPDIRECT3DDEVICE9* _ppDevice);
	void	Tick_Engine(_float fDeltaTime);
	HRESULT Render_Engine();
	void	RenderBegin();
	void	RenderEnd(HWND hWnd = 0);
public :
	FORCEINLINE _byte CGameInstance::Get_DIKeyState(_ubyte byKeyID)
	{
		if (!m_pInput_Device)
			return 0;

		return m_pInput_Device->Get_DIKeyState(byKeyID);
	}

	FORCEINLINE _long CGameInstance::Get_DIMMoveState(CInput_Device::DIMM eMouseMoveID)
	{
		if (!m_pInput_Device)
			return 0;

		return m_pInput_Device->Get_DIMMoveState(eMouseMoveID);
	}

	FORCEINLINE _byte CGameInstance::Get_DIMButtonState(CInput_Device::DIMB eMouseButtonID)
	{
		if (!m_pInput_Device)
			return 0;

		return m_pInput_Device->Get_DIMButtonState(eMouseButtonID);
	}
public:
	/* For.Level_Manager */
	HRESULT Open_Level(_uint eNextLevel, class CLevel* pLevel);
public: 
	/* For.Object_Manager */
	 HRESULT Add_ProtoTypeObject(const _tchar* ProtoTypeTag,  CGameObject* _pObject);
	HRESULT Add_Layer(_uint _iLayerIndex, const _tchar* _LayerTag, const _tchar* _ProtoTypeTag, void* _pArg);
	CGameObject* Get_Object(_uint _iLayerIndex, const _tchar* _LayerTag)
	{
		if (!m_pObjectManager)
			return NULL;

		return m_pObjectManager->Get_Object(_iLayerIndex, _LayerTag);
	}
public: 

	/* For.Component_Manager */
	FORCEINLINE HRESULT CGameInstance::Add_ComponentObject(_uint _iLayerIndex, const _tchar* pTag, CComponent* pComponent)
	{
		if (!m_pComponentManager)
			return E_FAIL;

		return m_pComponentManager->Add_ComponentObject(_iLayerIndex, pTag, pComponent);
	}

	CComponent* Clone_ComponentObject(_uint _iLayerIndex, const _tchar* pTag, void* _pArg = nullptr);
private:
	 CTimer_Manager*	m_pTimer_Manager = nullptr;
	 CGraphic_Device*	m_pGraphicDev = nullptr;
	 CLevel_Manager*     m_pLevelManager = nullptr;
	 CObject_Manager*    m_pObjectManager = nullptr;
	 CComponent_Manager* m_pComponentManager = nullptr;
	 CInput_Device*		 m_pInput_Device = nullptr;
public:
	virtual void	 Free() override;
	static void		 Release_Engine();
	void Clear(_uint iLayerIndex);
};
