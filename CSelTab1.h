#pragma once
#include "afxdialogex.h"


// CSelTab1 대화 상자

class CSelTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTab1)

public:
	CSelTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEL_1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButton1();
};
