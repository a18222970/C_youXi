
// MeGemgDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MeGemg.h"
#include "MeGemgDlg.h"
#include "afxdialogex.h"

#include "L_zhiXing.h"

#include<atltrace.h>//ATLTRACE输出
#include <iostream>//标准库,std输出

#ifdef _DEBUG
#define new DEBUG_NEW

#endif

L_zhiXing l_zhiXin;
L_GongJu l_gongJu;
L_GongJu::J_ti_qu_xin_xi j_get_xiXin{ "Sword2 Class", "Sword2 Window" ,NULL,NULL,NULL,NULL,NULL };

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


// CMeGemgDlg 对话框



CMeGemgDlg::CMeGemgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEGEMG_DIALOG, pParent)
	, dan_xuan_xue_liang(FALSE)
	, dan_xuan_nei_li(FALSE)
	, dan_xuan_ti_li(FALSE)
	, dan_xuan_qian(FALSE)
	, dan_xuan_chuan_qiang(FALSE)
	, bian_ji_x_ZB(_T(""))
	, bian_ji_y_ZB(_T(""))
	, wen_ben_xiaoXi(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeGemgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	/*控件与控件值进行绑定*/
	DDX_Control(pDX, IDC_BUTTON1, an_niu_qingDongZuoBi);
	DDX_Check(pDX, IDC_CHECK1, dan_xuan_xue_liang);
	DDX_Check(pDX, IDC_CHECK2, dan_xuan_nei_li);
	DDX_Check(pDX, IDC_CHECK3, dan_xuan_ti_li);
	DDX_Check(pDX, IDC_CHECK4, dan_xuan_qian);
	DDX_Check(pDX, IDC_CHECK5, dan_xuan_chuan_qiang);
	DDX_Text(pDX, IDC_EDIT2, bian_ji_x_ZB);
	DDX_Text(pDX, IDC_EDIT1, bian_ji_y_ZB);
	DDX_Text(pDX, IDC_TEXT, wen_ben_xiaoXi);
}

BEGIN_MESSAGE_MAP(CMeGemgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	/*控件对应的执行函数*/
	ON_BN_CLICKED(IDOK, &CMeGemgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMeGemgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CMeGemgDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK1, &CMeGemgDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMeGemgDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMeGemgDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CMeGemgDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CMeGemgDlg::OnBnClickedCheck5)


	ON_EN_CHANGE(IDC_EDIT2, &CMeGemgDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CMeGemgDlg::OnEnChangeEdit1)
	ON_STN_CLICKED(IDC_TEXT, &CMeGemgDlg::OnStnClickedText)
END_MESSAGE_MAP()


// CMeGemgDlg 消息处理程序

BOOL CMeGemgDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMeGemgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMeGemgDlg::OnPaint()
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
HCURSOR CMeGemgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/****************************
*
******************************/
void CMeGemgDlg::OnBnClickedOk()
{
	// 瞬移
	UpdateData(TRUE);
	GetDlgItem(IDC_STATIC)->SetWindowTextW(bian_ji_x_ZB);

}


void CMeGemgDlg::OnBnClickedButton1()
{
	//L_GongJu::J_ti_qu_xin_xi j_get_xiXin{ "Sword2 Class", "Sword2 Window" ,NULL,NULL,NULL,NULL };
	// 启动
	UpdateData(TRUE);//更新控件
	if (l_zhiXin.get_xin_xi("Sword2 Class", "Sword2 Window", &j_get_xiXin))
	{

		CString a;//MFC定义的字符串类
		a.Format(L"%p", j_get_xiXin.n_jiZhi);//将其他类型数据转换为字符串类型


		std::cout << "jizhishi:   "<<std::hex<<j_get_xiXin.n_jiZhi << std::endl;
		ATLTRACE("输出窗口输出内容");//调试模式VS 输出窗口输出
		GetDlgItem(IDC_STATIC)->SetWindowText(L"游戏基址为: "+a);
		showMsg(L"dfdfd");
		//GetDlgItem(IDC_STATIC)->SetWindowTextW((LPCTSTR)&j_get_xiXin.n_PDI);//还未能显示
	}
	else
	{
		GetDlgItem(IDC_STATIC)->SetWindowTextW(L"检测到游戏进程,作弊功能开启!");
	}
}


void CMeGemgDlg::OnBnClickedCancel()
{
	// 退出
	CDialogEx::OnCancel();
}


void CMeGemgDlg::OnBnClickedCheck1()
{
	// 无限血量
	/*TRUE   控件的值=>变量*/
	UpdateData(TRUE);
	if (dan_xuan_xue_liang)
	{
		//AfxMessageBox(L"开启无限血量");
		GetDlgItem(IDC_STATIC)->SetWindowTextW(L"无敌开启");
		//l_gongJu.xiu_gai_ji_qi_ma(1, &j_get_xiXin);
		l_gongJu.zhi_xing_1(1,&j_get_xiXin);

		if (!l_zhiXin.get_hp())
		{
			l_zhiXin.set_hp(true);
		}
	} 
	else
	{
		GetDlgItem(IDC_STATIC)->SetWindowTextW(L"无敌关闭");
		l_gongJu.zhi_xing_1(2, &j_get_xiXin);
		//AfxMessageBox((LPCTSTR)"moohjjkh");
		if (l_zhiXin.get_hp())
		{
			l_zhiXin.set_hp(false);
		}
	}

}


void CMeGemgDlg::OnBnClickedCheck2()
{
	// 无限内力
	/*TRUE   控件的值=>变量*/
	UpdateData(TRUE);
	if (dan_xuan_nei_li)
	{
		l_gongJu.zhi_xing_1(3, &j_get_xiXin);
	} 
	else
	{
		l_gongJu.zhi_xing_1(4, &j_get_xiXin);
	}
}


void CMeGemgDlg::OnBnClickedCheck3()
{
	// 无限体力  /////2
	/*TRUE   控件的值=>变量*/
	UpdateData(TRUE);
	if (dan_xuan_ti_li)
	{
		l_gongJu.zhi_xing_1(5, &j_get_xiXin);
		/////////
	}
	else
	{
		l_gongJu.zhi_xing_1(6, &j_get_xiXin);
	}
}


void CMeGemgDlg::OnBnClickedCheck4()
{
	// 金钱
}


void CMeGemgDlg::OnBnClickedCheck5()
{
	// 穿墙
}


void CMeGemgDlg::OnEnChangeEdit2()
{
	/*X坐标*/
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMeGemgDlg::OnEnChangeEdit1()
{
	/*Y坐标*/
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMeGemgDlg::OnStnClickedText()
{
	//单选框 IDC_TEXT
	// TODO: 在此添加控件通知处理程序代码
}


// //文本框内容改变
/*给指定控件发送消息*/
void CMeGemgDlg::showMsg(LPCTSTR msg)
{

	GetDlgItem(IDC_TEXT)->SetWindowText(msg);
	//GetDlgItem(IDC_STATIC)->SetWindowText(msg);
}
