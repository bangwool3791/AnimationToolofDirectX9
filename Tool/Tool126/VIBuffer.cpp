#include "stdafx.h"
#include "VIBuffer.h"

HRESULT CVIBuffer::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype()))
	{
		MSGBOX(TEXT("CVI Initiailize Failed in Component ProtoType Class Graphic Dev is NULL"));
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVIBuffer::NativeConstruct(void* pArg)
{
	if (FAILED(__super::NativeConstruct(pArg)))
	{
		MSGBOX(TEXT("CVI Initiailize Failed in Component Clone Class Graphic Dev is NULL"));
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CVIBuffer::Render()
{
	if (nullptr == m_pGraphicDev ||
		nullptr == m_pVB)
		return E_FAIL;

	if (FAILED(m_pGraphicDev->SetStreamSource(0, m_pVB, 0, m_iStride)))
		return E_FAIL;

	if (FAILED(m_pGraphicDev->SetFVF(m_dwFVF)))
		return E_FAIL;

	if (FAILED(m_pGraphicDev->SetIndices(m_pIB)))
		return E_FAIL;

	return m_pGraphicDev->DrawIndexedPrimitive(m_ePrimitiveType, 0, 0, m_iNumVertices, 0, m_iNumPrimitive);
}

void CVIBuffer::Free()
{
	__super::Free();
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
}