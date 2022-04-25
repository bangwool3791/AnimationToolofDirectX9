#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CChildForm form view
#include "Transform.h"
#include "VIBuffer_Cube.h"
#include "Tool126View.h"

class CChildForm : public CFormView
{
	DECLARE_DYNCREATE(CChildForm)

	//Bone Key String
	const TCHAR* KEY_BONE_ROOT = L"Bone_Root";
	const TCHAR* KEY_BONE_PELVIS = L"Bone_Pelvis";
	const TCHAR* KEY_BONE_SPINE = L"Bone_Spine";
	const TCHAR* KEY_BONE_NECK = L"Bone_Neck";
	const TCHAR* KEY_BONE_LEFTLEG = L"Bone_LeftLeg";
	const TCHAR* KEY_BONE_RIGHTLEG = L"Bone_RightLeg";

	const TCHAR* KEY_BONE_LEFTARM = L"Bone_LeftArm";
	const TCHAR* KEY_BONE_RIGHTARM = L"Bone_RightArm";

	const TCHAR* KEY_BONE_LEFTELBOW = L"Bone_LeftElbow";
	const TCHAR* KEY_BONE_RIGHTELBOW = L"Bone_RightElbow";

	const TCHAR* KEY_BONE_LEFTANKLE = L"Bone_LeftAnkle";
	const TCHAR* KEY_BONE_RIGHTANKLE = L"Bone_RightAnkle";
	//Animation Key String
	const TCHAR* KEY_ANI_HEAD = L"Ani_Head";
	const TCHAR* KEY_ANI_BODY = L"Ani_Body";
	const TCHAR* KEY_ANI_LEFTARM = L"Ani_LeftArm";
	const TCHAR* KEY_ANI_RIGHTARM = L"Ani_RightArm";
	const TCHAR* KEY_ANI_LEFTLEG = L"Ani_LeftLeg";
	const TCHAR* KEY_ANI_RIGHTLEG = L"Ani_RightLeg";
	const TCHAR* KEY_ANI_LEFTELBOW= L"Ani_LeftElbow";
	const TCHAR* KEY_ANI_RIGHTELBOW = L"Ani_RightElbow";
	const TCHAR* KEY_ANI_LEFTANKLE = L"Ani_LeftAnkle";
	const TCHAR* KEY_ANI_RIGHTANKLE = L"Ani_RightAnkle";

public :
	const TCHAR* pBone[12] = { KEY_BONE_ROOT , KEY_BONE_PELVIS , KEY_BONE_SPINE , KEY_BONE_NECK , KEY_BONE_LEFTLEG ,
		KEY_BONE_RIGHTLEG , KEY_BONE_LEFTARM , KEY_BONE_RIGHTARM , KEY_BONE_LEFTELBOW , KEY_BONE_RIGHTELBOW ,
		KEY_BONE_LEFTANKLE ,
		KEY_BONE_RIGHTANKLE };
protected:
	CChildForm();          
	virtual ~CChildForm();
public :
private :
	unsigned int m_iBoneIndex = 0;
	unsigned int m_iAniIndex = 0;
	unsigned int m_iAniInfoIndex = 0;
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private :
	bool CChildForm::isDigit(CString EditStr , CString& _string)
	{
		int count = EditStr.GetLength();
		int i = 0;
		for ( i = 0; i < count; ++i)
		{
			char temp = EditStr.GetAt(i);

			if (i == 0 && temp == '-')
				continue;

			if(temp >= '0' && temp <= '9')
				continue;
			else break;
		}

		if (i == count)
		{
			_string = EditStr;
			return true;
		}
		else
		{
			return false;
		}
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()
private :
	CTest::TEST_STATE* m_eAniState = NULL;
	CTest* m_pTest = NULL;
	CTool126View::THREAD_DESC* m_stThreadDesc;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedTestButton();
	CTreeCtrl m_treeBone;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CComboBox m_cbBone;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnTvnSelchangedBoneTree(NMHDR *pNMHDR, LRESULT *pResult);

	CEdit m_tbRootBonePosX;
	CString m_strRootBonePosX;

	CEdit m_tbRootBonePosY;
	CString m_strRootBonePosY;

	CEdit m_tbRootBonePosZ;
	CString m_strRootBonePosZ;
	CSpinButtonCtrl m_SpinRootBonePosX;

	D3DXVECTOR3 m_vBoneLocalAxis;
	afx_msg void OnDeltaposRootBonePosX(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposRootBonePosY(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnDeltaposRootBonePosZ(NMHDR *pNMHDR, LRESULT *pResult);

	CSpinButtonCtrl m_SpinRootBonePosZ;
	CSpinButtonCtrl m_SpinRootBonePosY;

	void CChildForm::AllowOnlyRealNum(CEdit *cedit, bool minus, CString& _String);
	//CString CChildForm::GetRealNum(float fVal, bool minus, CString _String);
	afx_msg void OnEnChangeRootBonePosX();
	afx_msg void OnEnChangeRootBonePosY();
	afx_msg void OnEnChangeRootBonePosZ();
	CComboBox cb_boneAxis;
	//Bone Angle
	CEdit m_tbBoneAngle;
	CSpinButtonCtrl m_SpinBoneAngle;
	CString m_strBoneAngle;
	float	m_fBoneLocalAngle = 0.f;
	afx_msg void OnEnChangeBoneAngle();
	afx_msg void OnDeltaposBoneAngle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnEditupdateRootBoneAxis();
	afx_msg void OnCbnDropdownRootBoneAxis();
	//Animation Area
	CTreeCtrl m_treeAni;
	afx_msg void OnTvnSelchangedAnimationTree(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_tbAniWidth;
	CSpinButtonCtrl m_SpinAniWidth;
	CEdit m_tbAniTop;
	CSpinButtonCtrl m_spinAniTop;
	CEdit m_tbAniBottom;
	CSpinButtonCtrl m_spinAniBottom;
	CEdit m_tbAniPos;

	CSpinButtonCtrl m_SpinAniPos;
	CString m_strAniWidth;
	CString m_strAniTop;
	CString m_strAniBottom;
	CString m_strAniPos;

	_float m_fWitdh = 0.f;
	_float m_fTop = 0.f;
	_float m_fBottom = 0.f;
	_float m_fPos = 0.f;
	afx_msg void OnEnChangeAnimationWidth();
	afx_msg void OnEnChangeAnimationPos();
	afx_msg void OnDeltaposAnimationWidth(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRootBonePosZ3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeAnimationTop();
	afx_msg void OnDeltaposAnimationTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeAnimationBottom();
	afx_msg void OnDeltaposRootBoneBottom(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_BtnThreadRun;
	//Animation UI
	CButton m_radioAxis;
	afx_msg void OnBnClickedAniAxis(UINT uiID);
	BOOL m_bAniAxis;
	CButton m_radioDir;
	BOOL m_bRadioDir;
	afx_msg void OnBnClickedAniDir(UINT uiID);
	afx_msg void OnBnClickedRoot();
	afx_msg void OnBnClickedPelvis();
	afx_msg void OnBnClickedSpine();
	afx_msg void OnBnClickedNeck();
	afx_msg void OnBnClickedLeftleg();
	afx_msg void OnBnClickedRightleg();
	afx_msg void OnBnClickedLeftarm();
	afx_msg void OnBnClickedRightarm();
	afx_msg void OnBnClickedLeftelbow();
	afx_msg void OnBnClickedRightelbow();
	afx_msg void OnBnClickedLeftankle();
	afx_msg void OnBnClickedRightankle();

	CEdit m_tbAniMaxAngle;
	CSpinButtonCtrl m_spinAniMaxAngle;
	CString			m_strAniMaxAngle;
	_float		    m_fMaxAngle = 0.f;
	afx_msg void OnCbnSelchangeAniSelectBone();
	CComboBox m_cbAniSelect;
	afx_msg void OnCbnSelchangeAniSelectAni();

	CComboBox m_cbAniBone;
	_uint	  m_iAniBoneSelect = 0;

	_float     m_fAniMaxAngle[12];
	afx_msg void AnimationMaxAngleChagned();
	afx_msg void OnDeltaposAnimationMaxAngle(NMHDR *pNMHDR, LRESULT *pResult);

	CEdit m_tbAniMinAngle;
	CString			m_strAniMinAngle;
	_float		    m_fMinAngle = 0.f;
	CSpinButtonCtrl m_spinAniMinAngle;
	_float     m_fAniMinAngle[12];
	afx_msg void EnChangeMinAngle();
	afx_msg void OnDeltaposAnimationMinAngle(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedLoadButton();
	CButton m_checkBoxRoot;
	CButton m_checkBoxPelvis;
	CButton m_checkBoxSpine;
	CButton m_checkBoxNeck;
	CButton m_checkBoxLeftLeg;
	CButton m_checkBoxRightLeg;
	CButton m_checkBoxLeftArm;
	CButton m_checkBoxRightArm;
	CButton m_checkBoxLeftElbow;
	CButton m_checkBoxRightElbow;
	CButton m_checkBoxLeftAnkle;
	CButton m_checkBoxRightAnkle;
};


