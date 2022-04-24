
// Tool126View.cpp : CTool126View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool126.h"
#endif

#include "Tool126Doc.h"
#include "Tool126View.h"

#include "GameInstance.h"
#include "Graphic_Device.h"
#include "GameObject.h"
#include "Test.h"
#include "Loader.h"
#include "Level_Loading.h"
#include "Level_GamePlay.h"
#include "MainFrm.h"
#include "ChildForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	  g_hWnd;			// 전역변수
HINSTANCE g_hInst;
CRITICAL_SECTION g_CriticalSection;
const int g_WINCX = 1280;
const int g_WINCY = 720;
CBone * g_pBone;
extern vector<CTransform*> g_vecBoneTransfrom;
// CTool126View
IMPLEMENT_DYNCREATE(CTool126View, CView)

BEGIN_MESSAGE_MAP(CTool126View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTool126View 생성/소멸

CTool126View::CTool126View()
{
}

CTool126View::~CTool126View()
{
}

_uint APIENTRY ToolEntryFunction(void* pArg)
{
	if (!pArg)
		return 0;

	CTool126View::THREAD_DESC* ThreadDesc = (CTool126View::THREAD_DESC*)pArg;

	while (1)
	{
		if (!ThreadDesc->bPlaying)
		{
			Sleep(10);
			continue;
		}
		EnterCriticalSection(&g_CriticalSection);
		ThreadDesc->fTimeAcc += ThreadDesc->pGameInstance->Compute_TimeDelta(TEXT("Timer_Default"));
		if (ThreadDesc->fTimeAcc > 1.f / 60.0f)
		{
			if (1000.f < ThreadDesc->fTimeAcc)
				continue;

			ThreadDesc->fTime60 = ThreadDesc->pGameInstance->Compute_TimeDelta(TEXT("Timer_60"));
			ThreadDesc->pGameInstance->Tick_Engine(ThreadDesc->fTime60);
			ThreadDesc->pView->Invalidate(FALSE);
		}
		LeaveCriticalSection(&g_CriticalSection);
		if (!ThreadDesc->bRun)
			return 0;
		Sleep(10);
	}

	return 0;
}

BOOL CTool126View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CTool126View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	ZeroMemory(&m_ThreadDesc, sizeof(THREAD_DESC));
	ZeroMemory(&m_MemoPoint, sizeof(CPoint));
	m_MemoPoint.x = g_WINCX * 0.5f;
	m_MemoPoint.y = g_WINCY * 0.5f;
	g_hWnd = m_hWnd;
	g_hInst = AfxGetInstanceHandle();
	m_ThreadDesc.bPlaying = true;
	if (!g_hWnd || !g_hInst)
	{
		AfxMessageBox(L"Handle or Instance in null");
	}
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	RECT		rcWindow{};
	m_pMainFrame->GetWindowRect(&rcWindow);
	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT	rcMainView{};
	GetClientRect(&rcMainView);
	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	m_pMainFrame->SetWindowPos(nullptr, 200, 200, int(g_WINCX), int(g_WINCY), SWP_NOZORDER);

	m_pGameInstance = CGameInstance::Get_Instance();

	m_pGameInstance->Add_Timer(TEXT("Timer_Default"));
	m_pGameInstance->Add_Timer(TEXT("Timer_60"));


	m_ThreadDesc.pGameInstance = m_pGameInstance;
	m_ThreadDesc.pView = this;
	Engine::Safe_AddRef(m_ThreadDesc.pGameInstance);

	Engine::Safe_AddRef(m_pGameInstance);

	Engine::GRAPHIC_DEVICE_DESC tDesc;
	ZeroMemory(&tDesc, sizeof(Engine::GRAPHIC_DEVICE_DESC));
	tDesc.eWindMode = Engine::MODE_WINMODE;
	tDesc.hWnd = g_hWnd;
	tDesc.iWinCX = g_WINCX;
	tDesc.iWinCY = g_WINCY;

	if (FAILED(m_pGameInstance->Initialize_Engine(g_hInst, LEVEL_END, tDesc, &m_pGraphic_Device)))
	{
		AfxMessageBox(L"m_pGraphic_Device Create Failed");
		return;
	}
	if (FAILED(m_pGameInstance->Add_ComponentObject(LEVEL_STATIC, KEY_COMPONENT_RENDERER, m_pRenderer = CRenderer::Create(m_pGraphic_Device))))
	{
		AfxMessageBox(L"Renderer Create Failed");
		return;
	}

	if (FAILED(m_pGameInstance->Add_ComponentObject(LEVEL_STATIC, KEY_COMPONENT_TRANSFORM, CTransform::Create(m_pGraphic_Device))))
	{
		AfxMessageBox(L"CTransform Create Failed");
		return;
	}

	if (FAILED(m_pGameInstance->Add_ComponentObject(LEVEL_STATIC, KEY_COMPONENT_VI_CUBE, CVIBuffer_Cube::Create(m_pGraphic_Device))))
	{
		AfxMessageBox(L"CVIBuffer_Cube Create Failed");
		return;
	}

	if (FAILED(m_pGameInstance->Add_ComponentObject(LEVEL_STATIC, KEY_COMPONENT_BONE, (CBone*)CBone::Create(m_pGraphic_Device))))
	{
		AfxMessageBox(L"CVIBuffer_Cube Create Failed");
		return;
	}

	CGameObject * pGameObject = nullptr;

	if (FAILED(SetUp_RenderState()))
	{
		return;
	}

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(LEVEL_GAMEPLAY, m_pGraphic_Device))))
	{
		AfxMessageBox(L"Failed to Create Level");
		return;
	}

	//Thread Initialize
	InitializeCriticalSection(&g_CriticalSection);
	m_ThreadDesc.bRun = TRUE;
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ToolEntryFunction, &m_ThreadDesc, 0, nullptr);
	if (0 == m_hThread)
		return;

}


void CTool126View::OnDraw(CDC* pDC)
{
	CTool126Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	static float fAcc = 0.f;

	if (!m_pRootTransForm)
		m_pRootTransForm = (CTransform*)g_pBone->Find_Bone(BONE_LAYER_PLAYER, Engine::KEY_BONE_ROOT);

	m_pGameInstance->Render_Engine();
	m_pGameInstance->RenderBegin();
	m_pRenderer->Draw_Renderer();
	m_pGameInstance->RenderEnd(nullptr);
}


// CTool126View 인쇄

BOOL CTool126View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CTool126View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CTool126View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}


// CTool126View 진단

#ifdef _DEBUG
void CTool126View::AssertValid() const
{
	CView::AssertValid();
}

void CTool126View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool126Doc* CTool126View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool126Doc)));
	return (CTool126Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool126View 메시지 처리기

void CTool126View::OnDestroy()
{
	EnterCriticalSection(&g_CriticalSection);
	m_ThreadDesc.bRun = false;
	LeaveCriticalSection(&g_CriticalSection);

	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&g_CriticalSection);

	DeleteObject(m_hThread);

	CloseHandle(m_hThread);

	CView::OnDestroy();

	Engine::Safe_Release(m_ThreadDesc.pGameInstance);
	Engine::Safe_Release(m_pRenderer);
	Engine::Safe_Release(m_pGameInstance);
	CGameInstance::Destroy_Instance();
}
void CTool126View::OnMouseMove(UINT nFlags, CPoint point)
{
	static float fAcc = 0.f;

	if (GetAsyncKeyState(VK_LBUTTON) < 0)
	{
		g_vecBoneTransfrom[CTest::ROOT]->Turn(_float3(0.f, 1.f, 0.f), (point.x - m_MemoPoint.x) * 0.03f);
		g_vecBoneTransfrom[CTest::ROOT]->Turn(g_vecBoneTransfrom[CTest::ROOT]->Get_State(STATE_RIGHT), (point.y - m_MemoPoint.y) * 0.03f);

		m_MemoPoint.x += point.x - m_MemoPoint.x;
		m_MemoPoint.y += point.y - m_MemoPoint.y;
	}
}

void CTool126View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	m_MemoPoint = point;
}