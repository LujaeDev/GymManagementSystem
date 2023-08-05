#pragma once
#include "afxdialogex.h"


// CUpdTab1 대화 상자

class CUpdTab1 : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdTab1)

public:
	CUpdTab1(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CUpdTab1();
	void showTableFitnessEquipment();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPD_1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	afx_msg void OnDtnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult);
	CDateTimeCtrl m_dateTime;
	afx_msg void OnBnClickedButtonUpd1();
	CEdit m_editSerial;
	CEdit m_editContent;
};
