#pragma once
#include "afxdialogex.h"


// CCusTab2 대화 상자

class CCusTab2 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab2)

public:
	CCusTab2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCus1Create();
	CEdit m_editMemberNo;
	CEdit m_editProgramNo;
	afx_msg void OnEnChangeEditProgramNo();
	CEdit m_EditSQL;
	afx_msg void OnBnClickedButtonCusExecute();
	CString memberNo;
	CString programNo;
};
