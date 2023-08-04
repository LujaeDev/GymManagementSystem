#pragma once
#include "afxdialogex.h"


// CSelectDlg 대화 상자

class CSelTab1;
class CSelTab2;
class CSelTab3;
class CSelTab4;
class CSelTab5;


class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSelectDlg();

	CSelTab1* pDlg1;
	CSelTab2* pDlg2;
	CSelTab3* pDlg3;
	CSelTab4* pDlg4;
	CSelTab5* pDlg5;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcmenubutton1();
	CTabCtrl mSelTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
