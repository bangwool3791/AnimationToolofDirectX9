#pragma once

#include "VIBuffer.h"



class CVIBuffer_Cube final : public CVIBuffer
{
public:
	CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphicDevice);
	CVIBuffer_Cube(const CVIBuffer_Cube& rhs);
	virtual ~CVIBuffer_Cube() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);

public:
	void Set_VerticesWidth(void* pArg)
	{
		float* pRadius = (float*)pArg;

		if (!pRadius)
			MSGBOX(TEXT("Set_Vertex radius pointer is null"));

		m_stShape.fWidth = pRadius[0];

		m_pVB->Lock(0, 0, (void**)&pVertices, 0);

		pVertices[0].vPosition.x = - 1.f * m_stShape.fWidth;
		pVertices[0].vPosition.z = -1.f * m_stShape.fWidth;

		pVertices[1].vPosition.x = 1.f * m_stShape.fWidth;
		pVertices[1].vPosition.z = -1.f * m_stShape.fWidth;


		pVertices[2].vPosition.x = 1.f * m_stShape.fWidth;
		pVertices[2].vPosition.z = -1.f * m_stShape.fWidth;

		pVertices[3].vPosition.x = -1.f * m_stShape.fWidth;
		pVertices[3].vPosition.z = -1.f * m_stShape.fWidth;

		pVertices[4].vPosition.x = -1.f * m_stShape.fWidth;
		pVertices[4].vPosition.z = 1.f * m_stShape.fWidth;

		pVertices[5].vPosition.x = 1.f * m_stShape.fWidth;
		pVertices[5].vPosition.z = 1.f * m_stShape.fWidth;

		pVertices[6].vPosition.x = 1.f * m_stShape.fWidth;
		pVertices[6].vPosition.z = 1.f * m_stShape.fWidth;

		pVertices[7].vPosition.x = -1.f * m_stShape.fWidth;
		pVertices[7].vPosition.z = 1.f * m_stShape.fWidth;

		m_pVB->Unlock();
	}

	void Set_VerticesHeight(void* pArg)
	{

		if (!pArg)
			MSGBOX(TEXT("Set_Vertex radius pointer is null"));

		m_stShape.fTop = ((float*)pArg)[0];
		m_stShape.fBottom = ((float*)pArg)[1];
		m_stShape.fPos = ((float*)pArg)[2];

		m_pVB->Lock(0, 0, (void**)&pVertices, 0);
		//fHeight = fHeight + -1.f;
		pVertices[0].vPosition.y = m_stShape.fTop + m_stShape.fPos;

		pVertices[1].vPosition.y = m_stShape.fTop + m_stShape.fPos;

		pVertices[2].vPosition.y = m_stShape.fBottom + m_stShape.fPos;

		pVertices[3].vPosition.y = m_stShape.fBottom + m_stShape.fPos;

		pVertices[4].vPosition.y = m_stShape.fTop + m_stShape.fPos;

		pVertices[5].vPosition.y = m_stShape.fTop + m_stShape.fPos;

		pVertices[6].vPosition.y = m_stShape.fBottom + m_stShape.fPos;

		pVertices[7].vPosition.y = m_stShape.fBottom + m_stShape.fPos;

		m_pVB->Unlock();
	}
public :
	typedef struct tagShape
	{
		_float fWidth = 0.f;
		_float fTop = 0.f;
		_float fBottom = 0.f;
		_float fPos = 0.f;
	}STSHAPE;
	STSHAPE m_stShape;

	STSHAPE* Get_ShapeInfo()
	{
		return &m_stShape;
	}
protected:
	VTXTEX* pVertices = nullptr;
	FACEINDICES16* pIndices = nullptr;

public:
	static CVIBuffer_Cube* Create(LPDIRECT3DDEVICE9 pGraphicDevice);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};
