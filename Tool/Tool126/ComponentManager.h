#pragma once

#include "VIBuffer_Rect.h"
#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "VIBuffer_Cube.h"
#include "Bone.h"


class CComponent_Manager final : public CBase
{
	DECLARE_SINGLETON(CComponent_Manager)
private:
	FORCEINLINE CComponent_Manager():m_MapProCom(NULL)
	{
	}

	virtual ~CComponent_Manager()
	{
	}

private :
	_uint m_iLayerIndex = 0;
	map<const TCHAR*,  CComponent*>* m_MapProCom = NULL;
	typedef map<const TCHAR*, CComponent*>	MAPCOMPONENT;
public :
	FORCEINLINE HRESULT CComponent_Manager::Reserve_ComponentMgr(_uint iLayer)
	{
		if (NULL != m_MapProCom || 0 >= iLayer)
		{
			MSGBOX(TEXT("Failed to Reserve CComponent_Manager"));
			return E_FAIL;
		}

		m_iLayerIndex = iLayer;

		m_MapProCom = new MAPCOMPONENT[iLayer];
		return S_OK;
	}

	FORCEINLINE HRESULT CComponent_Manager::Add_ComponentObject(_uint iLayer, const TCHAR* pTag, CComponent* pComponent)
	{
		if (0 >= lstrlen(pTag) || iLayer >= m_iLayerIndex || nullptr == pComponent || NULL == m_MapProCom)
		{
			MSGBOX(TEXT("Failed to Create CComponent_Manager [Parameter Failed]"));
			return E_FAIL;
		}

		if (nullptr != Find_ComponentObject(iLayer, pTag))
		{
			MSGBOX(TEXT("Failed to Create CComponent_Manager [Find Failed]"));
			return E_FAIL;
		}

		m_MapProCom[iLayer].emplace(pTag, pComponent);
		return S_OK;
	}

	FORCEINLINE CComponent* CComponent_Manager::Find_ComponentObject(_uint iLayer, const TCHAR* pTag)
	{
		MAPCOMPONENT::iterator iter = find_if(m_MapProCom[iLayer].begin(), m_MapProCom[iLayer].end(),
			[&](MAPCOMPONENT::value_type Tag)->bool
		{
			if (!lstrcmp(Tag.first, pTag))
				return true;
			else
				return false;
		});

		if (iter == m_MapProCom[iLayer].end())
			return nullptr;
		else
			return iter->second;
	}

	FORCEINLINE CComponent* CComponent_Manager::Clone(_uint iLayer, const TCHAR* pTag, void* pArg)
	{
		if (iLayer >= m_iLayerIndex || NULL == m_MapProCom || 0 >= lstrlen(pTag))
			return nullptr;

		CComponent* pInstance = Find_ComponentObject(iLayer, pTag);

		if (NULL == pInstance)
			return nullptr;

		CComponent* pRet = pInstance->Clone(pArg);

		return pRet;
	}

public :
	virtual void Free() override;
};


