#pragma once
#include "afxdialogex.h"

class CDelTab1;
class CDelTab2;
class CDelTab3;
class CDelTab4;

// CDelDlg 대화 상자

class CDelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelDlg)

public:
	CDelDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDelDlg();

	CDelTab1* pDlg1;
	CDelTab2* pDlg2;
	CDelTab3* pDlg3;
	CDelTab4* pDlg4;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mDelTab;
	afx_msg void OnTcnSelchangeTabDel(NMHDR* pNMHDR, LRESULT* pResult);
};
