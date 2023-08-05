#pragma once
#include "afxdialogex.h"


// CCusTab4 대화 상자

class CCusTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab4)

public:
	CCusTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editMemberNo;
	CEdit m_editProductNo;
	CEdit m_editQuantity;
	CEdit m_EditSQL;
	afx_msg void OnBnClickedButtonCus1Create();
	afx_msg void OnBnClickedButtonCusExecute();
	CString memberNo;
	CString productNo;
	CString quantity;
};
