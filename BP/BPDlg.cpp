
// BPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BP.h"
#include "BPDlg.h"
#include "afxdialogex.h"


#include "..\Flood\Utilities\InputTargetDataSet.h"
#include "..\Flood\MultilayerPerceptron\MultilayerPerceptron.h"
#include "..\Flood\ObjectiveFunctional\NormalizedSquaredError.h"
#include "..\Flood\TrainingAlgorithm\QuasiNewtonMethod.h"
#include "..\Flood/Utilities\PatternRecognitionUtilities.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"vfw32.lib")
using namespace Flood;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBPDlg 对话框
UINT TrainRatio = 75;
UINT TestRatio = 25;
UINT MaxTrainNum = 3000;
double StudyRatio = 0.01;
Vector<double> binary_classification_test(6,0.0);
Matrix<int> confusion_matrix(2,2,0);


CBPDlg::CBPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBPDlg::IDD, pParent)
	, m_pThreadTrain(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_TRAIN_RATIO, m_TrainRatio);
	//DDX_Text(pDX, IDC_TEST_RATIO, m_TestRatio);
	DDX_Control(pDX, IDC_ACTIVATION_HIDE, m_HideActivationFun);
	DDX_Control(pDX, IDC_ACTIVATION_OUTPUT, m_OutputActivationFun);
	DDX_Control(pDX, IDC_TRAIN_FUN, m_TrainFun);
	DDX_Control(pDX, IDC_OPEN, m_OpenFile);
	DDX_Control(pDX, IDC_EDIT1, m_FilePathName);
	//DDX_Text(pDX, IDC_MAXTRAIN_NUM, m_MaxTrainNum);
	DDX_Control(pDX, IDC_IS_SETTING, m_isSetting);
}

BEGIN_MESSAGE_MAP(CBPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_OPEN, &CBPDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_STRAT_TRAIN, &CBPDlg::OnBnClickedStratTrain)
	ON_BN_CLICKED(IDC_SETTING, &CBPDlg::OnBnClickedSetting)
	ON_MESSAGE(TRAIN_THREAD_EXIT, &CBPDlg::TrainThreadExit)
	ON_BN_CLICKED(IDC_CLASSFIL, &CBPDlg::OnBnClickedClassfil)
	ON_COMMAND(IDM_HELP_ABOUT, &CBPDlg::OnHelpAbout)
	ON_BN_CLICKED(IDC_CHECK_CLOSEMUSIC, &CBPDlg::OnBnClickedCheckClosemusic)
	ON_BN_CLICKED(IDC_ADVANCE, &CBPDlg::OnBnClickedAdvance)
END_MESSAGE_MAP()


// CBPDlg 消息处理程序

BOOL CBPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//HWND hMCI;
	CString choose = _T("./res/一千年以后.mp3");
	m_hMCI = MCIWndCreate(NULL, AfxGetApp()->m_hInstance, WS_POPUP | MCIWNDF_NOPLAYBAR | MCIWNDF_NOMENU, choose);
	MCIWndPlay(m_hMCI);
	
	m_HideActivationFun.AddString(_T("Logistic"));
	m_HideActivationFun.AddString(_T("HyperbolicTangent"));
	m_HideActivationFun.AddString(_T("Linear"));
	m_HideActivationFun.SetCurSel(1);

	m_OutputActivationFun.AddString(_T("Threshold"));
	m_OutputActivationFun.AddString(_T("Linear"));
	m_OutputActivationFun.SetCurSel(m_OutputActivationFun.FindString(-1,_T("Linear")));

	m_TrainFun.AddString(_T("Gradient descent"));    //梯度下降
	m_TrainFun.AddString(_T("Quasi-Newton method"));  //拟牛顿法
	m_TrainFun.SetCurSel(1);

	CString strRatio;
	strRatio.Format(_T("%d"),TrainRatio);
	((CEdit *)GetDlgItem(IDC_TRAIN_RATIO))->SetWindowTextW(strRatio);
	strRatio = "";
	strRatio.Format(_T("%d"), TestRatio);
	((CEdit *)GetDlgItem(IDC_TEST_RATIO))->SetWindowTextW(strRatio);
	
	CString strMaxTrainNum;
	strMaxTrainNum.Format(_T("%d"), MaxTrainNum);
	((CEdit *)GetDlgItem(IDC_MAXTRAIN_NUM))->SetWindowTextW(strMaxTrainNum);

	CString strStudyRatio;
	strStudyRatio.Format(_T("%1.2f"), StudyRatio);
	((CEdit *)GetDlgItem(IDC_STADY_RATIO))->SetWindowTextW(strStudyRatio);

	GetDlgItem(IDC_DRAW)->GetClientRect(m_rectGraph);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CDC *pDC = GetDlgItem(IDC_DRAW)->GetDC();
	pDC->MoveTo(m_rectGraph.left + 50, m_rectGraph.bottom - 50);   //绘制x轴
	pDC->LineTo(m_rectGraph.right - 50, m_rectGraph.bottom - 50);
	pDC->MoveTo(m_rectGraph.right - 60, m_rectGraph.bottom - 55);
	pDC->LineTo(m_rectGraph.right - 50, m_rectGraph.bottom - 50);
	pDC->LineTo(m_rectGraph.right - 60, m_rectGraph.bottom - 45);

	pDC->MoveTo(m_rectGraph.left + 50, m_rectGraph.bottom - 50);   //绘制y轴
	pDC->LineTo(m_rectGraph.left + 50, m_rectGraph.top + 10);
	pDC->MoveTo(m_rectGraph.left + 45, m_rectGraph.top + 20);
	pDC->LineTo(m_rectGraph.left + 50, m_rectGraph.top + 10);
	pDC->LineTo(m_rectGraph.left + 55, m_rectGraph.top + 20);

	ReleaseDC(pDC);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CBPDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_menu);
	return 0;
}


void CBPDlg::OnBnClickedOpen()
{
	// TODO: Add your control notification handler code here
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("data file (*.dat)|*.dat|txt file (*.txt)|*.txt|All file (*.*)|*.*||"));
	if (IDOK == filedlg.DoModal())
	{
		CString m_FilePath;
		m_FilePath = filedlg.GetPathName();
		m_FilePathName.SetWindowTextW(m_FilePath);
	}

	CString IntOutNum;
	IntOutNum = "2";
	((CEdit *)GetDlgItem(IDC_INPUT_NUM))->SetWindowTextW(IntOutNum);
	IntOutNum.Empty();
	IntOutNum = "2";
	((CEdit *)GetDlgItem(IDC_OUTPUT_NUM))->SetWindowTextW(IntOutNum);
	IntOutNum.Empty();
	IntOutNum = "1";
	((CEdit *)GetDlgItem(IDC_HIDE_NUM))->SetWindowTextW(IntOutNum);
}

BOOL m_ThreadRunFlag = FALSE;
UINT Thread_Train(LPVOID lpParam)
{

	srand((unsigned)time(NULL));

	InputTargetDataSet itds(100, 2, 1);

	CBPDlg *bpDlg = (CBPDlg *)lpParam;

	char filepath[250] = { 0 };
	GetWindowTextA(bpDlg->m_FilePathName, (LPSTR)filepath, 250);
	itds.load_data(filepath);

	itds.split_random_indices((double)TrainRatio / 100, 0.0, (double)TestRatio / 100);

	itds.set_variable_name(0, "x1");
	itds.set_variable_name(1, "x2");
	itds.set_variable_name(2, "y");
	
	Vector< Vector<std::string> > variables_information = itds.get_variables_information();

	Vector< Vector<double> > variables_statistics = itds.scale_input_variables_mean_standard_deviation();

	// Multilayer perceptron object

	MultilayerPerceptron mlp(2, 2, 1);

	int index_hide = ((CComboBox *)bpDlg->GetDlgItem(IDC_ACTIVATION_HIDE))->GetCurSel();
	mlp.set_hidden_layer_activation_function(index_hide);

	int index_output = ((CComboBox *)(bpDlg->GetDlgItem(IDC_ACTIVATION_OUTPUT)))->GetCurSel();
	mlp.set_output_layer_activation_function(index_output);

	mlp.set_variables_information(variables_information);
	mlp.set_variables_statistics(variables_statistics);
	
	//NormalizedSquaredError ObjectiveFunction

	NormalizedSquaredError nse(&mlp, &itds);

	// Quasi-Newton method object

	QuasiNewtonMethod qnm(&nse);

	qnm.set_first_training_rate(StudyRatio);  //设置学习率
	CString strMax_Epoc;
	((CEdit *)bpDlg->GetDlgItem(IDC_MAXTRAIN_NUM))->GetWindowTextW(strMax_Epoc);
	int max_epoch = 0;
	swscanf_s(strMax_Epoc, _T("%d"), &max_epoch);
	qnm.set_maximum_epochs_number(max_epoch);

	qnm.set_reserve_evaluation_history(true);
	
	qnm.train();    //训练

	// Pattern recognition utilities object

	PatternRecognitionUtilities pru(&mlp, &itds);

	binary_classification_test = pru.binary_classification_test();
	confusion_matrix = pru.calculate_confusion();
	m_ThreadRunFlag = FALSE;

	PostMessage(FindWindow(NULL,_T("BP神经网络")), TRAIN_THREAD_EXIT, 0, 1);
	return 0;
}


void CBPDlg::OnBnClickedStratTrain()
{
	// TODO: Add your control notification handler code here

	CString strStudy;
	((CEdit *)GetDlgItem(IDC_STADY_RATIO))->GetWindowTextW(strStudy);
	swscanf_s(strStudy, _T("%f"), &StudyRatio);      //获取当前的学习率，并保存在内存变量中

	if (BST_UNCHECKED == m_isSetting.GetCheck())
	{
		MessageBox(_T("请输入最大训练次数"), _T("Warning"), MB_ICONWARNING | MB_OK);
		return;
	}

	if (FALSE == m_ThreadRunFlag)
	{
		m_ThreadRunFlag = TRUE;
		m_pThreadTrain = AfxBeginThread(Thread_Train, this);//开启线程
	}

}




void CBPDlg::OnBnClickedSetting()
{
	// TODO: Add your control notification handler code here
	CString m_strRatio;

	((CEdit *)GetDlgItem(IDC_TRAIN_RATIO))->GetWindowTextW(m_strRatio);
	swscanf_s(m_strRatio, _T("%d"), &TrainRatio);

	m_strRatio = "";

	((CEdit *)GetDlgItem(IDC_TEST_RATIO))->GetWindowTextW(m_strRatio);
	swscanf_s(m_strRatio, _T("%d"), &TestRatio);

	if (100 != TrainRatio + TestRatio)
	{
		MessageBox(_T("训练和测试比例之和不为100%，请重新输入数据！"), _T("Warning"), MB_ICONWARNING|MB_OK);
		return;
	}

	((CEdit *)GetDlgItem(IDC_TRAIN_RATIO))->EnableWindow(FALSE);
	((CEdit *)GetDlgItem(IDC_TEST_RATIO))->EnableWindow(FALSE);

	//测试
	//CString strIfo;
	//strIfo.Format(_T("width = %d,height = %d"), m_rectGraph.Width(), m_rectGraph.Height());
	//MessageBox(strIfo);
}



LRESULT CBPDlg::TrainThreadExit(WPARAM wParam, LPARAM lParam)
{
	//测试
	//if (1 == lParam)
	//	AfxMessageBox(_T("Train Thread is exit!"));
	GetDlgItem(IDC_TRAIN_RATIO)->EnableWindow();
	GetDlgItem(IDC_TEST_RATIO)->EnableWindow();


	return 0;
}

void CBPDlg::OnBnClickedClassfil()
{
	// TODO: Add your control notification handler code here
	//m_resultDlg.Create(_T("分类结果"),NULL);
	CBPDlgResult *m_resultDlg = new CBPDlgResult();
	m_resultDlg->Create(IDD_DLG_RESULT,this);
	m_resultDlg->ShowWindow(SW_SHOW);

	double result[6];
	for (int i = 0; i < 6; i++)
	{
		result[i] = binary_classification_test[i];
	}

	int confusion[4] = { 0 };
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	{
		confusion[i*2 + j] = confusion_matrix[i][j];
	}


	m_resultDlg->ShowResult(result);
	m_resultDlg->ShowConfusion(confusion);
}


void CBPDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg *m_aboutDlg = new CAboutDlg();
	m_aboutDlg->Create(IDD_ABOUTBOX, this);
	m_aboutDlg->ShowWindow(SW_SHOW);
}


void CBPDlg::OnBnClickedCheckClosemusic()
{
	// TODO: Add your control notification handler code here
	if (((CButton *)GetDlgItem(IDC_CHECK_CLOSEMUSIC))->GetCheck() == BST_CHECKED)
		MCIWndStop(m_hMCI);
	else
		MCIWndPlay(m_hMCI);
}





void CBPDlg::OnBnClickedAdvance()
{
	// TODO: Add your control notification handler code here
	CBPDlgFrame *m_BPFrameDlg = new CBPDlgFrame;
	m_BPFrameDlg->Create(IDD_DLG_FRAME, this);
	m_BPFrameDlg->ShowWindow(SW_SHOW);
}
