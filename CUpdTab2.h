#pragma once
#include "afxdialogex.h"


// CUpdTab2 대화 상자

class CUpdTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdTab2)

public:
	CUpdTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPD_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CListCtrl m_ListCtrl;
	void showList();
	void sqlUpdate();
};
