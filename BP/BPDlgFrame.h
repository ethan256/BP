#pragma once


// CBPDlgFrame dialog

class CBPDlgFrame : public CDialogEx
{
	DECLARE_DYNAMIC(CBPDlgFrame)

public:
	CBPDlgFrame(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBPDlgFrame();

// Dialog Data
	enum { IDD = IDD_DLG_FRAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
