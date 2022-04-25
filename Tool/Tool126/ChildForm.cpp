// ChildForm.cpp : implementation file
//

#include "stdafx.h"
#include "Tool126.h"
#include "Tool126Doc.h"
#include "Tool126View.h"
extern CRITICAL_SECTION g_CriticalSection;
#include "ChildForm.h"
#include "MainFrm.h"

// CChildForm

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CChildForm, CFormView)

#include "Test.h"
#include "Parser.h"
extern vector<CTransform*> g_vecBoneTransfrom;
extern vector<CVIBuffer_Cube*> g_vecAniCube;
extern vector<CTest::TEST_STRUCT> g_vecAniInfo;
extern CTest* g_pTest;

CChildForm::CChildForm()
	: CFormView(IDD_DIALOG1)
	, m_bAniAxis(FALSE)
	, m_bRadioDir(FALSE)
{
	ZeroMemory(&m_vBoneLocalAxis, sizeof(D3DXVECTOR3));
}

CChildForm::~CChildForm()
{
	Safe_Release(m_pTest);
}

void CChildForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BONE_TREE, m_treeBone);
	m_treeBone.InsertItem(KEY_BONE_ROOT);
	m_treeBone.InsertItem(KEY_BONE_PELVIS);
	m_treeBone.InsertItem(KEY_BONE_SPINE);
	m_treeBone.InsertItem(KEY_BONE_NECK);
	m_treeBone.InsertItem(KEY_BONE_LEFTLEG);
	m_treeBone.InsertItem(KEY_BONE_RIGHTLEG);
	m_treeBone.InsertItem(KEY_BONE_LEFTARM);
	m_treeBone.InsertItem(KEY_BONE_RIGHTARM);
	m_treeBone.InsertItem(KEY_BONE_LEFTELBOW);
	m_treeBone.InsertItem(KEY_BONE_RIGHTELBOW);
	m_treeBone.InsertItem(KEY_BONE_LEFTANKLE);
	m_treeBone.InsertItem(KEY_BONE_RIGHTANKLE);

	DDX_Control(pDX, EIDT_ROOT_BONE_POS_X, m_tbRootBonePosX);
	DDX_Control(pDX, SPIN_ROOT_BONE_POS_X, m_SpinRootBonePosX);
	DDX_Control(pDX, EIDT_ROOT_BONE_POS_Y, m_tbRootBonePosY);
	DDX_Control(pDX, SPIN_ROOT_BONE_POS_Y, m_SpinRootBonePosY);
	DDX_Control(pDX, EIDT_ROOT_BONE_POS_Z, m_tbRootBonePosZ);
	DDX_Control(pDX, SPIN_ROOT_BONE_POS_Z, m_SpinRootBonePosZ);

	m_tbRootBonePosX.SetWindowTextW(TEXT("0.0"));
	m_SpinRootBonePosX.SetRange(-100, 100);
	m_SpinRootBonePosX.SetPos(0);

	m_tbRootBonePosY.SetWindowTextW(TEXT("0.0"));
	m_SpinRootBonePosY.SetRange(-100, 100);
	m_SpinRootBonePosY.SetPos(0);

	m_tbRootBonePosZ.SetWindowTextW(TEXT("0.0"));
	m_SpinRootBonePosZ.SetRange(-100, 100);
	m_SpinRootBonePosZ.SetPos(0);

	DDX_Control(pDX, CB_ROOT_BONE_AXIS, cb_boneAxis);
	DDX_Control(pDX, EDIT_BONE_ANGLE, m_tbBoneAngle);
	DDX_Control(pDX, SPIN_BONE_ANGLE, m_SpinBoneAngle);
	m_tbBoneAngle.SetWindowTextW(TEXT("0.0"));
	m_SpinBoneAngle.SetRange(-100, 100);
	m_SpinBoneAngle.SetPos(0);

	cb_boneAxis.InsertString(0, TEXT("X"));
	cb_boneAxis.InsertString(1, TEXT("Y"));
	cb_boneAxis.InsertString(2, TEXT("Z"));
	cb_boneAxis.SetCurSel(0);

	m_strBoneAngle = CString();
	DDX_Control(pDX, IDC_ANIMATION_TREE, m_treeAni);

	m_treeAni.InsertItem(KEY_ANI_HEAD);
	m_treeAni.InsertItem(KEY_ANI_BODY);
	m_treeAni.InsertItem(KEY_ANI_LEFTARM);
	m_treeAni.InsertItem(KEY_ANI_RIGHTARM);
	m_treeAni.InsertItem(KEY_ANI_LEFTLEG);
	m_treeAni.InsertItem(KEY_ANI_RIGHTLEG);
	m_treeAni.InsertItem(KEY_ANI_LEFTELBOW);
	m_treeAni.InsertItem(KEY_ANI_RIGHTELBOW);
	m_treeAni.InsertItem(KEY_ANI_LEFTANKLE);
	m_treeAni.InsertItem(KEY_ANI_RIGHTANKLE);

	DDX_Control(pDX, EDIT_ANIMATION_WIDTH, m_tbAniWidth);
	DDX_Control(pDX, SPIN_ANIMATION_WIDTH, m_SpinAniWidth);

	DDX_Control(pDX, EDIT_ANIMATION_TOP, m_tbAniTop);
	DDX_Control(pDX, SPIN_ANIMATION_TOP, m_spinAniTop);

	DDX_Control(pDX, SPIN_ANIMATION_BOTTOM, m_tbAniBottom);
	DDX_Control(pDX, SPIN_ROOT_BONE_BOTTOM, m_spinAniBottom);

	DDX_Control(pDX, SPIN_ANIMATION_POS, m_tbAniPos);
	DDX_Control(pDX, SPIN_ROOT_BONE_POS_Z3, m_SpinAniPos);

	m_tbAniWidth.SetWindowTextW(TEXT("0.0"));
	m_tbAniTop.SetWindowTextW(TEXT("0.0"));
	m_tbAniBottom.SetWindowTextW(TEXT("0.0"));
	m_tbAniPos.SetWindowTextW(TEXT("0.0"));

	m_SpinAniWidth.SetRange(-100, 100);
	m_SpinAniWidth.SetPos(0);
	m_spinAniTop.SetRange(-100, 100);
	m_spinAniTop.SetPos(0);
	m_spinAniBottom.SetRange(-100, 100);
	m_spinAniBottom.SetPos(0);
	m_SpinAniPos.SetRange(-100, 100);
	m_SpinAniPos.SetPos(0);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CTool126View*	pView = dynamic_cast<CTool126View*>(pMainFrame->m_MainSplitter.GetPane(0, 0));

	m_stThreadDesc = &pView->Get_ThreadDesc();
	DDX_Control(pDX, IDC_THREAD_BUTTON, m_BtnThreadRun);
	DDX_Control(pDX, RADIO_ANI_AXIS_1, m_radioAxis);
	DDX_Radio(pDX, RADIO_ANI_AXIS_1, m_bAniAxis);
	DDX_Control(pDX, RADIO_ANI_DIR_1, m_radioDir);
	DDX_Radio(pDX, RADIO_ANI_DIR_1, m_bRadioDir);
	DDX_Control(pDX, EIDT__ANIMATION_MAX_ANGLE, m_tbAniMaxAngle);
	DDX_Control(pDX, SPIN_ANIMATION_MAX_ANGLE, m_spinAniMaxAngle);

	m_spinAniMaxAngle.SetRange(-100, 100);
	m_spinAniMaxAngle.SetPos(0);

	DDX_Control(pDX, CB_ANI_SELECT_ANI, m_cbAniSelect);

	m_cbAniSelect.InsertString(0, TEXT("Idle"));
	m_cbAniSelect.InsertString(1, TEXT("Attack"));
	m_cbAniSelect.InsertString(2, TEXT("Stun"));
	m_cbAniSelect.InsertString(3, TEXT("Die"));
	m_cbAniSelect.SetCurSel(0);

	DDX_Control(pDX, CB_ANI_SELECT_BODY_BONE, m_cbAniBone);

	m_cbAniBone.InsertString(0, TEXT("Root"));
	m_cbAniBone.InsertString(1, TEXT("Pelvis"));
	m_cbAniBone.InsertString(2, TEXT("Spine"));
	m_cbAniBone.InsertString(3, TEXT("Neck"));
	m_cbAniBone.InsertString(4, TEXT("LeftLeg"));
	m_cbAniBone.InsertString(5, TEXT("RightLeg"));
	m_cbAniBone.InsertString(6, TEXT("LeftArm"));
	m_cbAniBone.InsertString(7, TEXT("RightArm"));
	m_cbAniBone.InsertString(8, TEXT("LeftElbow"));
	m_cbAniBone.InsertString(9, TEXT("RightElbow"));
	m_cbAniBone.InsertString(10, TEXT("LeftAnkle"));
	m_cbAniBone.InsertString(11, TEXT("RightAnkle"));
	m_cbAniBone.SetCurSel(0);

	m_tbAniMaxAngle.SetWindowTextW(TEXT("0.0"));

	DDX_Control(pDX, EIDT__ANIMATION_MIN_ANGLE, m_tbAniMinAngle);
	DDX_Control(pDX, SPIN_ANIMATION_MIN_ANGLE, m_spinAniMinAngle);

	m_tbAniMinAngle.SetWindowTextW(TEXT("0.0"));
	m_spinAniMinAngle.SetRange(-100, 100);
	m_spinAniMinAngle.SetPos(0);
	DDX_Control(pDX, CHECK_ROOT, m_checkBoxRoot);
	DDX_Control(pDX, CHECK_PELVIS, m_checkBoxPelvis);
	DDX_Control(pDX, CHECK_SPINE, m_checkBoxSpine);
	DDX_Control(pDX, CHECK_NECK, m_checkBoxNeck);
	DDX_Control(pDX, CHECK_LEFTLEG, m_checkBoxLeftLeg);
	DDX_Control(pDX, CHECK_RIGHTLEG, m_checkBoxRightLeg);
	DDX_Control(pDX, CHECK_LEFTARM, m_checkBoxLeftArm);
	DDX_Control(pDX, CHECK_RIGHTARM, m_checkBoxRightArm);
	DDX_Control(pDX, CHECK_LEFTELBOW, m_checkBoxLeftElbow);
	DDX_Control(pDX, CHECK_RIGHTELBOW, m_checkBoxRightElbow);
	DDX_Control(pDX, CHECK_LEFTANKLE, m_checkBoxLeftAnkle);
	DDX_Control(pDX, CHECK_RIGHTANKLE, m_checkBoxRightAnkle);

	OnCbnSelchangeAniSelectAni();
}

BEGIN_MESSAGE_MAP(CChildForm, CFormView)
	ON_BN_CLICKED(IDC_TEST_BUTTON, &CChildForm::OnBnClickedTestButton)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChildForm::OnCbnSelchangeCombo1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_BONE_TREE, &CChildForm::OnTvnSelchangedBoneTree)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ROOT_BONE_POS_X, &CChildForm::OnDeltaposRootBonePosX)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ROOT_BONE_POS_Y, &CChildForm::OnDeltaposRootBonePosY)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ROOT_BONE_POS_Z, &CChildForm::OnDeltaposRootBonePosZ)
	ON_EN_CHANGE(EIDT_ROOT_BONE_POS_X, &CChildForm::OnEnChangeRootBonePosX)
	ON_EN_CHANGE(EIDT_ROOT_BONE_POS_Y, &CChildForm::OnEnChangeRootBonePosY)
	ON_EN_CHANGE(EIDT_ROOT_BONE_POS_Z, &CChildForm::OnEnChangeRootBonePosZ)
	ON_EN_CHANGE(EDIT_BONE_ANGLE, &CChildForm::OnEnChangeBoneAngle)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_BONE_ANGLE, &CChildForm::OnDeltaposBoneAngle)
	ON_CBN_EDITUPDATE(CB_ROOT_BONE_AXIS, &CChildForm::OnCbnEditupdateRootBoneAxis)
	ON_CBN_DROPDOWN(CB_ROOT_BONE_AXIS, &CChildForm::OnCbnDropdownRootBoneAxis)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ANIMATION_TREE, &CChildForm::OnTvnSelchangedAnimationTree)
	ON_EN_CHANGE(EDIT_ANIMATION_WIDTH, &CChildForm::OnEnChangeAnimationWidth)
	ON_EN_CHANGE(SPIN_ANIMATION_POS, &CChildForm::OnEnChangeAnimationPos)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ANIMATION_WIDTH, &CChildForm::OnDeltaposAnimationWidth)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ROOT_BONE_POS_Z3, &CChildForm::OnDeltaposRootBonePosZ3)
	ON_EN_CHANGE(EDIT_ANIMATION_TOP, &CChildForm::OnEnChangeAnimationTop)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ANIMATION_TOP, &CChildForm::OnDeltaposAnimationTop)
	ON_EN_CHANGE(SPIN_ANIMATION_BOTTOM, &CChildForm::OnEnChangeAnimationBottom)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ROOT_BONE_BOTTOM, &CChildForm::OnDeltaposRootBoneBottom)
	ON_CONTROL_RANGE(BN_CLICKED, RADIO_ANI_AXIS_1, RADIO_ANI_AXIS_3, &CChildForm::OnBnClickedAniAxis)
	ON_CONTROL_RANGE(BN_CLICKED, RADIO_ANI_DIR_1, RADIO_ANI_DIR_2, &CChildForm::OnBnClickedAniDir)
	ON_BN_CLICKED(CHECK_ROOT, &CChildForm::OnBnClickedRoot)
	ON_BN_CLICKED(CHECK_PELVIS, &CChildForm::OnBnClickedPelvis)
	ON_BN_CLICKED(CHECK_SPINE, &CChildForm::OnBnClickedSpine)
	ON_BN_CLICKED(CHECK_NECK, &CChildForm::OnBnClickedNeck)
	ON_BN_CLICKED(CHECK_LEFTLEG, &CChildForm::OnBnClickedLeftleg)
	ON_BN_CLICKED(CHECK_RIGHTLEG, &CChildForm::OnBnClickedRightleg)
	ON_BN_CLICKED(CHECK_LEFTARM, &CChildForm::OnBnClickedLeftarm)
	ON_BN_CLICKED(CHECK_RIGHTARM, &CChildForm::OnBnClickedRightarm)
	ON_BN_CLICKED(CHECK_LEFTELBOW, &CChildForm::OnBnClickedLeftelbow)
	ON_BN_CLICKED(CHECK_RIGHTELBOW, &CChildForm::OnBnClickedRightelbow)
	ON_BN_CLICKED(CHECK_LEFTANKLE, &CChildForm::OnBnClickedLeftankle)
	ON_BN_CLICKED(CHECK_RIGHTANKLE, &CChildForm::OnBnClickedRightankle)
	ON_CBN_SELCHANGE(CB_ANI_SELECT_BODY_BONE, &CChildForm::OnCbnSelchangeAniSelectBone)
	ON_CBN_SELCHANGE(CB_ANI_SELECT_ANI, &CChildForm::OnCbnSelchangeAniSelectAni)
	ON_EN_CHANGE(EIDT__ANIMATION_MAX_ANGLE, &CChildForm::AnimationMaxAngleChagned)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ANIMATION_MAX_ANGLE, &CChildForm::OnDeltaposAnimationMaxAngle)
	ON_EN_CHANGE(EIDT__ANIMATION_MIN_ANGLE, &CChildForm::EnChangeMinAngle)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ANIMATION_MIN_ANGLE, &CChildForm::OnDeltaposAnimationMinAngle)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CChildForm::OnBnClickedSaveButton)
	ON_BN_CLICKED(IDC_LOAD_BUTTON, &CChildForm::OnBnClickedLoadButton)
END_MESSAGE_MAP()


// CChildForm diagnostics

#ifdef _DEBUG
void CChildForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChildForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void CChildForm::OnBnClickedTestButton()
{
	CString str;
	m_BtnThreadRun.GetWindowTextW(str);

	if (!str.Compare(L"Run"))
	{
		m_stThreadDesc->bPlaying = false;
		m_BtnThreadRun.SetWindowTextW(L"Stop");
	}
	else
	{
		m_stThreadDesc->bPlaying = true;
		m_BtnThreadRun.SetWindowTextW(L"Run");
	}
}


int CChildForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CChildForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
}

void CChildForm::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFormView::OnActivate(nState, pWndOther, bMinimized);
	// TODO: Add your message handler code here
}


void CChildForm::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
}


void CChildForm::OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CString strItem = m_treeBone.GetItemText(pNMTreeView->itemNew.hItem);

	if (!strItem.Compare(KEY_BONE_ROOT))
	{
		m_iBoneIndex = 0;
	}
	else if (!strItem.Compare(KEY_BONE_PELVIS))
	{
		m_iBoneIndex = 1;
	}
	else if (!strItem.Compare(KEY_BONE_SPINE))
	{
		m_iBoneIndex = 2;
	}
	else if (!strItem.Compare(KEY_BONE_NECK))
	{
		m_iBoneIndex = 3;
	}
	else if (!strItem.Compare(KEY_BONE_LEFTLEG))
	{
		m_iBoneIndex = 4;
	}
	else if (!strItem.Compare(KEY_BONE_RIGHTLEG))
	{
		m_iBoneIndex = 5;
	}
	else if (!strItem.Compare(KEY_BONE_LEFTARM))
	{
		m_iBoneIndex = 6;
	}
	else if (!strItem.Compare(KEY_BONE_RIGHTARM))
	{
		m_iBoneIndex = 7;
	}
	else if (!strItem.Compare(KEY_BONE_LEFTELBOW))
	{
		m_iBoneIndex = 8;
	}
	else if (!strItem.Compare(KEY_BONE_RIGHTELBOW))
	{
		m_iBoneIndex = 9;
	}
	else if (!strItem.Compare(KEY_BONE_LEFTANKLE))
	{
		m_iBoneIndex = 10;
	}
	else if (!strItem.Compare(KEY_BONE_RIGHTANKLE))
	{
		m_iBoneIndex = 11;
	}

	*pResult = 0;
}

void CChildForm::OnDeltaposRootBonePosX(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strRootBonePosX = sValue;
		m_tbRootBonePosX.SetWindowTextW(sValue);
	}
	*pResult = 0;
}

void CChildForm::OnDeltaposRootBonePosY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strRootBonePosY = sValue;
		m_tbRootBonePosY.SetWindowTextW(sValue);
	}
	*pResult = 0;
}

void CChildForm::OnDeltaposRootBonePosZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strRootBonePosZ = sValue;
		m_tbRootBonePosZ.SetWindowTextW(sValue);
	}
	*pResult = 0;
}

void CChildForm::AllowOnlyRealNum(CEdit *cedit, bool minus, CString& _String)
{
	//// [ 1. initialize value ]
	CString cstrText;
	cedit->GetWindowTextW(cstrText);
	TCHAR chText[100] = {'0', };
	lstrcpy(chText, cstrText);
	int count = lstrlen(chText);

	//// [ 2. remove second point ]
	bool pointChecker = false;
	for (int i = 0; i < count; i++) {
		if (!pointChecker && chText[i] == '.') pointChecker = true;
		else if (pointChecker && chText[i] == '.') chText[i] = NULL;
	}

	//// [ 3. remove middle of minuse ]
	int startIdx = (minus) ? 1 : 0;
	for (int i = startIdx; i < count; i++) {
		if (chText[i] == '-') chText[i] = NULL;
	}

	//// [ 4. remove character ]
	for (int i = 0; i < count; i++) {
		if (!(chText[i] >= 48 && chText[i] <= 57)) {
			if (chText[i] != '.' && chText[i] != '-') chText[i] = NULL;
		}
	}

	//// [ 5. Set text ]
	int n = _String.Compare(chText);
	if (0 != _String.Compare(chText))
	{
		_String = chText;
		cedit->SetWindowTextW(chText);
		//// [ 6. Move cursor to end ]
		cedit->SetSel(0, 0);
		cedit->SetSel(-1, -1);
	}

}

void CChildForm::OnEnChangeRootBonePosX()
{
	AllowOnlyRealNum(&m_tbRootBonePosX, true, m_strRootBonePosX);
	CString str;
	m_tbRootBonePosX.GetWindowTextW(str);

	float fValue = _tstof(str);
	g_vecBoneTransfrom[m_iBoneIndex]->Set_LocalPos(fValue, Engine::AXISX);
}


void CChildForm::OnEnChangeRootBonePosY()
{
	AllowOnlyRealNum(&m_tbRootBonePosY, true, m_strRootBonePosY);
	CString str;
	m_tbRootBonePosY.GetWindowTextW(str);

	float fValue = _tstof(str);
	g_vecBoneTransfrom[m_iBoneIndex]->Set_LocalPos(fValue, Engine::AXISY);
}


void CChildForm::OnEnChangeRootBonePosZ()
{
	AllowOnlyRealNum(&m_tbRootBonePosZ, true, m_strRootBonePosZ);
	CString str;
	m_tbRootBonePosZ.GetWindowTextW(str);

	float fValue = _tstof(str);
	g_vecBoneTransfrom[m_iBoneIndex]->Set_LocalPos(fValue, Engine::AXISZ);
}


void CChildForm::OnEnChangeBoneAngle()
{
	AllowOnlyRealNum(&m_tbBoneAngle, true, m_strBoneAngle);
	CString str;
	m_tbBoneAngle.GetWindowTextW(m_strBoneAngle);

	float fValue = _tstof(m_strBoneAngle);
	m_fBoneLocalAngle = fValue;
	g_vecBoneTransfrom[m_iBoneIndex]->Set_LocalXYZMatrix(m_vBoneLocalAxis, m_fBoneLocalAngle);
}


void CChildForm::OnDeltaposBoneAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strBoneAngle = sValue;
		m_tbBoneAngle.SetWindowTextW(sValue);
	}
	*pResult = 0;
}

void CChildForm::OnCbnEditupdateRootBoneAxis()
{
	if (AXISX == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(1.f, 0.f, 0.f);
	}
	else if (AXISY == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(-1.f, 0.f, 0.f);
	}
	else if (AXISZ == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(0.f, 0.f, 1.f);
	}
}


void CChildForm::OnCbnDropdownRootBoneAxis()
{
	if (AXISX == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(1.f, 0.f, 0.f);
	}
	else if (AXISY == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(0.f, 1.f, 0.f);
	}
	else if (AXISZ == cb_boneAxis.GetCurSel())
	{
		m_vBoneLocalAxis = D3DXVECTOR3(0.f, 0.f, 1.f);
	}
}


void CChildForm::OnTvnSelchangedAnimationTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CString strItem = m_treeAni.GetItemText(pNMTreeView->itemNew.hItem);

	if (!strItem.Compare(KEY_ANI_HEAD))
	{
		m_iAniIndex = 0;
	}
	else if (!strItem.Compare(KEY_ANI_BODY))
	{
		m_iAniIndex = 1;
	}
	else if (!strItem.Compare(KEY_ANI_LEFTARM))
	{
		m_iAniIndex = 2;
	}
	else if (!strItem.Compare(KEY_ANI_RIGHTARM))
	{
		m_iAniIndex = 3;
	}
	else if (!strItem.Compare(KEY_ANI_LEFTLEG))
	{
		m_iAniIndex = 4;
	}
	else if (!strItem.Compare(KEY_ANI_RIGHTLEG))
	{
		m_iAniIndex = 5;
	}
	else if (!strItem.Compare(KEY_ANI_LEFTELBOW))
	{
		m_iAniIndex = 6;
	}
	else if (!strItem.Compare(KEY_ANI_RIGHTELBOW))
	{
		m_iAniIndex = 7;
	}
	else if (!strItem.Compare(KEY_ANI_LEFTANKLE))
	{
		m_iAniIndex = 8;
	}
	else if (!strItem.Compare(KEY_ANI_RIGHTANKLE))
	{
		m_iAniIndex = 9;
	}

	*pResult = 0;
}

void CChildForm::OnEnChangeAnimationWidth()
{
	AllowOnlyRealNum(&m_tbAniWidth, true, m_strAniWidth);
	m_tbAniWidth.GetWindowTextW(m_strAniWidth);

	m_fWitdh = _tstof(m_strAniWidth);

	g_vecAniCube[m_iAniIndex]->Set_VerticesWidth(&m_fWitdh);
}

void CChildForm::OnDeltaposAnimationWidth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fWitdh = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= m_fWitdh) && (100.f >= m_fWitdh))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), m_fWitdh);
		m_strAniWidth = sValue;
		m_tbAniWidth.SetWindowTextW(m_strAniWidth);
		g_vecAniCube[m_iAniIndex]->Set_VerticesWidth(&m_fWitdh);
	}
	*pResult = 0;
}


void CChildForm::OnEnChangeAnimationTop()
{
	AllowOnlyRealNum(&m_tbAniTop, true, m_strAniTop);
	m_tbAniTop.GetWindowTextW(m_strAniTop);

	m_fTop = _tstof(m_strAniTop);

	_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
	g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
}


void CChildForm::OnDeltaposAnimationTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fTop = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= m_fTop) && (100.f >= m_fTop))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), m_fTop);
		m_strAniTop = sValue;
		m_tbAniTop.SetWindowTextW(m_strAniTop);
		_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
		g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
	}
	*pResult = 0;
}


void CChildForm::OnEnChangeAnimationBottom()
{
	AllowOnlyRealNum(&m_tbAniBottom, true, m_strAniBottom);
	m_tbAniBottom.GetWindowTextW(m_strAniBottom);

	m_fBottom = _tstof(m_strAniBottom);

	_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
	g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
}


void CChildForm::OnDeltaposRootBoneBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fBottom = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= m_fBottom) && (100.f >= m_fBottom))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), m_fBottom);
		m_strAniBottom = sValue;
		m_tbAniBottom.SetWindowTextW(m_strAniBottom);
		_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
		g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
	}
	*pResult = 0;
}

void CChildForm::OnEnChangeAnimationPos()
{
	AllowOnlyRealNum(&m_tbAniPos, true, m_strAniPos);
	m_tbAniPos.GetWindowTextW(m_strAniWidth);

	m_fPos = _tstof(m_strAniPos);

	_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
	g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
}

void CChildForm::OnDeltaposRootBonePosZ3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	m_fPos = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= m_fPos) && (100.f >= m_fPos))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), m_fPos);
		m_strAniPos = sValue;
		m_tbAniPos.SetWindowTextW(m_strAniPos);
		_float fArr[3] = { m_fTop, m_fBottom, m_fPos };
		g_vecAniCube[m_iAniIndex]->Set_VerticesHeight(&fArr);
	}
	*pResult = 0;
}



void CChildForm::OnBnClickedAniAxis(UINT uiID)
{
	g_vecBoneTransfrom[m_iAniBoneSelect]->Init_ActiveAngle();

	cout << "애니 본 인덱스" << m_iAniBoneSelect << endl;
 	switch (uiID)
	{
	case RADIO_ANI_AXIS_1:
		g_vecAniInfo[m_iAniInfoIndex].m_varr[m_iAniBoneSelect] = D3DXVECTOR3{ 1.f, 0.f, 0.f };
		break;
	case RADIO_ANI_AXIS_2:
		g_vecAniInfo[m_iAniInfoIndex].m_varr[m_iAniBoneSelect] = D3DXVECTOR3{ 0.f, 1.f, 0.f };
		break;
	case RADIO_ANI_AXIS_3:
		g_vecAniInfo[m_iAniInfoIndex].m_varr[m_iAniBoneSelect] = D3DXVECTOR3{0.f, 0.f, 1.f};
		break;
	}
}

void CChildForm::OnBnClickedAniDir(UINT uiID)
{
	switch (uiID)
	{
	case RADIO_ANI_DIR_1:
		g_vecAniInfo[m_iAniInfoIndex].uDir[m_iAniBoneSelect] = 0x00;
		g_vecAniInfo[m_iAniInfoIndex].uDir[m_iAniBoneSelect] |= 0b10;
		g_vecBoneTransfrom[m_iAniBoneSelect]->Set_Animation(m_fAniMaxAngle[m_iAniBoneSelect], 1.f);
		break;
	case RADIO_ANI_DIR_2:
		g_vecAniInfo[m_iAniInfoIndex].uDir[m_iAniBoneSelect] = 0x00;
		g_vecAniInfo[m_iAniInfoIndex].uDir[m_iAniBoneSelect] |= 0b01;
		g_vecBoneTransfrom[m_iAniBoneSelect]->Set_Animation(m_fAniMaxAngle[m_iAniBoneSelect], -1.f);
		break;
	}
}


void CChildForm::OnBnClickedRoot()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_ROOT;
}


void CChildForm::OnBnClickedPelvis()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_PELVIS;
}


void CChildForm::OnBnClickedSpine()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_SPINE;
}


void CChildForm::OnBnClickedNeck()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_NECK;
}


void CChildForm::OnBnClickedLeftleg()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_LEFTLEG;
}


void CChildForm::OnBnClickedRightleg()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_RIGHTLEG;
}


void CChildForm::OnBnClickedLeftarm()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_LEFTARM;
}


void CChildForm::OnBnClickedRightarm()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_RIGHTARM;
}


void CChildForm::OnBnClickedLeftelbow()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_LEFTELBOW;
}


void CChildForm::OnBnClickedRightelbow()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_RIGHTELBOW;
}


void CChildForm::OnBnClickedLeftankle()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_LEFTANKLE;
}


void CChildForm::OnBnClickedRightankle()
{
	g_vecAniInfo[m_iAniInfoIndex].uMotion ^= 1UL << CTest::INV_RIGHTANKLE;
}


void CChildForm::OnCbnSelchangeAniSelectBone()
{
	m_iAniBoneSelect = m_cbAniBone.GetCurSel();
}


void CChildForm::OnCbnSelchangeAniSelectAni()
{
	m_iAniInfoIndex = m_cbAniSelect.GetCurSel();
	g_pTest->Set_TestState((CTest::TEST_STATE)m_iAniInfoIndex);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_ROOT))
		m_checkBoxRoot.SetCheck(TRUE);
	else
		m_checkBoxRoot.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_PELVIS))
		m_checkBoxPelvis.SetCheck(TRUE);
	else
		m_checkBoxPelvis.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_SPINE))
		m_checkBoxSpine.SetCheck(TRUE);
	else
		m_checkBoxSpine.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_NECK))
		m_checkBoxNeck.SetCheck(TRUE);
	else
		m_checkBoxNeck.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_LEFTLEG))
		m_checkBoxLeftLeg.SetCheck(TRUE);
	else
		m_checkBoxLeftLeg.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_RIGHTLEG))
		m_checkBoxRightLeg.SetCheck(TRUE);
	else
		m_checkBoxRightLeg.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_LEFTARM))
		m_checkBoxLeftArm.SetCheck(TRUE);
	else
		m_checkBoxLeftArm.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_RIGHTARM))
		m_checkBoxRightArm.SetCheck(TRUE);
	else
		m_checkBoxRightArm.SetCheck(FALSE);
	//Modifying
	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_LEFTELBOW))
		m_checkBoxLeftElbow.SetCheck(TRUE);
	else
		m_checkBoxLeftElbow.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_RIGHTELBOW))
		m_checkBoxRightElbow.SetCheck(TRUE);
	else
		m_checkBoxRightElbow.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_LEFTANKLE))
		m_checkBoxLeftAnkle.SetCheck(TRUE);
	else
		m_checkBoxLeftAnkle.SetCheck(FALSE);

	if (g_vecAniInfo[m_iAniInfoIndex].uMotion SHIFT_OPERATOR(CTest::INV_RIGHTANKLE))
		m_checkBoxRightAnkle.SetCheck(TRUE);
	else
		m_checkBoxRightAnkle.SetCheck(FALSE);
}


void CChildForm::AnimationMaxAngleChagned()
{
	AllowOnlyRealNum(&m_tbAniMaxAngle, true, m_strAniMaxAngle);
	m_tbAniMaxAngle.GetWindowTextW(m_strAniMaxAngle);

	m_fAniMaxAngle[m_iAniBoneSelect] = _tstof(m_strAniMaxAngle);

	g_vecAniInfo[m_iAniInfoIndex].fAngle[m_iAniBoneSelect] = m_fAniMaxAngle[m_iAniBoneSelect];
	g_vecBoneTransfrom[m_iAniBoneSelect]->Set_MaxAngle(g_vecAniInfo[m_iAniInfoIndex].fAngle[m_iAniBoneSelect]);
}


void CChildForm::OnDeltaposAnimationMaxAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strAniMaxAngle = sValue;
		m_tbAniMaxAngle.SetWindowTextW(sValue);
	}
	*pResult = 0;
}


void CChildForm::EnChangeMinAngle()
{
	AllowOnlyRealNum(&m_tbAniMinAngle, true, m_strAniMinAngle);
	m_tbAniMinAngle.GetWindowTextW(m_strAniMinAngle);

	m_fAniMinAngle[m_iAniBoneSelect] = _tstof(m_strAniMinAngle);

	g_vecAniInfo[m_iAniInfoIndex].fAngle[m_iAniBoneSelect] = m_fAniMinAngle[m_iAniBoneSelect];

	g_vecBoneTransfrom[m_iAniBoneSelect]->Set_LocalAngle(g_vecAniInfo[m_iAniInfoIndex].fAngle[m_iAniBoneSelect]);
}


void CChildForm::OnDeltaposAnimationMinAngle(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	float fVal = pNMUpDown->iPos * 0.1 + pNMUpDown->iDelta* 0.1;

	if ((-100.f <= fVal) && (100.f >= fVal))
	{
		CString sValue;
		sValue.Format(_T("%3.2f"), fVal);
		m_strAniMinAngle = sValue;
		m_tbAniMinAngle.SetWindowTextW(sValue);
	}
	*pResult = 0;
}

void CChildForm::OnBnClickedSaveButton()
{
	CParser().Save_Process_Animation();
}


void CChildForm::OnBnClickedLoadButton()
{
	CParser().Load_Process_Animation();
}
