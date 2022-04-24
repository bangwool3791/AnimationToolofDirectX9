#pragma once
#include "Base.h"
#include "Layer.h"
#include "GameObject.h"


class CObject_Manager : public CBase
{
DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;
public :
	void Tick(_float fDeltaTime);
	void Late_Tick(_float fDeltaTime);
	FORCEINLINE HRESULT	CObject_Manager::ReserveLayer(_uint _iLayerIndex)
	{
		if (m_ArrayLayer)
			return E_FAIL;

		m_ArrayLayer = new LAYER[_iLayerIndex];

		m_iLayerIndex = _iLayerIndex;

		return S_OK;
	}
	FORCEINLINE HRESULT		CObject_Manager::Add_ProtoObject(const _tchar* _ProtoTypeTag, CGameObject* _pGameObject)
	{
		if (NULL == _pGameObject || 0 >= lstrlen(_ProtoTypeTag))
			return E_FAIL;

		CGameObject* pInstance = Find_ProtoType(_ProtoTypeTag);

		if (pInstance)
		{
			MSGBOX(TEXT("Already ProtoType Object Created : CObject_Manager Add_ProtoObject"));
			return E_FAIL;
		}
		cout << "프로토타입 객체 생성 완료 " << endl;
		m_MapProtoType.emplace(_ProtoTypeTag, _pGameObject);

		return S_OK;
	}

	CGameObject*	CObject_Manager::Get_Object(_uint _iLayerIndex, const _tchar* _LayerTag)
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

		return iter->second->Get_Object();
	}


	HRESULT		CObject_Manager::Add_Layer(_uint _iLayerIndex, const _tchar* _LayerTag, const _tchar* _ProtoTypeTag, void* _pArg);
private :
	FORCEINLINE CGameObject* CObject_Manager::Find_ProtoType(const _tchar* _ProtoTypeTag);
	void*	 Find_Layer(_uint _iLayerIndex, const _tchar* _LayerTag);
private :
	map<const _tchar*, CGameObject*> m_MapProtoType;
	typedef map<const _tchar*, CGameObject*> PROTO;
	map<const _tchar*, CLayer*>*  m_ArrayLayer = nullptr;
	typedef map<const _tchar*, CLayer*>   LAYER;
	_uint	m_iLayerIndex = 0;
public :
	virtual void	Free() override;

	FORCEINLINE void CObject_Manager::Clear(_uint iLayerIndex)
	{
		if (!m_ArrayLayer[iLayerIndex].size())
			return;

		LAYER::iterator beginIter = m_ArrayLayer[iLayerIndex].begin();
		LAYER::iterator endIter = m_ArrayLayer[iLayerIndex].end();

		while (beginIter != endIter)
		{
			Safe_Release(beginIter->second);
			++beginIter;
		}

		m_ArrayLayer[iLayerIndex].swap(LAYER());
		m_ArrayLayer[iLayerIndex].clear();

		return;
	}
};