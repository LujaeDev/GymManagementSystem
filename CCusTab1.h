#pragma once
#include "afxdialogex.h"


// CCusTab1 대화 상자

class CCusTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab1)

public:
	CCusTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_editProgramName;
	CListCtrl m_ListCtrl;
	CEdit m_EditProgeamNo;
	CEdit m_editAttr1;
	CEdit m_editAttr2;
	CEdit m_editAttr3;
	CEdit m_editAttr4;
	CEdit m_editAttr5;
	CEdit* m_ArrAttrValue[5] = { &m_editAttr1, &m_editAttr2, &m_editAttr3, &m_editAttr4, &m_editAttr5};
	afx_msg void OnBnClickedButton1Load();
	afx_msg void OnBnClickedButtonCus2Execute();
	CEdit m_EditSQL;
};
