#pragma once
#include "Base.h"

///�÷��̾�, ���� � has a ����� ����� �θ� Ŭ����
//������Ÿ�� ������ ������ ����Ѵ�.
//��ӹ޴� �ڽĵ��� ������ �� ���̹Ƿ� �׷��� ����̽��� ��� ������ ���´�.

class CComponent abstract : public CBase
{
protected:
	CComponent(LPDIRECT3DDEVICE9 pDevice);
	CComponent(const CComponent & Rhs);
	virtual ~CComponent() = default;
protected :
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
protected :
	LPDIRECT3DDEVICE9 m_pGraphicDev = nullptr;
public :
	virtual CComponent* Clone(void* pArg) = 0;
	virtual void Free();
};

