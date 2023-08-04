#pragma once
#include "afxdialogex.h"


// CSelTab3 대화 상자

class CSelTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTab3)

public:
	CSelTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEL_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButtonSel3();
};
