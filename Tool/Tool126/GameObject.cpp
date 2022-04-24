#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"
#include "GameInstance.h"

CGameObject::CGameObject(LPDIRECT3DDEVICE9 _pDevice): m_pGraphicDev(_pDevice)
{
	memset(&m_vPos, 0, sizeof(_float3));
	Safe_AddRef(m_pGraphicDev);
}

CGameObject::CGameObject(const CGameObject& _rhs)
	: m_pGraphicDev(_rhs.m_pGraphicDev)
{
	Safe_AddRef(m_pGraphicDev);
}


void CGameObject::Tick(_float _fDeltaTime)
{
	
}

void CGameObject::Late_Tick(_float _fDeltaTime)
{

}

HRESULT CGameObject::Render()
{
	return S_OK;
}

HRESULT CGameObject::NativeConstruct_Prototype()
{
	if (!m_pGraphicDev)
		return E_FAIL;

	return S_OK;
}

HRESULT CGameObject::NativeConstruct(void* pArg)
{
	if (!m_pGraphicDev)
		return E_FAIL;

	return S_OK;
}

CGameObject* CGameObject::Clone(void* pArg)
{
	return nullptr;
}

void CGameObject::Free()
{
	cout << "CGameObject Free" << endl;
	if(m_pGraphicDev)
	Safe_Release(m_pGraphicDev);
}