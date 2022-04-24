#pragma once



// CChildDlg form view

class CChildDlg : public CFormView
{
	DECLARE_DYNCREATE(CChildDlg)

protected:
	CChildDlg();           // protected constructor used by dynamic creation
	virtual ~CChildDlg();

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


