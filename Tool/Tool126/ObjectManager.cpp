#include "stdafx.h"
#include "ObjectManager.h"
#include "Layer.h"
#include "GameObject.h"
IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{

}

void CObject_Manager::Tick(_float fDeltaTime)
{
	for (size_t i = 0; i < m_iLayerIndex; ++i)
	{
		if (!m_ArrayLayer[i].size())
			continue;

		LAYER::iterator iter_begin = m_ArrayLayer[i].begin();
		LAYER::iterator iter_end = m_ArrayLayer[i].end();

		while (iter_begin != iter_end)
		{
			(*iter_begin).second->Tick(fDeltaTime);
			++iter_begin;
		}
	}
}

void CObject_Manager::Late_Tick(_float fDeltaTime)
{
	for (size_t i = 0; i < m_iLayerIndex; ++i)
	{
		if (!m_ArrayLayer[i].size())
			continue;

		LAYER::iterator iter_begin = m_ArrayLayer[i].begin();
		LAYER::iterator iter_end = m_ArrayLayer[i].end();

		while (iter_begin != iter_end)
		{
			(*iter_begin).second->Late_Tick(fDeltaTime);
			++iter_begin;
		}
	}
}

HRESULT		CObject_Manager::Add_Layer(_uint _iLayerIndex, const _tchar* _LayerTag, const _tchar* _ProtoTypeTag, void* _pArg)
{
	cout << "입력 레이어 계층 : " << _iLayerIndex << endl;
	cout << "입력 레이어 태그 : " << _LayerTag << endl;
	if (_iLayerIndex >= m_iLayerIndex || 0 >= lstrlen(_LayerTag) || 0 >= lstrlen(_ProtoTypeTag))
		return E_FAIL;

	CGameObject* pInstance = Find_ProtoType(_ProtoTypeTag);
	if (!pInstance)
	{
		MSGBOX(TEXT("ProtoType GameObject Not Founded"));
		return E_FAIL;
	}

	CLayer* pLayer = (CLayer*)Find_Layer(_iLayerIndex, _LayerTag);

	if (!pLayer)
	{
		pLayer = CLayer::Create();

		if (!pLayer)
			return E_FAIL;

		if (FAILED(pLayer->Add_Object(pInstance->Clone(_pArg))))
			return E_FAIL;

		cout << "[복사객체] 레이어 생성 및 객체 추가 완료 " << endl;
		m_ArrayLayer[_iLayerIndex].emplace(_ProtoTypeTag, pLayer);
	}
	else
	{
		if (FAILED(pLayer->Add_Object(pInstance->Clone(NULL))))
			return E_FAIL;
	}
	return S_OK;
}

FORCEINLINE CGameObject* CObject_Manager::Find_ProtoType(const _tchar* _ProtoTypeTag)
{
	if (0 >= lstrlen(_ProtoTypeTag))
		return nullptr;

	PROTO::iterator iter = find_if(m_MapProtoType.begin(), m_MapProtoType.end(), [&](PROTO::value_type Tag)->bool
	{
		if (!lstrcmp(Tag.first, _ProtoTypeTag))
			return true;
		else
			return false;
	});

	if (iter == m_MapProtoType.end())
		return nullptr;

	return iter->second;
}

void*	CObject_Manager::Find_Layer(_uint _iLayerIndex, const _tchar* _LayerTag)
{
	if (_iLayerIndex >= m_iLayerIndex)
		return nullptr;

	if (0 >= lstrlen(_LayerTag))
		return nullptr;

	LAYER::iterator iter = find_if(m_ArrayLayer[_iLayerIndex].begin(), m_ArrayLayer[_iLayerIndex].end(), [&](LAYER::value_type Tag)->bool
	{
		if (!lstrcmp(_LayerTag, Tag.first))
			return true;
		else
			return false;
	});

	if (iter == m_ArrayLayer[_iLayerIndex].end())
		return nullptr;

	return iter->second;
}

void CObject_Manager::Free()
{
	for (size_t i = 0; i < m_iLayerIndex; ++i)
	{
		LAYER::iterator iter_begin = m_ArrayLayer[i].begin();
		LAYER::iterator iter_end = m_ArrayLayer[i].end();

		while (iter_begin != iter_end)
		{
			Safe_Release(iter_begin->second);
			++iter_begin;
		}
		m_ArrayLayer[i].swap(LAYER());
		m_ArrayLayer[i].clear();
	}
	Safe_Delete_Array(m_ArrayLayer);

	PROTO::iterator iter_begin = m_MapProtoType.begin();
	PROTO::iterator iter_end = m_MapProtoType.end();

	while (iter_begin != iter_end)
	{
		Safe_Release(iter_begin->second);
		++iter_begin;
	}

	m_MapProtoType.swap(PROTO());
	m_MapProtoType.clear();

	cout << "[CObject_Manager Free]" << endl;
}