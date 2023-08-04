#pragma once
#include "afxdialogex.h"


// CDelTab1 대화 상자

class CDelTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CDelTab1)

public:
	CDelTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDelTab1();
	void showList();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL_4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CEdit CEditMemberNo;
	afx_msg void OnBnClickedButtonDel1();
};
