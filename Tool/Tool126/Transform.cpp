#include "stdafx.h"
#include "Transform.h"
#include <math.h>

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_pParentLocalMatrix(rhs.m_pParentLocalMatrix)
	, m_pParentWorldMatrix(rhs.m_pParentWorldMatrix)
	, m_BindLocalMatrix(rhs.m_BindLocalMatrix)
	, m_BindWorldMatrix(rhs.m_BindWorldMatrix)
{
	m_TransformDesc.LocalMatrix = rhs.m_TransformDesc.LocalMatrix;
	m_TransformDesc.WorldMatrix = rhs.m_TransformDesc.WorldMatrix;
}

HRESULT CTransform::NativeConstruct_Prototype()
{
	D3DXMatrixIdentity(&m_TransformDesc.WorldMatrix);
	D3DXMatrixIdentity(&m_TransformDesc.LocalMatrix);
	D3DXMatrixIdentity(&m_BindLocalMatrix);
	D3DXMatrixIdentity(&m_BindWorldMatrix);
	m_pParentLocalMatrix = NULL;
	m_pParentWorldMatrix = NULL;

	return S_OK;
}

HRESULT CTransform::NativeConstruct(void * pArg)
{
	if (nullptr != pArg)
	{
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));
		//로컬 월드 매트릭스 멤버 변수 삭제
		m_fDir = m_TransformDesc.fDir;

		if (!lstrcmp(Engine::KEY_BONE_ROOT, m_TransformDesc.szKey))
		{
			m_pParentLocalMatrix = new _float4x4;
			m_pParentWorldMatrix = new _float4x4;
			D3DXMatrixIdentity(m_pParentLocalMatrix);
			D3DXMatrixIdentity(m_pParentWorldMatrix);
		}
	}

	return S_OK;
}

HRESULT CTransform::Go_Straight(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE_POSITION);
	_float3		vLook = Get_State(STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE_POSITION);
	_float3		vRight = Get_State(STATE_RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE_POSITION);
	_float3		vRight = Get_State(STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);

	return S_OK;
}
#include <iostream>
using namespace std;
HRESULT CTransform::Go_3DPerspective(_float fTimeDelta, _float3 vTarget)
{
	_float3		vPosition = Get_State(STATE_POSITION);

	cout << "X 좌표 값 이동 : " << fabsf(vTarget.x - vPosition.x) << endl;
	cout << "Y 좌표 값 이동 : " << fabsf(vTarget.y - vPosition.y) << endl;
	cout << "Z 좌표 값 이동 : " << fabsf(vTarget.z - vPosition.z) << endl;
	cout << "X 타겟 " << vTarget.x << endl;
	cout << "Y 타겟 " << vTarget.y << endl;
	cout << "Z 타겟 " << vTarget.z << endl;
	cout << "X 이동 " << vPosition.x << endl;
	cout << "Y 이동 " << vPosition.y << endl;
	cout << "Z 이동 " << vPosition.z << endl;

	if (fabsf(vTarget.y - vPosition.y) < 1.f)
		return S_OK;

	vPosition += *D3DXVec3Normalize(&vTarget, &vTarget) * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);
	//if ((fabsf(vPosition.x) - fabsf(vTarget.x) < 1) && (fabsf(vPosition.y) - fabsf(vTarget.y) < 1) && (fabsf(vPosition.z) - fabsf(vTarget.z) < 1))

	return E_FAIL;

}
HRESULT CTransform::Go_Backward(_float fTimeDelta)
{
	_float3		vPosition = Get_State(STATE_POSITION);
	_float3		vLook = Get_State(STATE_LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(STATE_POSITION, vPosition);

	return S_OK;
}

HRESULT CTransform::Rotation(const _float3 & vAxis, _float fRadian)
{
	_float3		vScaleDesc = Get_Scale();

	_float3		vRight = _float3(1.f, 0.f, 0.f) * vScaleDesc.x;
	_float3		vUp = _float3(0.f, 1.f, 0.f) * vScaleDesc.y;
	_float3		vLook = _float3(0.f, 0.f, 1.f) * vScaleDesc.z;

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, fRadian);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(STATE_RIGHT, vRight);
	Set_State(STATE_UP, vUp);
	Set_State(STATE_LOOK, vLook);

	return S_OK;
}

HRESULT CTransform::Turn(const _float3 & vAxis, _float fTimeDelta)
{
	_float3		vRight = Get_State(STATE_RIGHT);
	_float3		vUp = Get_State(STATE_UP);
	_float3		vLook = Get_State(STATE_LOOK);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_TransformDesc.fRotationPerSec * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(STATE_RIGHT, vRight);
	Set_State(STATE_UP, vUp);
	Set_State(STATE_LOOK, vLook);

	//m_eTransState = TRANS_STATE_CHILD;

	return S_OK;
}

_float CTransform::Turn_Local(_float3 & vAxis, _float fTimeDelta)
{
	if (fTimeDelta > 1.f)
		return 0.f;

	if (3.141592 * 2 < fabsf(m_fAngle))
		m_fAngle = 0.f;

	//if(m_pTag)
	//	if(!CString(m_pTag).Compare(KEY_BONE_LEFTLEG))
	//		wcout << "왼쪽 다리 : " << m_fAngle << endl;
	//	else if (!CString(m_pTag).Compare(KEY_BONE_RIGHTLEG))
	//		wcout << "오른쪽 다리 : " << m_fAngle << endl;
	//	else if (!CString(m_pTag).Compare(KEY_BONE_LEFTARM))
	//		wcout << "왼쪽 팔 : " << m_fAngle << endl;
	//	else if (!CString(m_pTag).Compare(KEY_BONE_RIGHTARM))
	//		wcout << "오른쪽 팔 : " << m_fAngle << endl;

	if (0 < m_TransformDesc.fMaxAngle - m_TransformDesc.fLocalAngle)
	{
		if (m_TransformDesc.fLocalAngle > m_fAngle)
		{
			m_TransformDesc.fDir = 1.f;
		}

		if (m_TransformDesc.fMaxAngle < m_fAngle)
		{
			m_TransformDesc.fDir = -1.f;
		}
	}

	if (0 > m_TransformDesc.fMaxAngle - m_TransformDesc.fLocalAngle)
	{
		if (m_TransformDesc.fLocalAngle < m_fAngle)
		{
			m_TransformDesc.fDir = -1.f;
		}

		if (m_TransformDesc.fMaxAngle > m_fAngle)
		{
			m_TransformDesc.fDir = 1.f;
		}
	}

	if (0 == m_TransformDesc.fMaxAngle - m_TransformDesc.fLocalAngle)
	{
		m_fAngle = 0.f;
	}

	m_fAngle += fTimeDelta * m_TransformDesc.fDir * 0.7f;

	_float3		vScaleDesc = Get_Scale();

	_float3		vRight = _float3(1.f, 0.f, 0.f) * vScaleDesc.x;
	_float3		vUp = _float3(0.f, 1.f, 0.f) * vScaleDesc.y;
	_float3		vLook = _float3(0.f, 0.f, 1.f) * vScaleDesc.z;

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_fAngle);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_LocalState(STATE_RIGHT, vRight);
	Set_LocalState(STATE_UP, vUp);
	Set_LocalState(STATE_LOOK, vLook);
	return m_fAngle;
}

HRESULT CTransform::LookAt(const _float3 & vTargetPos)
{
	_float3		vPosition = Get_State(STATE_POSITION);
	_float3		vLook = vTargetPos - vPosition;
	_float3		vRight;
	_float3		vUp;

	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);

	_float3		vScaleDesc = Get_Scale();

	Set_State(STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScaleDesc.x);
	Set_State(STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScaleDesc.y);
	Set_State(STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScaleDesc.z);

	return S_OK;
}

HRESULT CTransform::Chase(const _float3 & vTargetPos, _float fTimeDelta, _float fLimit)
{
	LookAt(vTargetPos);

	_float fDistance = D3DXVec3Length(&(vTargetPos - Get_State(STATE_POSITION)));

	if (fDistance > fLimit)
		Go_Straight(fTimeDelta);

	return S_OK;
}

HRESULT CTransform::Bind_OnGraphicDevice()
{
	if (nullptr == m_pGraphicDev)
		return E_FAIL;

	_float4x4 World;
	//부모행렬의 경우 Tag이름을 설정하지 않는다.
	if (0 < lstrlen(m_TransformDesc.szKey))
	{
		if (!lstrcmp(m_TransformDesc.szKey, KEY_BONE_ROOT))
			World = m_TransformDesc.LocalMatrix * m_TransformDesc.WorldMatrix;
		else
		{
			D3DXMatrixIdentity(&m_BindLocalMatrix);
			D3DXMatrixIdentity(&m_BindWorldMatrix);
			m_BindLocalMatrix = m_TransformDesc.LocalMatrix * m_pParentLocalMatrix[0];
			m_BindWorldMatrix = m_TransformDesc.WorldMatrix * m_pParentWorldMatrix[0];
			World = m_TransformDesc.LocalMatrix * m_pParentLocalMatrix[0] * m_TransformDesc.WorldMatrix *  m_pParentWorldMatrix[0];
		}
	}
	else
		World = m_TransformDesc.LocalMatrix * m_TransformDesc.WorldMatrix;

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &World);

	return S_OK;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTransform*	pInstance = new CTransform(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct_Prototype()))
	{
		MSGBOX(TEXT("Failed to Created : CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}


CComponent * CTransform::Clone(void * pArg)
{
	CTransform*	pInstance = new CTransform(*this);

	if (FAILED(pInstance->NativeConstruct(pArg)))
	{
		MSGBOX(TEXT("Failed to Cloned : CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();

	if (!lstrcmp(Engine::KEY_BONE_ROOT, m_TransformDesc.szKey))
	{
		Safe_Delete(m_pParentLocalMatrix);
		Safe_Delete(m_pParentWorldMatrix);
	}
}
