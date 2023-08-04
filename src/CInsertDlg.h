#pragma once
#include "afxdialogex.h"


// CInsertDlg 대화 상자

class CInsertDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInsertDlg)

public:
	CInsertDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInsertDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_radioMember;
	CButton m_radioTrainer;
	CButton m_radioProgram;
	CButton m_radioEquipment;
	CButton m_radioProduct;
	CStatic m_staticAttrName1;
	CStatic m_staticAtName2;
	CStatic m_staticAtName3;
	CStatic m_staticAtName4;
	CStatic m_staticAtName5;
	CStatic m_staticAtName6;
	CStatic m_staticAtName7;
	CEdit m_editAttr1;
	CEdit m_editAttr2;
	CEdit m_editAttr3;
	CEdit m_editAttr4;
	CEdit m_editAttr5;
	CEdit m_editAttr6;
	CEdit m_editAttr7;
	CStatic* m_ArrAttrName[7] = { &m_staticAttrName1, &m_staticAtName2, &m_staticAtName3, &m_staticAtName4, &m_staticAtName5, &m_staticAtName6, &m_staticAtName7 };
	CEdit* m_ArrAttrValue[7] = { &m_editAttr1, &m_editAttr2, &m_editAttr3, &m_editAttr4, &m_editAttr5, &m_editAttr6, &m_editAttr7 };
	CString attrName[7][7];
	int cntAttr[7] = { 0 };


	/*void setFormMember();
	void setFormTrainer();*/
	
	//index 0 : member, 1 : trainer ...
	void setForm(int idx); //index로 member, trainer 등 구분
	void insertMember();
	void insertTrainer();
	void insertProgram();
	void insertFitnessEquipment();
	void insertProduct();


	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioMember();
	afx_msg void RadioCtrl(UINT id);
	CButton m_btnQuery;
};
