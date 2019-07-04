// BPDlgFrame.cpp : implementation file
//

#include "stdafx.h"
#include "BP.h"
#include "BPDlgFrame.h"
#include "afxdialogex.h"


// CBPDlgFrame dialog

IMPLEMENT_DYNAMIC(CBPDlgFrame, CDialogEx)

CBPDlgFrame::CBPDlgFrame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBPDlgFrame::IDD, pParent)
{

}

CBPDlgFrame::~CBPDlgFrame()
{
}

void CBPDlgFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBPDlgFrame, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBPDlgFrame message handlers


void CBPDlgFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	//HBRUSH brush;
	//ÊäÈë²ã
	//brush = (HBRUSH)GetStockObject((int)RGB(200, 50, 50));
	//dc.SelectObject(brush);
	dc.Ellipse(50, 50, 100, 100);
	dc.Ellipse(50, 200, 100, 250);
	dc.DrawText(_T("inputs"), CRect(50, 270, 100, 300), DT_MODIFYSTRING);
	/*ÊäÈë---->Òþ²ã*/
	dc.MoveTo(100,75);     
	dc.LineTo(200,75);
	dc.LineTo(100, 225);
	dc.LineTo(200, 225);
	dc.LineTo(100, 75);

	/*Òþ²ã---->Êä³ö*/
	dc.MoveTo(250, 75);
	dc.LineTo(350, 150);
	dc.LineTo(250, 225);


	dc.MoveTo(175, 60);  //¼ýÍ·
	dc.LineTo(200, 75);
	dc.LineTo(175, 90);

	dc.MoveTo(175, 210); //¼ýÍ·
	dc.LineTo(200, 225);
	dc.LineTo(175, 240);

	
	//Òþ²ã
	//brush = (HBRUSH)GetStockObject((int)RGB(50, 200, 50));
	//dc.SelectObject(brush);
	dc.Ellipse(200, 50, 250, 100);
	dc.Ellipse(200, 200, 250, 250);
	dc.DrawText(_T("hides"), CRect(200, 270, 250, 300), DT_MODIFYSTRING);
	//Êä³ö²ã
	//brush = (HBRUSH)GetStockObject((int)RGB(50, 50, 200));
	//dc.SelectObject(brush);
	dc.Ellipse(350, 125, 400, 175);
	dc.MoveTo(400, 150);
	dc.LineTo(450, 150);
	dc.MoveTo(425, 135);
	dc.LineTo(450, 150);
	dc.LineTo(425, 165);
	dc.DrawText(_T("output"), CRect(350, 200, 400, 230), DT_MODIFYSTRING);
}
