#pragma once
#include "afxdialogex.h"


// CUpdTab4 대화 상자

class CUpdTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdTab4)

public:
	CUpdTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPD_4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_ListCtrl1;
	CEdit m_EditLocker;
	void showMemberInfo();
	void showLockerInfo();
	afx_msg void OnBnClickedButtonUpd4();
};
