#pragma once
#include "Component.h"

class CVIBuffer abstract : public CComponent
{
protected:
	FORCEINLINE CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice) : CComponent(pDevice)
	{
	}

	FORCEINLINE CVIBuffer::CVIBuffer(const CVIBuffer & Rhs) 
		: CComponent(Rhs)
		, m_pVB(Rhs.m_pVB)
		, m_iNumVertices(Rhs.m_iNumVertices)
		, m_iStride(Rhs.m_iStride)
		, m_dwFVF(Rhs.m_dwFVF)
		, m_ePrimitiveType(Rhs.m_ePrimitiveType)
		, m_iNumPrimitive(Rhs.m_iNumPrimitive)
		, m_pIB(Rhs.m_pIB)
		, m_iPrimitiveIndicesSize(Rhs.m_iPrimitiveIndicesSize)
	{
		Safe_AddRef(m_pIB);
		Safe_AddRef(m_pVB);
	}
	virtual ~CVIBuffer() = default;

protected :
	FORCEINLINE HRESULT Create_VertexBuffer()
	{
		//cout << "VP Buffer Param" << endl;
		//cout << "m_iNumVertices " << m_iNumVertices << endl;
		//cout << "m_iNumVertices " << m_iNumPrimitive << endl;
		//cout << "m_iNumVertices " << m_dwFVF << endl;
		//cout << "m_iNumVertices " << m_pVB << endl;

		if (FAILED(m_pGraphicDev->CreateVertexBuffer(m_iNumVertices * m_iStride, NULL, m_dwFVF, D3DPOOL_MANAGED, &m_pVB, 0)))
		{
			MSGBOX(TEXT("Failed to Create VPBuffer"));
			return E_FAIL;
		}


		return TRUE;
	}
	FORCEINLINE HRESULT Create_IndexBuffer()
	{

		if (FAILED(m_pGraphicDev->CreateIndexBuffer(m_iPrimitiveIndicesSize * m_iNumPrimitive, NULL, m_eIndexFormat, D3DPOOL_MANAGED, &m_pIB, 0)))
		{
			MSGBOX(TEXT("Failed to Create VIBuffer"));
			return E_FAIL;
		}


		return TRUE;
	}
protected:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB = nullptr;
	_uint						m_iNumVertices = 0;
	_uint						m_iStride = 0; 
	_ulong						m_dwFVF = 0;
	D3DPRIMITIVETYPE			m_ePrimitiveType;
	_uint						m_iNumPrimitive = 0;
protected:
	LPDIRECT3DINDEXBUFFER9		m_pIB = nullptr;
	_uint						m_iPrimitiveIndicesSize = 0;
	D3DFORMAT					m_eIndexFormat;
public :

	virtual	HRESULT Render();
public:
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};
END

