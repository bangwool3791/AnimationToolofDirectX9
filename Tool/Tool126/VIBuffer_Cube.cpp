#include "stdafx.h"
#include "VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphicDevice)
	:CVIBuffer(pGraphicDevice)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube & rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Cube::NativeConstruct_Prototype()
{
	m_iNumVertices = 8;
	m_iStride = sizeof(VTXTEX);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 12;

	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;

	if (FAILED(__super::NativeConstruct_Prototype()))
		return E_FAIL;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;
	//VERTEXTXT* pVertices = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertices, 0);

	pVertices[0].vPosition = _float3(-0.05f, 0.05f, -0.05f);
	pVertices[0].vTexUV = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(0.05f, 0.05f, -0.05f);
	pVertices[1].vTexUV = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(0.05f, -0.05f, -0.05f);
	pVertices[2].vTexUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.05f, -0.05f, -0.05f);
	pVertices[3].vTexUV = _float2(0.f, 1.f);

	pVertices[4].vPosition = _float3(-0.05f, 0.05f, 0.05f);
	pVertices[4].vTexUV = _float2(1.f, 0.f);

	pVertices[5].vPosition = _float3(0.05f, 0.05f, 0.05f);
	pVertices[5].vTexUV = _float2(0.f, 0.f);

	pVertices[6].vPosition = _float3(0.05f, -0.05f, 0.05f);
	pVertices[6].vTexUV = _float2(0.f, 1.f);

	pVertices[7].vPosition = _float3(-0.05f, -0.05f, 0.05f);
	pVertices[7].vTexUV = _float2(1.f, 1.f);

	m_pVB->Unlock();

	m_iPrimitiveIndicesSize = sizeof(FACEINDICES16);
	m_eIndexFormat = D3DFMT_INDEX16;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	//FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	pIndices[2]._0 = 4;
	pIndices[2]._1 = 5;
	pIndices[2]._2 = 1;

	pIndices[3]._0 = 4;
	pIndices[3]._1 = 1;
	pIndices[3]._2 = 0;

	pIndices[4]._0 = 5;
	pIndices[4]._1 = 4;
	pIndices[4]._2 = 6;

	pIndices[5]._0 = 6;
	pIndices[5]._1 = 4;
	pIndices[5]._2 = 7;

	pIndices[6]._0 = 3;
	pIndices[6]._1 = 2;
	pIndices[6]._2 = 7;

	pIndices[7]._0 = 7;
	pIndices[7]._1 = 2;
	pIndices[7]._2 = 6;

	pIndices[8]._0 = 3;
	pIndices[8]._1 = 7;
	pIndices[8]._2 = 0;

	pIndices[9]._0 = 0;
	pIndices[9]._1 = 7;
	pIndices[9]._2 = 4;

	pIndices[10]._0 = 1;
	pIndices[10]._1 = 5;
	pIndices[10]._2 = 2;

	pIndices[11]._0 = 2;
	pIndices[11]._1 = 5;
	pIndices[11]._2 = 6;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Cube::NativeConstruct(void * pArg)
{
	m_iNumVertices = 8;
	m_iStride = sizeof(VTXTEX);
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 12;

	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1;

	if (FAILED(__super::NativeConstruct(pArg)))
		return E_FAIL;

	if (FAILED(__super::Create_VertexBuffer()))
		return E_FAIL;
	//VERTEXTXT* pVertices = nullptr;

	float* pRadius = (float*)pArg;

	if (!pRadius)
		MSGBOX(TEXT("Cube Copy Object's radius pointer is null"));

	float fWidth = pRadius[0];
	float fTopHeight = pRadius[1];
	float fBottomHeight = pRadius[2];
	float fPos = pRadius[3];

	m_stShape.fWidth = fWidth;
	m_stShape.fTop = fTopHeight;
	m_stShape.fBottom = fBottomHeight;
	m_stShape.fPos = fPos;

	//float fPos = pRadius[3];
	m_pVB->Lock(0, 0, (void**)&pVertices, 0);
	//fHeight = fHeight + -1.f;
	pVertices[0].vPosition = _float3(-1.f * fWidth, fTopHeight + fPos, -1.f * fWidth);
	pVertices[0].vTexUV = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(fWidth, fTopHeight + fPos, -1.f * fWidth);
	pVertices[1].vTexUV = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(fWidth, fBottomHeight + fPos, -1.f * fWidth);
	pVertices[2].vTexUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-1.f * fWidth, fBottomHeight + fPos, -1.f * fWidth);
	pVertices[3].vTexUV = _float2(0.f, 1.f);

	pVertices[4].vPosition = _float3(-1.f * fWidth, fTopHeight + fPos, fWidth);
	pVertices[4].vTexUV = _float2(1.f, 0.f);

	pVertices[5].vPosition = _float3(fWidth, fTopHeight + fPos, fWidth);
	pVertices[5].vTexUV = _float2(0.f, 0.f);

	pVertices[6].vPosition = _float3(fWidth, fBottomHeight + fPos, fWidth);
	pVertices[6].vTexUV = _float2(0.f, 1.f);

	pVertices[7].vPosition = _float3(-1.f * fWidth, fBottomHeight + fPos, fWidth);
	pVertices[7].vTexUV = _float2(1.f, 1.f);

	m_pVB->Unlock();

	m_iPrimitiveIndicesSize = sizeof(FACEINDICES16);
	m_eIndexFormat = D3DFMT_INDEX16;

	if (FAILED(__super::Create_IndexBuffer()))
		return E_FAIL;

	//FACEINDICES16* pIndices = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndices, 0);

	pIndices[0]._0 = 0;
	pIndices[0]._1 = 1;
	pIndices[0]._2 = 2;

	pIndices[1]._0 = 0;
	pIndices[1]._1 = 2;
	pIndices[1]._2 = 3;

	pIndices[2]._0 = 4;
	pIndices[2]._1 = 5;
	pIndices[2]._2 = 1;

	pIndices[3]._0 = 4;
	pIndices[3]._1 = 1;
	pIndices[3]._2 = 0;

	pIndices[4]._0 = 5;
	pIndices[4]._1 = 4;
	pIndices[4]._2 = 6;

	pIndices[5]._0 = 6;
	pIndices[5]._1 = 4;
	pIndices[5]._2 = 7;

	pIndices[6]._0 = 3;
	pIndices[6]._1 = 2;
	pIndices[6]._2 = 7;

	pIndices[7]._0 = 7;
	pIndices[7]._1 = 2;
	pIndices[7]._2 = 6;

	pIndices[8]._0 = 3;
	pIndices[8]._1 = 7;
	pIndices[8]._2 = 0;

	pIndices[9]._0 = 0;
	pIndices[9]._1 = 7;
	pIndices[9]._2 = 4;

	pIndices[10]._0 = 1;
	pIndices[10]._1 = 5;
	pIndices[10]._2 = 2;

	pIndices[11]._0 = 2;
	pIndices[11]._1 = 5;
	pIndices[11]._2 = 6;

	m_pIB->Unlock();

	return S_OK;
}

CVIBuffer_Cube* CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphicDevice)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(pGraphicDevice);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
		Safe_Release(pInstance);

	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone(void * pArg)
{
	CVIBuffer_Cube* pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
		Safe_Release(pInstance);

	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	__super::Free();
}
