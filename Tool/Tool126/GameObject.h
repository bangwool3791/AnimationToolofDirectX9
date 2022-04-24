#pragma once
#include "Base.h"
//������ ���� �� ���̳� ���纻�� ������ ���̳�
//������ �ε����� �����κ��� �޾ƿ��� �����͸� ���� ��������� ��ü
//���纻�� �ε��� ���� �� �ΰ��ӿ��� ���� �Ǿ��� ��ü

class CGameObject abstract : public CBase
{
public:
	explicit CGameObject(LPDIRECT3DDEVICE9 _pDevice);
	explicit CGameObject(const CGameObject& _rhs);//���۷����� �����Ϳ� �����ϰ� 4byte �Ҵ��� �Ͼ��.
	virtual ~CGameObject() = default;
public:
	virtual void Tick(_float _fDeltaTime);
	virtual void Late_Tick(_float _fDeltaTime);
	virtual HRESULT Render();
protected:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
protected:
	_float3			  m_vPos;
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
	class CRenderer * m_pRendererCom = NULL;
	class CTransform* m_pTransformCom = nullptr;
	class CVIBuffer_Rect* m_pVIBufferCom = NULL;
public :
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};


