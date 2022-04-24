#include "stdafx.h"
#include "Renderer.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 _pDev):
	CComponent(_pDev)
{

}

HRESULT CRenderer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (!m_pGraphicDev)
	{
		MSGBOX(TEXT("Failed to Init CRenderer"));
		return E_FAIL;
	}

	m_RenderList = new RENDERLIST[RENDER_END];
	return S_OK;
}

HRESULT CRenderer::Draw_Renderer()
{
	if (FAILED(Render_Priority()))
	{
		MSGBOX(TEXT("Render Failed to Priority"));
		return E_FAIL;
	}

	if (FAILED(Render_Nonalphablend()))
	{
		MSGBOX(TEXT("Render Failed to Nonalphablend"));
		return E_FAIL;
	}

	if (FAILED(Render_Alphablend()))
	{
		MSGBOX(TEXT("Render Failed to Alphablend"));
		return E_FAIL;
	}

	if (FAILED(Render_Ui()))
	{
		MSGBOX(TEXT("Render Failed to Ui"));
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CRenderer::Add_RenderList(RENDERGROUP _eGroup, CGameObject* _pObject)
{
	if (_eGroup >= RENDERGROUP::RENDER_END || NULL == _pObject)
		return E_FAIL;

	m_RenderList[_eGroup].push_back(_pObject);

	_pObject->AddRef();

	return S_OK;
}

FORCEINLINE HRESULT CRenderer::Render_Priority()
{
	if (!m_RenderList)
		return S_OK;

	if (!m_RenderList[RENDERGROUP::RENDER_PRIORITY].size())
		return S_OK;

	for (auto& elem : m_RenderList[RENDERGROUP::RENDER_PRIORITY])
	{
		if (FAILED(elem->Render()))
			return E_FAIL;

		Safe_Release(elem);
	}
	m_RenderList[RENDERGROUP::RENDER_PRIORITY].swap(RENDERLIST());
	m_RenderList[RENDERGROUP::RENDER_PRIORITY].clear();
	return S_OK;
}

FORCEINLINE HRESULT CRenderer::Render_Nonalphablend()
{
	if (!m_RenderList[RENDERGROUP::RENDER_NONALPHABLEND].size())
		return S_OK;

	for (auto& elem : m_RenderList[RENDERGROUP::RENDER_NONALPHABLEND])
	{
		if (FAILED(elem->Render()))
			return E_FAIL;

		Safe_Release(elem);
	}
	m_RenderList[RENDERGROUP::RENDER_NONALPHABLEND].swap(RENDERLIST());
	m_RenderList[RENDERGROUP::RENDER_NONALPHABLEND].clear();
	return S_OK;
}
FORCEINLINE HRESULT CRenderer::Render_Alphablend()
{
	if (!m_RenderList[RENDERGROUP::RENDER_ALPHABLEND].size())
		return S_OK;

	for (auto& elem : m_RenderList[RENDERGROUP::RENDER_ALPHABLEND])
	{
		if (FAILED(elem->Render()))
			return E_FAIL;

		Safe_Release(elem);
	}
	m_RenderList[RENDERGROUP::RENDER_ALPHABLEND].swap(RENDERLIST());
	m_RenderList[RENDERGROUP::RENDER_ALPHABLEND].clear();
	return S_OK;
}
FORCEINLINE HRESULT CRenderer::Render_Ui()
{
	if (!m_RenderList[RENDERGROUP::RENDER_UI].size())
		return S_OK;

	for (auto& elem : m_RenderList[RENDERGROUP::RENDER_UI])
	{
		if (FAILED(elem->Render()))
			return E_FAIL;

		Safe_Release(elem);
	}
	m_RenderList[RENDERGROUP::RENDER_UI].swap(RENDERLIST());
	m_RenderList[RENDERGROUP::RENDER_UI].clear();
	return S_OK;
}

CComponent* CRenderer::Clone(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return NULL;

	if (FAILED(this->NativeConstruct(pArg)))
		return NULL;

	return this;
}
 void CRenderer::Free()
{
	 cout << "[CRenderer Free]" << endl;
	 for (size_t i = 0; i < RENDERGROUP::RENDER_END; ++i)
	 {
		 for (auto& elem : m_RenderList[i])
		 {
			 Safe_Release(elem);
		 }
		 m_RenderList[i].swap(RENDERLIST());
		 m_RenderList[i].clear();
	}
	 Safe_Delete_Array(m_RenderList);
}