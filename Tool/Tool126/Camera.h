#pragma once

#include "GameObject.h"
#include "Transform.h"

class CCamera abstract : public CGameObject
{
public:
	typedef struct tagCameraDesc
	{
		_float3		vEye;
		_float3		vAt;
		_float3		vAxisY;

		_float		fFovy, fAspect, fNear, fFar;
		TRANSFORMDESC	TransformDesc;
	}CAMERADESC;

protected:
	FORCEINLINE explicit CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
		: CGameObject(pGraphic_Device)
	{
	}

	FORCEINLINE explicit CCamera::CCamera(const CCamera & rhs)
		: CGameObject(rhs)
	{
	}

	virtual ~CCamera() = default;

public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void Late_Tick(_float fTimeDelta);
	virtual HRESULT Render();

protected:
	class CTransform*			m_pTransform = nullptr;
	CAMERADESC					m_CameraDesc;


protected:
	HRESULT Bind_TransformMatrices();


public:
	virtual CGameObject* Clone(void* pArg) = 0;
	virtual void Free() override;
};

