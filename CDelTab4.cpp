// CDelTab4.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CDelTab4.h"
#include "DBController.h"


// CDelTab4 대화 상자

IMPLEMENT_DYNAMIC(CDelTab4, CDialogEx)

CDelTab4::CDelTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL_4, pParent)
{

}

CDelTab4::~CDelTab4()
{
}
void CDelTab4::showFitnessEquipmentWithAb() {
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT serial_no, brand, equipment_name, abnormality_content, abnormality_occur_date, t.trainer_no, t.name "
				"FROM fitness_equipment AS fe "
				"JOIN trainer AS t ON fe.trainer_no = t.trainer_no "
				"WHERE fe.abnormality_content is NOT NULL; ");

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);

			colCount = 7;
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			int index = 0;

			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				m_ListCtrl.InsertItem(index, _T("index"));

				for (int i = 0; i < colCount; ++i)
				{
					if (nullData[i] == SQL_NULL_DATA) m_ListCtrl.SetItem(index, i, LVIF_TEXT, TEXT("NULL"), NULL, NULL, NULL, NULL); ///결과로 ...이 왜 생긱지??
					else m_ListCtrl.SetItem(index, i, LVIF_TEXT, TEXT((const char*)data[i]), NULL, NULL, NULL, NULL);
				}

				index++;
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}

void CDelTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEL_4, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_SERIAL_NO, m_editSerial);


	CRect rt;
	int numColumn = 7;
	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("equipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("abnormality"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("abnormality_date"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(5, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(6, TEXT("trainer_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	showFitnessEquipmentWithAb();
}


BEGIN_MESSAGE_MAP(CDelTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDelTab4::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDelTab4 메시지 처리기


void CDelTab4::OnBnClickedButtonDelete()
{
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];
		SQLCHAR queryCheck1[401];
		SQLCHAR queryCheck2[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			CString serialNo;
			m_editSerial.GetWindowTextA(serialNo);

			sprintf_s((char*)queryCheck1, 401, "SELECT * "
				"FROM fitness_equipment "
				"WHERE serial_no = %s; ", serialNo);
			int retCode = SQLExecDirect(hStmt, queryCheck1, SQL_NTS);

			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND)
			{
				MessageBox("The serial number is not exist", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			int cnt = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				cnt++;
			}
			SQLCloseCursor(hStmt);

			if (cnt == 0) {
				MessageBox("The serial number is not exist.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			SQLCloseCursor(hStmt);

			sprintf_s((char*)queryCheck2, 401, "SELECT * "
				"FROM fitness_equipment "
				"WHERE abnormality_content is NOT NULL AND serial_no = %s; ", serialNo);
			retCode = SQLExecDirect(hStmt, queryCheck2, SQL_NTS);

			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			cnt = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				cnt++;
			}
			SQLCloseCursor(hStmt);

			if (cnt == 0)
			{
				MessageBox("a product has the serial number has no abnormality!", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}
			SQLCloseCursor(hStmt);


			sprintf_s((char*)query, 401, "DELETE fitness_equipment "
				"WHERE serial_no in(SELECT serial_no "
				"FROM fitness_equipment "
				"WHERE abnormality_content IS NOT NULL) AND serial_no = %s; ", serialNo);

			MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			retCode = SQLExecDirect(hStmt, query, SQL_NTS);

	
			SQLNumResultCols(hStmt, &colCount);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}

	showFitnessEquipmentWithAb();
}
