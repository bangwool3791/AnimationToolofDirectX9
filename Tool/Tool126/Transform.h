#pragma once

#include "Component.h"

/* 객체의 월드 상태를 정의한다.(행렬) */




class CTransform final : public CComponent
{
private:
	CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	//엔진으로 코드 옮길 것

	_float3 Get_State(STATE eState, _float4x4 _matrix)
	{
		return *(_float3 *)&_matrix.m[eState][0];
	}

	_float3 Get_State(STATE eState) {
		return *(_float3 *)&m_TransformDesc.WorldMatrix.m[eState][0];
	}

	void Set_State(STATE eState, _float4x4& _matrix, const D3DXVECTOR3& vState)
	{
		memcpy(&_matrix.m[eState][0], &vState, sizeof(D3DXVECTOR3));
	}


	_float4x4 Get_WorldMatrixInverse() {
		_float4x4		WorldMatrix;
		return *D3DXMatrixInverse(&WorldMatrix, nullptr, &m_TransformDesc.WorldMatrix);
	}

	void Set_State(STATE eState, const D3DXVECTOR3& vState) {
		memcpy(&m_TransformDesc.WorldMatrix.m[eState][0], &vState, sizeof(D3DXVECTOR3));
	}

	TRANSFORMDESC* Get_TansDesc()
	{
		return &m_TransformDesc;
	}

	_float3 Get_LocalState(STATE eState) {
		return *(_float3 *)&m_TransformDesc.LocalMatrix.m[eState][0];
	}

	_float4x4 Get_BindMatrix() {
		return m_BindLocalMatrix * m_BindWorldMatrix;
	}

	void Set_LocalState(STATE eState, const D3DXVECTOR3& vState);

	void Set_LocalPos(float _fPos, const AXIS eAxis) {
		m_TransformDesc.LocalMatrix.m[STATE_POSITION][eAxis] = _fPos;
	}

	TRANSFORMDESC Get_TransformDesc(const TRANSFORMDESC& TransformDesc) {
		return m_TransformDesc;
	}

	void Set_TransformDesc(const TRANSFORMDESC& TransformDesc) {
		m_TransformDesc = TransformDesc;
	}

	void Bind_Parent(CTransform& Rhs, TCHAR* pTag)
	{
		m_pTag = pTag;

		if (!lstrcmp(pTag, KEY_BONE_PELVIS))
		{
			m_pParentLocalMatrix = &(Rhs.m_TransformDesc.LocalMatrix);
			m_pParentWorldMatrix = &(Rhs.m_TransformDesc.WorldMatrix);
		}
		else
		{
			m_pParentLocalMatrix = &(Rhs.m_BindLocalMatrix);
			m_pParentWorldMatrix = &(Rhs.m_BindWorldMatrix);
		}
	}

	_float3 Get_Scale() {
		return _float3(D3DXVec3Length(&Get_State(STATE_RIGHT)),
			D3DXVec3Length(&Get_State(STATE_UP)),
			D3DXVec3Length(&Get_State(STATE_LOOK)));
	}
	
	_float3 Get_LocalScale() {
		return _float3(D3DXVec3Length(&Get_LocalState(STATE_RIGHT)),
			D3DXVec3Length(&Get_LocalState(STATE_UP)),
			D3DXVec3Length(&Get_LocalState(STATE_LOOK)));
	}
	//삭제
	void Set_LocalXYZMatrix(_float3 vAxis, _float fAngle)
	{
		m_TransformDesc.vAxis = vAxis;
		m_TransformDesc.fInitAngle = fAngle;
		if (vAxis.x)
		{
			m_TransformDesc.LocalMatrix.m[1][1] = cosf(fAngle);
			m_TransformDesc.LocalMatrix.m[1][2] = sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[2][1] = -sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[2][2] = cosf(fAngle);
		}

		if (vAxis.y)
		{
			m_TransformDesc.LocalMatrix.m[0][0] = cosf(fAngle);
			m_TransformDesc.LocalMatrix.m[0][2] = -sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[2][0] = sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[2][2] = cosf(fAngle);
		}

		if (vAxis.z)
		{
			m_TransformDesc.LocalMatrix.m[0][0] = cosf(fAngle);
			m_TransformDesc.LocalMatrix.m[0][1] = sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[1][0] = -sinf(fAngle);
			m_TransformDesc.LocalMatrix.m[1][1] = cosf(fAngle);
		}
		Bind_OnGraphicDevice();
	}

public:
	virtual HRESULT NativeConstruct_Prototype() override;
	virtual HRESULT NativeConstruct(void* pArg) override;

public:
	HRESULT Go_Straight(_float fTimeDelta);
	HRESULT Go_Left(_float fTimeDelta);
	HRESULT Go_Right(_float fTimeDelta);
	HRESULT Go_Backward(_float fTimeDelta);
	HRESULT Rotation(const _float3& vAxis, _float fRadian);
	HRESULT Turn(const _float3& vAxis, _float fTimeDelta);
	_float Turn_Local(_float3& vAxis, _float fTimeDelta);
	HRESULT LookAt(const _float3& vTargetPos);
	HRESULT Chase(const _float3& vTargetPos, _float fTimeDelta, _float fLimit = 1.f);
	void  Turn_Bone(_float3 & vAxis, _float fTimeDelta, _float fAngle);
	//hhlee
	_float3 Set_MatrixPos(STATE eState, _float4x4 matrix, _float3 vPos)
	{
		//행렬의 포지션 값을 가져옴
		_float3 position = Get_State(eState, matrix);

		Set_State(eState, matrix, vPos);

		return position;
	}
	void Set_MaxAngle(_float _fMaxAngle)
	{
		m_TransformDesc.fMaxAngle = _fMaxAngle;
	}
	float Get_MaxAngle()
	{
		return m_TransformDesc.fMaxAngle;
	}
#ifdef _DEBUG
	const TCHAR* Get_Tag()
	{
		return m_pTag;
	}
#endif
	//로컬 앵글이란 뼈가 회전을 할 때 회전하는 시작 각도를 말함.
	void	Set_Animation(_float _fMaxAngle, _float _fDir)
	{
		m_TransformDesc.fMaxAngle = _fMaxAngle;
		m_fAngle = m_TransformDesc.fLocalAngle;
		m_TransformDesc.fDir = _fDir;
	}

	void	Set_Dir(_float _fDir)
	{
		m_TransformDesc.fDir = _fDir;
	}

	
	void	Set_Speed(_float _fSpd)
	{
		m_TransformDesc.fRotationPerSec = _fSpd;
	}

	void	Set_LocalAngle(_float _fMinAngle)
	{
		m_TransformDesc.fLocalAngle = _fMinAngle;
	}
	float	Get_LocalAngle()
	{
		return m_TransformDesc.fLocalAngle;
	}

	void	Init_ActiveAngle()
	{
		m_fAngle = 0;
	}

public:
	HRESULT Bind_OnGraphicDevice();

private:
	_bool				m_bCamearaTrans = false;
	_float3				m_vTargetCam;
	_float				m_fAngle = 0.f;
	_float				m_fDir = 1.f;
private:
	_float4x4			m_BindWorldMatrix;
	_float4x4			m_BindLocalMatrix;
private:
	_float4x4			*m_pParentWorldMatrix = NULL;
	_float4x4			*m_pParentLocalMatrix = NULL;
	TRANSFORMDESC		m_TransformDesc;
	TCHAR*				m_pTag = NULL;
public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};
END