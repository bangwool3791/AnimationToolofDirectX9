#pragma once
#include "Base.h"

///플레이어, 몬스터 등에 has a 관계로 상속할 부모 클래스
//프로토타입 디자인 패턴을 사용한다.
//상속받는 자식들은 랜더를 할 것이므로 그래픽 디바이스를 멤버 변수로 갖는다.

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

