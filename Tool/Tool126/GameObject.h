#pragma once
#include "Base.h"
//원형을 생성 할 것이냐 복사본을 생성할 것이냐
//원형은 로딩에서 서버로부터 받아오는 데이터를 통해 만들어지는 객체
//복사본은 로딩이 끝난 후 인게임에서 생성 되어질 객체

class CGameObject abstract : public CBase
{
public:
	explicit CGameObject(LPDIRECT3DDEVICE9 _pDevice);
	explicit CGameObject(const CGameObject& _rhs);//레퍼런스도 포인터와 동일하게 4byte 할당이 일어난다.
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


