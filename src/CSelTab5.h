#pragma once
#include "afxdialogex.h"


// CSelTab5 대화 상자

class CSelTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTab5)

public:
	CSelTab5(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelTab5();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEL_5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButtonSel4();
	CEdit m_editProgramName;
};
