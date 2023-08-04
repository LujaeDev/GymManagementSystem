#pragma once
#include "afxdialogex.h"


// CSchemaDlg 대화 상자

class CSchemaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSchemaDlg)

public:
	CSchemaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSchemaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCHEMA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlCBox;
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_ListCtrl;
	afx_msg void OnLvnItemchangedListSchema(NMHDR* pNMHDR, LRESULT* pResult);
	void showTableMember();
	void showTableTrainer();
	void showTableProgram();
	void showTableFitnessEquipment();
	void showTableProduct();
	void showTablePurchaseHistory();
	void showTablePersonalLocker();
	void showTableParticipate();
};
