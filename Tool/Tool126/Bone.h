#include "Component.h"
#include "Transform.h"
#include "VIBuffer_Cube.h"

class CBone : public CComponent
{
private:
	FORCEINLINE explicit CBone(LPDIRECT3DDEVICE9 pGraphic_Device)
		:m_pGraphicDev(pGraphic_Device)
		, CComponent(pGraphic_Device)
	{
	}
	FORCEINLINE explicit CBone(const CBone& rhs)
		: m_pGraphicDev(rhs.m_pGraphicDev)
		, CComponent(rhs.m_pGraphicDev)

	{
	}
	virtual ~CBone() = default;

public:
private:
	LPDIRECT3DDEVICE9 m_pGraphicDev = NULL;
	map<const TCHAR*, CTransform*>* m_mapBone = NULL;
	typedef map<const TCHAR*, CTransform*> MAP_BONE;
	map<const TCHAR*, CVIBuffer_Cube*>* m_mapCube = NULL;
	typedef map<const TCHAR*, CVIBuffer_Cube*> MAP_CUBE;
private:
	virtual HRESULT NativeConstruct_Prototype()
	{
		if (!m_pGraphicDev)
			return E_FAIL;

		if (m_mapBone || m_mapCube)
		{
			MSGBOX(TEXT("Already map in the bone allocated"));
			return E_FAIL;
		}

		m_mapCube = new MAP_CUBE[BONE_LAYER_END];
		m_mapBone = new MAP_BONE[BONE_LAYER_END];

		if (!m_mapBone || !m_mapCube)
			return E_FAIL;

		return S_OK;
	};
	virtual HRESULT NativeConstruct(void* pArg)
	{
		if (!m_pGraphicDev || m_mapBone || m_mapCube)
			return E_FAIL;

		if (m_mapBone || m_mapCube)
		{
			MSGBOX(TEXT("Already map in the bone allocated"));
			return E_FAIL;
		}

		m_mapCube = new MAP_CUBE[BONE_LAYER_END];
		m_mapBone = new MAP_BONE[BONE_LAYER_END];

		if (!m_mapBone || !m_mapCube)
			return E_FAIL;

		return S_OK;
	};
public:
	HRESULT Render()
	{
		for (size_t i = 0; i < BONE_LAYER_END; ++i)
		{
			MAP_CUBE::iterator CubeBegin = m_mapCube[i].begin();
			MAP_CUBE::iterator CubeEnd = m_mapCube[i].end();

			MAP_BONE::iterator BoneBegin = m_mapBone[i].begin();
			MAP_BONE::iterator BoneEnd = m_mapBone[i].end();

			while (CubeBegin != CubeEnd && BoneBegin != BoneEnd)
			{
				if (FAILED(BoneBegin->second->Bind_OnGraphicDevice()))
					return E_FAIL;

				Engine::_float4x4			ViewMatrix, ProjMatrix;

				D3DXMatrixLookAtLH(&ViewMatrix, &D3DXVECTOR3(0.f, 2.f, -10.f), &D3DXVECTOR3(0.f, 0.f, 0.f), &D3DXVECTOR3(0.f, 1.f, 0.f));
				m_pGraphicDev->SetTransform(D3DTS_VIEW, &ViewMatrix);

				D3DXMatrixPerspectiveFovLH(&ProjMatrix, D3DXToRadian(60.f), 1280 / (_float)700, 0.2f, 300.f);

				m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &ProjMatrix);

				if (FAILED(CubeBegin->second->Render()))
					return E_FAIL;

				++CubeBegin;
				++BoneBegin;
			}

			//if (CubeBegin == CubeEnd && BoneBegin == BoneEnd)
			//{
			//	MSGBOX(TEXT("Bone Render missing Some Object"));
			//	return E_FAIL;
			//}
		}
		return S_OK;
	}
public:
	FORCEINLINE HRESULT Add_Bone(BONE_LAYER _Layer, const TCHAR* _key, TRANSFORMDESC& Rhs, _float* fRadius)
	{
		if (!fRadius)
		{
			MSGBOX(TEXT("fRadius Parameter Pointer is null in AddBone"));
			return E_FAIL;
		}
		if (!m_mapCube || !m_mapBone)
		{
			MSGBOX(TEXT("Container is NULL"));
			return E_FAIL;
		}

		if (!m_pGraphicDev)
		{
			MSGBOX(TEXT("Graphic Device Not Setting"));
			return E_FAIL;
		}

		if (_Layer >= BONE_LAYER_END)
		{
			MSGBOX(TEXT("Failed to Add Bone Layer Index Error!"));
			return E_FAIL;
		}

		Rhs.szKey = const_cast<TCHAR*>(_key);
		//Add to Trans Bone
		MAP_BONE::iterator iter = find_if(m_mapBone[_Layer].begin(), m_mapBone[_Layer].end(), [&](MAP_BONE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});

		if (iter != m_mapBone[_Layer].end())
		{
			MSGBOX(TEXT("Already Inserted Bone"));
			return E_FAIL;
		}
		CTransform* pIns = CTransform::Create(m_pGraphicDev);
		m_mapBone[_Layer].emplace(_key, (CTransform*)pIns->Clone((void*)&Rhs));
		Safe_Release(pIns);

		//Add to Cube Bone
		MAP_CUBE::iterator Cubeiter = find_if(m_mapCube[_Layer].begin(), m_mapCube[_Layer].end(), [&](MAP_CUBE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});

		if (Cubeiter != m_mapCube[_Layer].end())
		{
			MSGBOX(TEXT("Already Inserted Cube"));
			return E_FAIL;
		}
		//float형 배열을 입력 받아 팔다리 삭제 할 수 있도록 할 것.
		CVIBuffer_Cube* pCube = CVIBuffer_Cube::Create(m_pGraphicDev);
		m_mapCube[_Layer].emplace(_key, (CVIBuffer_Cube*)pCube->Clone(fRadius));
		Safe_Release(pCube);
		return S_OK;
	}

	FORCEINLINE CComponent* Find_Bone(BONE_LAYER _Layer, const TCHAR* _key)
	{
		if (_Layer >= BONE_LAYER_END)
		{
			MSGBOX(TEXT("Failed to Find Bone"));
			return NULL;
		}

		MAP_BONE::iterator iter = find_if(m_mapBone[_Layer].begin(), m_mapBone[_Layer].end(), [&](MAP_BONE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});
		
		if (iter == m_mapBone[_Layer].end())
		{
			MSGBOX(TEXT("Cannot find Bone"));
			return nullptr;
		}
		return (CComponent*)iter->second;
	}

	FORCEINLINE CComponent* Find_Cube(BONE_LAYER _Layer, const TCHAR* _key)
	{
		if (_Layer >= BONE_LAYER_END)
		{
			MSGBOX(TEXT("Failed to Find Bone"));
			return NULL;
		}

		MAP_CUBE::iterator iter = find_if(m_mapCube[_Layer].begin(), m_mapCube[_Layer].end(), [&](MAP_CUBE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});

		if (iter == m_mapCube[_Layer].end())
		{
			MSGBOX(TEXT("Cannot find Cube"));
			return nullptr;
		}
		return (CComponent*)iter->second;
	}

	FORCEINLINE HRESULT EraseBone(BONE_LAYER _Layer, const TCHAR* _key)
	{
		MAP_BONE::iterator iter = find_if(m_mapBone[_Layer].begin(), m_mapBone[_Layer].end(), [&](MAP_BONE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});

		MAP_CUBE::iterator iter2 = find_if(m_mapCube[_Layer].begin(), m_mapCube[_Layer].end(), [&](MAP_CUBE::value_type Pair)->bool
		{
			if (!lstrcmp(Pair.first, _key))
				return true;
			else
				return false;
		});

		m_mapBone[_Layer].erase(iter);
		m_mapCube[_Layer].erase(iter2);

		return S_OK;
	}

	FORCEINLINE HRESULT Setting_ParentBone(BONE_LAYER _Layer, const TCHAR* _parentkey, const TCHAR* _childkey)
	{
		if (_Layer >= BONE_LAYER_END)
		{
			MSGBOX(TEXT("Failed to Setting Parent Bone"));
			return E_FAIL;
		}
		CTransform* pChildBone = (CTransform*)Find_Bone(_Layer, _childkey);
		Safe_AddRef(pChildBone);
		CTransform* pParentBone = (CTransform*)Find_Bone(_Layer, _parentkey);
		Safe_AddRef(pParentBone);

		if (!pChildBone || !pParentBone)
		{
			MSGBOX(TEXT("Child Bone or Parent Bone is not founded"));
			return E_FAIL;
		}

		pChildBone->Bind_Parent(*pParentBone, const_cast<TCHAR*>(_childkey));
		Safe_Release(pChildBone);
		Safe_Release(pParentBone);

		return S_OK;
	}

	HRESULT Clear_BoneAngle(BONE_LAYER _Layer)
	{
		MAP_BONE::iterator Begin = m_mapBone[_Layer].begin();
		MAP_BONE::iterator End = m_mapBone[_Layer].end();

		while (Begin != End)
		{
			Begin->second->Init_LocalAngle();
			++Begin;
		}
		return S_OK;
	}
public:
	static CComponent * Create(LPDIRECT3DDEVICE9 pGraphicDevice)
	{
		CBone* pIns = new CBone(pGraphicDevice);

		if (FAILED(pIns->NativeConstruct_Prototype()))
		{
			MSGBOX(TEXT("Failed to Init in CBon Prototype"));
			return NULL;
		}
		return pIns;
	}
	virtual CComponent* Clone(void* pArg)
	{
		CBone* pIns = new CBone(*this);

		if (FAILED(pIns->NativeConstruct(pArg)))
		{
			MSGBOX(TEXT("Failed to Init in CBone Clone"));
			return NULL;
		}
		return pIns;
	}
	virtual void Free() override
	{
		__super::Free();

		for (size_t i = 0; i < BONE_LAYER_END; ++i)
		{
			for (auto& elem : m_mapBone[i])
			{
				MSGBOX(elem.second->Get_Tag());

				Safe_Release(elem.second);
			}
		}
		Safe_Delete_Array(m_mapBone);

		for (size_t i = 0; i < BONE_LAYER_END; ++i)
		{
			for (auto& elem : m_mapCube[i])
			{
				Safe_Release(elem.second);
			}
		}
		Safe_Delete_Array(m_mapCube);
	}
};
END