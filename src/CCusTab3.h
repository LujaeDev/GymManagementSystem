#pragma once
#include "afxdialogex.h"


// CCusTab3 대화 상자

class CCusTab3 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab3)

public:
	CCusTab3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editMemberNo;
	CEdit m_editProgramNo;
	CEdit m_EditSQL;
	afx_msg void OnBnClickedButtonCus1Create();
	afx_msg void OnBnClickedButtonCusExecute();
	CString memberNo;
	CString programNo;
};
