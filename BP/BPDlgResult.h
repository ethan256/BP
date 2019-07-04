#pragma once


// CBPDlgResult dialog

class CBPDlgResult : public CDialogEx
{
	DECLARE_DYNAMIC(CBPDlgResult)

public:
	CBPDlgResult(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBPDlgResult();

// Dialog Data
	enum { IDD = IDD_DLG_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	void ShowResult(double *result);
	void ShowConfusion(int *confusion);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
public:
	CDC m_cacheDC;
	CBitmap bitmap;
};
