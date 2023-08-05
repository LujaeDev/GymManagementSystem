#pragma once
#include "afxdialogex.h"


// CSelTab4 대화 상자

class CSelTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTab4)

public:
	CSelTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEL_4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonSel4();

	CListCtrl m_ListCtrl;
	CEdit m_editBrand;
};
