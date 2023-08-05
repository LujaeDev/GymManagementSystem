#pragma once
#include "afxdialogex.h"


// CCustomDlg 대화 상자
class CCusTab1;
class CCusTab2;
class CCusTab3;
class CCusTab4;
class CCusTab0;
class CusTab5;

class CCustomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomDlg)

public:
	CCustomDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCustomDlg();

	CCusTab1* pDlg1;
	CCusTab2* pDlg2;
	CCusTab3* pDlg3;
	CCusTab4* pDlg4;
	CCusTab0* pDlg0;
	CusTab5* pDlg5;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUSTOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mCusTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
