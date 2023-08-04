#pragma once
#include "afxdialogex.h"


// CusTab5 대화 상자

class CusTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CusTab5)

public:
	CusTab5(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CusTab5();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editAddress;
	CComboBox m_ctrlCBox;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListCtrl;
};
