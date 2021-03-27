
// MeGemgDlg.h: 头文件
//

#pragma once


// CMeGemgDlg 对话框
class CMeGemgDlg : public CDialogEx
{
// 构造
public:
	CMeGemgDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEGEMG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// //启动作弊
	CButton an_niu_qingDongZuoBi;
	// //单选框_血量
	BOOL dan_xuan_xue_liang;
	// //单选框_内力
	BOOL dan_xuan_nei_li;
	// //单选框_体力
	BOOL dan_xuan_ti_li;
	// //单选框_金钱
	BOOL dan_xuan_qian;
	// //单选框 穿墙
	BOOL dan_xuan_chuan_qiang;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	// //X坐标
	CString bian_ji_x_ZB;
	// //Y坐标
	CString bian_ji_y_ZB;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	// //消息提示
	CString wen_ben_xiaoXi;
	afx_msg void OnStnClickedText();
	// //文本框内容改变
	void showMsg(LPCTSTR msg);
};
