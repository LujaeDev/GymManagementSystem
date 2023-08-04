#pragma once
#include "afxdialogex.h"


// CDelTab4 대화 상자

class CDelTab4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDelTab4)

public:
	CDelTab4(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDelTab4();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEL_4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDelete();
	CListCtrl m_ListCtrl;
	CEdit m_editSerial;
	void showFitnessEquipmentWithAb();
};
