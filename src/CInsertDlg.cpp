// CInsertDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CInsertDlg.h"
#include "sql.h"
#include "DBController.h"


// CInsertDlg 대화 상자

IMPLEMENT_DYNAMIC(CInsertDlg, CDialogEx)

CInsertDlg::CInsertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERT, pParent)
{
	//member
	attrName[0][0] = "member_no";
	attrName[0][1] = "name";
	attrName[0][2] = "phone_number";
	attrName[0][3] = "gender";
	attrName[0][4] = "address";
	attrName[0][5] = "payment";
	attrName[0][6] = "recommender";
	cntAttr[0] = 7;

	//trainer
	attrName[1][0] = "trainer_no";
	attrName[1][1] = "name";
	attrName[1][2] = "phone_number";
	attrName[1][3] = "gender";
	attrName[1][4] = "address";
	attrName[1][5] = "salary";
	cntAttr[1] = 6;

	//program
	attrName[2][0] = "program_no";
	attrName[2][1] = "name";
	attrName[2][2] = "type";
	attrName[2][3] = "price";
	attrName[2][4] = "current_\#member";
	attrName[2][5] = "limit_\#member";
	cntAttr[2] = 6;

	//fitness_equipment
	attrName[3][0] = "serial_no";
	attrName[3][1] = "trainer_no";
	attrName[3][2] = "brand";
	attrName[3][3] = "equipment_name";
	cntAttr[3] = 4;

	//product
	attrName[4][0] = "prodcut_no";
	attrName[4][1] = "price";
	attrName[4][2] = "product_name";
	attrName[4][3] = "quantity";
	cntAttr[4] = 4;
}

CInsertDlg::~CInsertDlg()
{
}

void CInsertDlg::setForm(int idx) {
	m_btnQuery.ShowWindow(SW_SHOW);

	for (int i = 0; i < 7; ++i)
		m_ArrAttrValue[i]->SetWindowTextA("");

	for (int i = 0; i < 7; ++i) {
		if (i < cntAttr[idx]) {
			m_ArrAttrName[i]->ShowWindow(SW_SHOW);
			m_ArrAttrValue[i]->ShowWindow(SW_SHOW);
		}
		else {
			m_ArrAttrName[i]->ShowWindow(SW_HIDE);
			m_ArrAttrValue[i]->ShowWindow(SW_HIDE);
		}
	}

	for (int i = 0; i < cntAttr[idx]; ++i) {
		m_ArrAttrName[i]->SetWindowTextA(attrName[idx][i]);
	}
}

void CInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_MEMBER, m_radioMember);
	DDX_Control(pDX, IDC_RADIO_TRAINER, m_radioTrainer);
	DDX_Control(pDX, IDC_RADIO_PROGRAM, m_radioProgram);
	DDX_Control(pDX, IDC_RADIO_FITNESS_EQUIPMENT, m_radioEquipment);
	DDX_Control(pDX, IDC_RADIO_PRODUCT, m_radioProduct);
	DDX_Control(pDX, IDC_STATIC_AT_NAME1, m_staticAttrName1);
	DDX_Control(pDX, IDC_STATIC_AT_NAME2, m_staticAtName2);
	DDX_Control(pDX, IDC_STATIC_AT_NAME3, m_staticAtName3);
	DDX_Control(pDX, IDC_STATIC_AT_NAME4, m_staticAtName4);
	DDX_Control(pDX, IDC_STATIC_AT_NAME5, m_staticAtName5);
	DDX_Control(pDX, IDC_STATIC_AT_NAME6, m_staticAtName6);
	DDX_Control(pDX, IDC_STATIC_AT_NAME7, m_staticAtName7);
	DDX_Control(pDX, IDC_EDIT_AT_1, m_editAttr1);
	DDX_Control(pDX, IDC_EDIT_AT_2, m_editAttr2);
	DDX_Control(pDX, IDC_EDIT_AT_3, m_editAttr3);
	DDX_Control(pDX, IDC_EDIT_AT_4, m_editAttr4);
	DDX_Control(pDX, IDC_EDIT_AT_5, m_editAttr5);
	DDX_Control(pDX, IDC_EDIT_AT_6, m_editAttr6);
	DDX_Control(pDX, IDC_EDIT_AT_7, m_editAttr7);
	DDX_Control(pDX, IDC_BUTTON1, m_btnQuery);

	for (int i = 0; i < 7; ++i) {
		m_ArrAttrName[i]->ShowWindow(SW_HIDE);
		m_ArrAttrValue[i]->ShowWindow(SW_HIDE);
	}

	m_btnQuery.ShowWindow(SW_HIDE);
}

void CInsertDlg::RadioCtrl(UINT id) {
	UpdateData(TRUE);

	switch(id)
	{
	case IDC_RADIO_MEMBER:
		setForm(0);
		break;
	case IDC_RADIO_TRAINER:
		setForm(1);
		break;
	case IDC_RADIO_PROGRAM:
		setForm(2);
		break;
	case IDC_RADIO_FITNESS_EQUIPMENT:
		setForm(3);
		break;
	case IDC_RADIO_PRODUCT:
		setForm(4);
		break;
	}
	
}

BEGIN_MESSAGE_MAP(CInsertDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CInsertDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO_MEMBER, &CInsertDlg::OnBnClickedRadioMember)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO_TRAINER, IDC_RADIO_MEMBER, &CInsertDlg::RadioCtrl)
END_MESSAGE_MAP()



// CInsertDlg 메시지 처리기
void CInsertDlg::OnBnClickedRadioMember()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	if (m_radioMember.GetCheck() == BST_CHECKED) {
		setForm(0);
	} else if (m_radioTrainer.GetCheck() == BST_CHECKED) {
		setForm(1);
	} else if (m_radioProgram.GetCheck() == BST_CHECKED) {
		setForm(2);
	} else if (m_radioEquipment.GetCheck() == BST_CHECKED) {
		setForm(3);
	} else if (m_radioProduct.GetCheck() == BST_CHECKED) {
		setForm(4);
	}
}

void CInsertDlg::insertMember() {
	CString data[10];

	for (int i = 0; i < cntAttr[0]; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}
	for (int i = 0; i < cntAttr[0]; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	for (int i = 0; i < cntAttr[0]; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	data[1] = '\'' + data[1] + '\'';
	data[2] = '\'' + data[2] + '\'';
	data[3] = '\'' + data[3] + '\'';
	data[4] = '\'' + data[4] + '\'';

	for (int i = 0; i < cntAttr[0]; ++i) {
		if (data[i].Compare("'NULL'") == 0)
			data[i] = "NULL";
	}


	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "INSERT INTO member VALUES(%s, %s, %s, %s, %s, %s, %s)",
				data[0], data[1], data[2], data[3], data[4], data[5], data[6]);

			if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR)
			{
				MessageBox("Query Error!\nCheck your Input", "Information", MB_OKCANCEL | MB_ICONERROR);
			}
			else {
				MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}

void CInsertDlg::insertTrainer() {
	CString data[10];

	//cntAttr[] 숫자 테이블마다 다름
	for (int i = 0; i < cntAttr[1]; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}

	for (int i = 0; i < cntAttr[1]; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	data[1] = '\'' + data[1] + '\'';
	data[2] = '\'' + data[2] + '\'';
	data[3] = '\'' + data[3] + '\'';
	data[4] = '\'' + data[4] + '\'';

	for (int i = 0; i < cntAttr[1]; ++i) {
		if (data[i].Compare("'NULL'") == 0)
			data[i] = "NULL";
	}

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "INSERT INTO trainer VALUES(%s, %s, %s, %s, %s, %s)",
				data[0], data[1], data[2], data[3], data[4], data[5]);

			if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR)
			{
				MessageBox("Query Error!\nCheck your Input", "Information", MB_OKCANCEL | MB_ICONERROR);
			}
			else {
				MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}

void CInsertDlg::insertProgram() {
	CString data[30];
	int cnt = cntAttr[2];
	//cntAttr[] 숫자 테이블마다 다름
	for (int i = 0; i < cnt; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}

	for (int i = 0; i < cnt; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	for (int i = 0; i < cnt; ++i) {
		data[i] = '\'' + data[i] + '\'';
	}

	for (int i = 0; i < cntAttr[1]; ++i) {
		if (data[i].Compare("'NULL'") == 0)
			data[i] = "NULL";
	}

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "INSERT INTO program VALUES(%s, %s, %s, %s, %s, %s)",
				data[0], data[1], data[2], data[3], data[4], data[5]);

			if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR)
			{
				MessageBox("Query Error!\nCheck your Input", "Information", MB_OKCANCEL | MB_ICONERROR);
			}
			else {
				MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}
void CInsertDlg::insertFitnessEquipment() {
	CString data[30];
	int cnt = cntAttr[3];
	//cntAttr[] 숫자 테이블마다 다름
	for (int i = 0; i < cnt; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}

	for (int i = 0; i < cnt; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	for (int i = 0; i < cnt; ++i) {
		data[i] = '\'' + data[i] + '\'';
	}

	for (int i = 0; i < cntAttr[1]; ++i) {
		if (data[i].Compare("'NULL'") == 0)
			data[i] = "NULL";
	}

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "INSERT INTO fitness_equipment VALUES(%s, %s, %s, %s, NULL, NULL)",
				data[0], data[1], data[2], data[3]);

			if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR)
			{
				MessageBox("Query Error!\nCheck your Input", "Information", MB_OKCANCEL | MB_ICONERROR);
			}
			else {
				MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}
void CInsertDlg::insertProduct() {
	CString data[30];
	int cnt = cntAttr[4];
	//cntAttr[] 숫자 테이블마다 다름
	for (int i = 0; i < cnt; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}

	for (int i = 0; i < cnt; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	for (int i = 0; i < cnt; ++i) {
		data[i] = '\'' + data[i] + '\'';
	}

	for (int i = 0; i < cntAttr[1]; ++i) {
		if (data[i].Compare("'NULL'") == 0)
			data[i] = "NULL";
	}

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];
		SQLRETURN retCode;

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 201, "INSERT INTO product VALUES(%s, %s, %s, %s)",
				data[0], data[1], data[2], data[3]);

			if (SQLExecDirect(hStmt, query, SQL_NTS) == SQL_ERROR)
			{
				MessageBox("Query Error!\nCheck your Input", "Information", MB_OKCANCEL | MB_ICONERROR);
			}
			else {
				MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}

//Insert button
void CInsertDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_radioMember.GetCheck() == BST_CHECKED) {
		insertMember();
	}
	else if (m_radioTrainer.GetCheck() == BST_CHECKED) {
		insertTrainer();
	}
	else if (m_radioProgram.GetCheck() == BST_CHECKED) {
		insertProgram();
	}
	else if (m_radioEquipment.GetCheck() == BST_CHECKED) {
		insertFitnessEquipment();
	}
	else if (m_radioProduct.GetCheck() == BST_CHECKED) {
		insertProduct();
	}
}



