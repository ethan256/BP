// BPDlgResult.cpp : implementation file
//

#include "stdafx.h"
#include "BP.h"
#include "BPDlgResult.h"
#include "afxdialogex.h"



// CBPDlgResult dialog

IMPLEMENT_DYNAMIC(CBPDlgResult, CDialogEx)

CBPDlgResult::CBPDlgResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBPDlgResult::IDD, pParent)
{

}

CBPDlgResult::~CBPDlgResult()
{
}

void CBPDlgResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBPDlgResult, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBPDlgResult message handlers



void CBPDlgResult::ShowResult(double *result)
{

	CString strTemp;

	for (int index = 0; index < 6; index++)
	{
		strTemp.Format(_T("%f"), *(result+index));
		((CEdit *)GetDlgItem(IDC_CLS_ACE + index))->SetWindowTextW(strTemp);
		strTemp.Empty();
	}

}


void CBPDlgResult::ShowConfusion(int *confusion)
{

	CString strTemp;

	for (int i = 0; i < 4; i++)
	{
		strTemp.Format(_T("%d"), *(confusion+i));
		((CEdit *)GetDlgItem(IDC_TRUE_POSITIVE + i))->SetWindowTextW(strTemp);
		strTemp.Empty();
	}

}

void CBPDlgResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages

	CDC *cDC = (GetDlgItem(IDC_CLASS_RES))->GetDC();
	CImage image;
	image.Load(_T(".\\res\\input.png"));
	image.Draw(*cDC, 0, 0, 360, 330);
	ReleaseDC(cDC);
}
