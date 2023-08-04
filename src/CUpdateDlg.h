#pragma once
#include "afxdialogex.h"

class CUpdTab1;
class CUpdTab2;
class CUpdTab3;
class CUpdTab4;

// CUpdateDlg 대화 상자

class CUpdateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateDlg)

public:
	CUpdateDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdateDlg();
	CUpdTab1* pDlg1;
	CUpdTab2* pDlg2;
	CUpdTab3* pDlg3;
	CUpdTab4* pDlg4;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl mUpdTab;
	afx_msg void OnTcnSelchangeTabUpdate(NMHDR* pNMHDR, LRESULT* pResult);
};
