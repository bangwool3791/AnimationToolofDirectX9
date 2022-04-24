#include "stdafx.h"
#include "VIBuffer_Rect.h"

HRESULT CVIBuffer_Rect::NativeConstruct_Prototype()
{
#pragma region VERTEX_BUFFER
	m_iNumVertices = 4;
	m_iStride = sizeof(VTXTEX);
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;

	if (!m_pVB)
	{
		MSGBOX(TEXT("m_pVB is NULL in Init CVIBuffer"));
		return E_FAIL;
	}

	VTXTEX * pVetex;

	if (FAILED(m_pVB->Lock(0, m_iNumVertices * m_iStride, (void**)&pVetex, TRUE)))
		return E_FAIL;

	pVetex[0].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.f);
	pVetex[0].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVetex[1].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.f);
	pVetex[1].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVetex[2].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.f);
	pVetex[2].vTexUV = D3DXVECTOR2(1.f, 1.f);

	pVetex[3].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
	pVetex[3].vTexUV = D3DXVECTOR2(0.f, 1.f);

	if (FAILED(m_pVB->Unlock()))
		return E_FAIL;

#pragma endregion
#pragma region INDEX_BUFFER

	m_iPrimitiveIndicesSize = sizeof(FACEINDICES16);

	m_eIndexFormat = D3DFMT_INDEX16;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	FACEINDICES16* pIndices = NULL;

	if (m_pIB->Lock(0, 0, (void**)&pIndices, 0))
		return E_FAIL;

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	if (m_pIB->Unlock())
		return E_FAIL;

#pragma endregion
	return S_OK;
}

HRESULT CVIBuffer_Rect::NativeConstruct(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	return S_OK;
}

CVIBuffer_Rect* CVIBuffer_Rect::Create(LPDIRECT3DDEVICE9 pDev)
{
	CVIBuffer_Rect* pInstance = new CVIBuffer_Rect(pDev);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX(TEXT("Failed to Create CVIBuffer Instance "));
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CVIBuffer_Rect::Clone(void* pArg)
{
	CVIBuffer_Rect* pInstance = new CVIBuffer_Rect(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX(TEXT("Failed to Clone CVIBuffer Instance "));
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CVIBuffer_Rect::Free()
{
	__super::Free();
	cout << "CVIBuffer_Rect Free" << endl;
}