#include "stdafx.h"
#include "Level.h"

CLevel::CLevel(LPDIRECT3DDEVICE9 pDevice)
	:m_pGraphicDev(pDevice)
{
	Safe_AddRef(m_pGraphicDev);
}

HRESULT CLevel::NativeConstruct()
{
	if (!m_pGraphicDev)
		return E_FAIL;
	return S_OK;
}

void CLevel::Tick(_float fDeltaTime)
{

}

HRESULT CLevel::Render()
{
	if (!m_pGraphicDev)
		return E_FAIL;
	return S_OK;
}

void CLevel::Free()
{
	cout << "CLevel Free" << endl;
	Safe_Release(m_pGraphicDev);
}