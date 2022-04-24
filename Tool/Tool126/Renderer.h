#pragma once
#include "Component.h"
#include "GameObject.h"


class CRenderer final : public CComponent
{
private:
	CRenderer(LPDIRECT3DDEVICE9 _pDev);
	virtual ~CRenderer() = default;
public :
	virtual HRESULT NativeConstruct_Prototype() override;
	HRESULT Draw_Renderer();
	HRESULT Add_RenderList(RENDERGROUP _eGroup, CGameObject* _pObject);
protected:
private:
	list<CGameObject*>*	m_RenderList = NULL;
	typedef list<CGameObject*> RENDERLIST;
	FORCEINLINE HRESULT Render_Priority();
	FORCEINLINE HRESULT Render_Nonalphablend();
	FORCEINLINE HRESULT Render_Alphablend();
	FORCEINLINE HRESULT Render_Ui();
public :
	static CRenderer* CRenderer::Create(LPDIRECT3DDEVICE9 _pDev)
	{
		CRenderer * pInstance = new CRenderer(_pDev);

		if (FAILED(pInstance->NativeConstruct_Prototype()))
			return NULL;

		return pInstance;
	}
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};


