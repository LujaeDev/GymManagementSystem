#pragma once
#include "afxdialogex.h"


// CUpdTab3 대화 상자

class CUpdTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdTab3)

public:
	CUpdTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPD_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	void showList();
	afx_msg void OnBnClickedButtonUpd3();
};
