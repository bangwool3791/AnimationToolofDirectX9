#include "stdafx.h"
#include "Component.h"

CComponent::CComponent(LPDIRECT3DDEVICE9 pDevice):m_pGraphicDev(pDevice)
{
	Safe_AddRef(m_pGraphicDev);
}

CComponent::CComponent(const CComponent & Rhs): m_pGraphicDev(Rhs.m_pGraphicDev)
{
	Safe_AddRef(m_pGraphicDev);
}

 HRESULT CComponent::NativeConstruct_Prototype()
{
	 if (!m_pGraphicDev)
		 return E_FAIL;

	 return S_OK;
}

 HRESULT CComponent::NativeConstruct(void* pArg)
{
	 if (!m_pGraphicDev)
		 return E_FAIL;

	 return S_OK;
}

 void CComponent::Free()
 {
	 //cout << "[CComponent Free]" << endl;
	 Safe_Release(m_pGraphicDev);
 }