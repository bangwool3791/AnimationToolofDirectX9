#include "stdafx.h"
#include "Layer.h"

HRESULT CLayer::Native_Construct()
{
	return S_OK;
}

HRESULT CLayer::Render()
{
	return S_OK;
}

HRESULT CLayer::Add_Object(CGameObject* _pGameObject)
{
	if (!_pGameObject)
		return E_FAIL;

	m_listGameObject.push_back(_pGameObject);
	return S_OK;
}

CLayer* CLayer::Create()
{
	CLayer* pInstance = new CLayer();

	if (FAILED(pInstance->Native_Construct()))
		return NULL;

	return pInstance;
}

//Free에서 실패할 경우 대비해서 다시 만들 것.
void CLayer::Free()
{
	GAMEOBJECTLIST::iterator iter = m_listGameObject.begin();
	GAMEOBJECTLIST::iterator iter_end = m_listGameObject.end();

	for (; iter != iter_end; ++iter)
	{
		if(*iter)
			Safe_Release(*iter);
	}
}