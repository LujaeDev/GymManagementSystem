#pragma once
#include "afxdialogex.h"


// CDelTab2 대화 상자

class CDelTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDelTab2)

public:
	CDelTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDelTab2();
	void showList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_ListCtrl;
	CEdit CEditTrainerNo;
	afx_msg void OnBnClickedButtonDel2();
};
