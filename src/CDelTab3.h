#pragma once
#include "afxdialogex.h"


// CDelTab3 대화 상자

class CDelTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CDelTab3)

public:
	CDelTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDelTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	CListCtrl m_ListCtrl1;
	afx_msg void OnBnClickedButtonDel3();
	void showProduct();
	void showPurchaseHistory();
};
