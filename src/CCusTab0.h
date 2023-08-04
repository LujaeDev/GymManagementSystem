#pragma once
#include "afxdialogex.h"


// CCusTab0 대화 상자

class CCusTab0 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab0)

public:
	CCusTab0(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab0();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedListCus0(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_ListCtrl;
	CEdit m_editQuery;
	afx_msg void OnBnClickedButtonQuery();
};
