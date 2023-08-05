#pragma once
#include "afxdialogex.h"


// CSelTab2 대화 상자

class CSelTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTab2)

public:
	CSelTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEL_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButtonSel2();
public:
	bool firstQuery = true;
	CEdit CEditMemberNo;
	afx_msg void OnLvnItemchangedListSel2(NMHDR* pNMHDR, LRESULT* pResult);
};
