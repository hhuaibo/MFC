
// MFCDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC.h"
#include "MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDlg 对话框



CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, m_Sum(_T(""))
	, m_Span(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW, m_List);
	DDX_Text(pDX, IDC_EDIT_SUM, m_Sum);
	DDX_Text(pDX, IDC_EDIT_SPAN, m_Span);
	DDX_Control(pDX, IDC_SHOW, m_Show);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMFCDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CMFCDlg 消息处理程序

BOOL CMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	m_List.InsertColumn(0, _T("出队顺序"), LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, _T("出队号码"), LVCFMT_LEFT, 350);
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_List.SetExtendedStyle(dwStyle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCDlg::OnPaint()
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
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*****************************************************************************
*	Author: Huaibo
*	Date:   2019-5-30
*****************************************************************************/

void CMFCDlg::Start(int n, int m)
{
	m_List.DeleteAllItems();

	int *arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = i + 1;
	}
	int index = 0;
	CString result = _T("");
	for (int j = 1; j < n; j++)
	{
		for (int k = 1; k <= m;) {
			if (arr[index] != 0) {
				k++;
			}
			index = (index + 1) % n;
		}
		if (index == 0)
			arr[n - 1] = 0;
		else
			arr[index - 1] = 0;

		result.Format(_T("%d"), j);
		m_List.InsertItem(j - 1, result);

		if (index == 0) {
			result.Format(_T("%d号"), n);
			Select(n);
			Sleep(250);
		} else {
			result.Format(_T("%d号"), index);
			Select(index);
			Sleep(250);
		}

		m_List.SetItemText(j - 1, 1, result);
		//Select(n);
	}
	for (int i = 0; i < n; i++) {
		if (arr[i] != 0) {
			m_List.InsertItem(n - 1, _T("幸存者："));
			result.Format(_T("%d号"), i + 1);
			m_List.SetItemText(n - 1, 1, result);
			MessageBox(result, _T("幸存者："));
			break;
		}
	}

	delete[] arr; //释放内存
}

void CMFCDlg::Show()
{
	int m = GetDlgItemInt(IDC_EDIT_SUM); //人数
	CWnd * pWnd = GetDlgItem(IDC_SHOW);
	CDC * pControlDC = pWnd->GetDC();
	CString str;
	double x = 0;
	double y = 0;
	int count = 0;
	x = 90 * cos(count * 2 * 3.14 / m);
	y = 90 * sin(count * 2 * 3.14 / m);
	//pWnd->Invalidate();
	pWnd->UpdateWindow();
	pControlDC->SelectStockObject(BLACK_BRUSH);
	for (int count = 1; count < m + 1; count++)
	{
		double x = 0;
		double y = 0;
		x = 90 * cos(count * 2 * 3.14 / m);
		y = 90 * sin(count * 2 * 3.14 / m);
		pControlDC->Ellipse((int)x + 100, (int)y + 100, (int)x + 115, (int)y + 115);
		str.Format(_T("%d"), count);
		pControlDC->TextOut((int)x + 120, (int)y + 100, str);
	}
	pWnd->ReleaseDC(pControlDC);
}

void CMFCDlg::Select(int n)
{
	int m = GetDlgItemInt(IDC_EDIT_SUM);
	CWnd * pWnd = GetDlgItem(IDC_SHOW);
	CDC * pControlDC = pWnd->GetDC();
	//	CString str;
	double x = 0;
	double y = 0;
	x = 90 * cos(n * 2 * 3.14 / m);
	y = 90 * sin(n * 2 * 3.14 / m);

	//pWnd->Invalidate();
	pWnd->UpdateWindow();
	pControlDC->SelectStockObject(WHITE_BRUSH);
	//	pControlDC->Ellipse(n*30, 0, 20+n*30, 20);
	pControlDC->Ellipse((int)x + 100, (int)y + 100, (int)x + 115, (int)y + 115);
	//	DrawEllipse(n*30, 0,20);
	//	str.Format("%d", n);
	//	pControlDC->TextOut((int)x+100, (int)y+100,str);
	pWnd->ReleaseDC(pControlDC);
	Sleep(800);
}

void CMFCDlg::DrawEllipse(int x, int y, int r) //重载画圆函数
{ /*
	CClientDC dc(this);
	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(0xD1,0xFB,0xED));
	oldbrush=dc.SelectObject(&brush);
	dc.Ellipse(x-r,y-r,x+r,y+r);
	dc.SelectObject(oldbrush);
	*/
}

void CMFCDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	int sum = GetDlgItemInt(IDC_EDIT_SUM); //人数
	int span = GetDlgItemInt(IDC_EDIT_SPAN); //间隔
	if (sum < 2)
	{
		MessageBox(_T("输入错误,人数最少为2个！"));
		return;
	}
	if (span < 1)
	{
		MessageBox(_T("输入错误,间隔数最小为1！"));
		return;
	}
	Show();
	Start(sum, span);
}


void CMFCDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Sum = _T("");
	m_Span = _T("");
	UpdateData(FALSE);

	CWnd * pWnd = GetDlgItem(IDC_SHOW);
	CDC * pControlDC = pWnd->GetDC();
	pWnd->Invalidate();
	m_List.DeleteAllItems();
}
