#pragma once

#include "GameInstance.h"
#include "Test.h"

class CTool126Doc;
class CTool126View : public CView
{
protected: 
	CTool126View();
	DECLARE_DYNCREATE(CTool126View)
public :
	typedef struct ThreadDesc
	{
		CTool126View * pView = NULL;
		CGameInstance * pGameInstance = NULL;
		float      fTimeAcc = 0.f;
		float      fTime60 = 0.f;
		bool		bRun = false;
		bool		bPlaying = true;
	}THREAD_DESC;
	THREAD_DESC& Get_ThreadDesc()
	{
		return m_ThreadDesc;
	}
private :
	THREAD_DESC m_ThreadDesc;
public:
	CTool126Doc* GetDocument() const;

public:

public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

private :
	class CMainFrame * m_pMainFrame = NULL;
	class CChildForm* m_pChildForm = NULL;
public:
	virtual ~CTool126View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	DECLARE_MESSAGE_MAP()
private :
	FORCEINLINE HRESULT CTool126View::SetUp_RenderState()
	{
		m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_pGraphic_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		return S_OK;
	}
private :
	vector<CGameObject *> m_VecGameObject;
	typedef vector<CGameObject *> MAP_GAME_OBJ;
	CGameInstance* m_pGameInstance = NULL;
	LPDIRECT3DDEVICE9 m_pGraphic_Device = NULL;
	CRenderer* m_pRenderer = NULL;
	CTest* m_pTest = NULL;
	CBone* m_pBone = NULL;
	CTransform* m_pRootTransForm = NULL;
	HANDLE				m_hThread;
	CPoint				m_MemoPoint;
public :

public:
	virtual void OnInitialUpdate();
	void CTool126View::OnMouseMove(UINT nFlags, CPoint point);
	void CTool126View::OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // Tool126View.cpp의 디버그 버전
inline CTool126Doc* CTool126View::GetDocument() const
   { return reinterpret_cast<CTool126Doc*>(m_pDocument); }
#endif

