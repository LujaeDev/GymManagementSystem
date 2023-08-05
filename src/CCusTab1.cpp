// CCusTab1.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CCusTab1.h"
#include "DBController.h"
#include "DBController.h"


// CCusTab1 대화 상자

IMPLEMENT_DYNAMIC(CCusTab1, CDialogEx)

CCusTab1::CCusTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_1, pParent)
{

}

CCusTab1::~CCusTab1()
{
}

void CCusTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROGRAM, m_editProgramName);
	DDX_Control(pDX, IDC_EDIT2_POGRAM_NO, m_EditProgeamNo);
	DDX_Control(pDX, IDC_EDIT_AT_1, m_editAttr1);
	DDX_Control(pDX, IDC_EDIT_AT_2, m_editAttr2);
	DDX_Control(pDX, IDC_EDIT_AT_3, m_editAttr3);
	DDX_Control(pDX, IDC_EDIT_AT_4, m_editAttr4);
	DDX_Control(pDX, IDC_EDIT_AT_5, m_editAttr5);
	DDX_Control(pDX, IDC_EDIT1, m_EditSQL);
}


BEGIN_MESSAGE_MAP(CCusTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CUS_1_CREATE, &CCusTab1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1_LOAD, &CCusTab1::OnBnClickedButton1Load)
	ON_BN_CLICKED(IDC_BUTTON_CUS_2, &CCusTab1::OnBnClickedButtonCus2Execute)
END_MESSAGE_MAP()


// CCusTab1 메시지 처리기

void CCusTab1::OnBnClickedButton1Load()
{
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];
		CString program_no;
		m_EditProgeamNo.GetWindowTextA(program_no);
		if (program_no.IsEmpty()) {
			MessageBox("Check program_no", "Information", MB_YESNO | MB_ICONERROR);

			for (int i = 0; i < 5; ++i)
				m_ArrAttrValue[i]->SetWindowTextA("");
			return;

		}

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			for (int i = 0; i < program_no.GetLength(); ++i) {
				if (0 >= program_no[i] || 127 < program_no[i]){
					MessageBox("Check program_no", "ERROR", MB_YESNO | MB_ICONERROR);
					return;
				}

				if (!isdigit(program_no[i])) {
					MessageBox("Check program_no", "ERROR", MB_YESNO | MB_ICONERROR);
					return;
				}
			}

			sprintf_s((char*)query, 301, "SELECT program_name, program_type, price, current_number_of_member, limit_number_of_member "
				"FROM program "
				"WHERE program_no = %s; ", program_no);

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101];


			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
			
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			int index = 0;

			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{

				for (int i = 0; i < colCount; ++i)
				{
					if (nullData[i] == SQL_NULL_DATA){
						m_ArrAttrValue[i]->SetWindowTextA("NULL");
					}
					else {
						m_ArrAttrValue[i]->SetWindowTextA((const char*)data[i]);
					}
				}

				index++;
			}

			if (index == 0) {
				MessageBox("The program is not exist", "Information", MB_YESNO | MB_ICONERROR);

				for (int i = 0; i < 5; ++i)
					m_ArrAttrValue[i]->SetWindowTextA("");
					return;
			}
			else {
				MessageBox("Data load Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}
void CCusTab1::OnBnClickedButton1()
{
	m_EditSQL.SetWindowTextA("");
	CString attributeName[5] = { "program_name", "program_type", "price", "current_number_of_member", "limit_number_of_member" };
	CString data[5];
	for (int i = 0; i < 5; ++i) {
		m_ArrAttrValue[i]->GetWindowTextA(data[i]);
	}

	for (int i = 0; i < 5; ++i) {
		if (data[i].IsEmpty())
			data[i] = "NULL";
	}

	CString sql = "UPDATE program";
	
	for (int i = 0; i < 5; ++i) {
		if (data[i].Compare("NULL") != 0 && i < 2) {
			data[i] = "'" + data[i] + "'";
		}
	}

	boolean first = true;
	sql += "\r\nSET " + attributeName[0] + " = " + data[0];
	for (int i = 1; i < 5; ++i) {
		CString line = "\r\n," + attributeName[i] + " = " + data[i];
		sql += line;
	}

	CString program_no;
	m_EditProgeamNo.GetWindowTextA(program_no);
	sql += "\r\nWHERE program_no = " + program_no;

	m_EditSQL.SetWindowTextA(sql);
}

void CCusTab1::OnBnClickedButtonCus2Execute()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString userQuery;
	m_EditSQL.GetWindowTextA(userQuery);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, userQuery);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);

			if (userQuery.IsEmpty() || retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO | MB_ICONERROR);
			}
			else {
				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
				
				MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			}
		}
		dbConroller.db_disconnect();
	}

}
