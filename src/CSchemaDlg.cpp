// CSchemaDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSchemaDlg.h"
#include "DBController.h"


// CSchemaDlg 대화 상자

IMPLEMENT_DYNAMIC(CSchemaDlg, CDialogEx)

CSchemaDlg::CSchemaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCHEMA, pParent)
{

}

CSchemaDlg::~CSchemaDlg()
{
}

//사용 안 함
void CSchemaDlg::showTableMember() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 6;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(3, TEXT("gender"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("address"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 3);
	m_ListCtrl.InsertColumn(5, TEXT("amount_of_payment"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(6, TEXT("recommender"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM member;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = {NULL};

			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';


			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTableTrainer() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(3, TEXT("gender"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("address"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 3);
	m_ListCtrl.InsertColumn(5, TEXT("salary"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM trainer;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTableProgram() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("program_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("program_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.7);
	m_ListCtrl.InsertColumn(2, TEXT("program_type"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("price"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("current_number_of_member"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.3);
	m_ListCtrl.InsertColumn(5, TEXT("limit_number_of_member"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.3);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM program;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTableFitnessEquipment() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 5;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("eqipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("abnormality_content"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(5, TEXT("abnormality_occur_date"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.7);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM fitness_equipment;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTableProduct() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("product_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("price"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("product_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("quantity"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	
	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM product;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTablePurchaseHistory() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("product_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("product_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("price"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM purchase_history;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTablePersonalLocker() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 3;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("locker_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("abnormality_content"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	
	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM personal_locker;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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
void CSchemaDlg::showTableParticipate() {

	//이전 기록 삭제
	CHeaderCtrl* pHeaderCtrl;       /*< 리스트 컨트롤 헤더 인스턴스의 포인터 */

	pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
	int columnNumber = pHeaderCtrl->GetItemCount();

	m_ListCtrl.DeleteAllItems();
	for (int i = 0; i < columnNumber; ++i)
		m_ListCtrl.DeleteColumn(0);


	CRect rt;
	int numColumn = 3;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("program_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM participate;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			// ... 생기는 거 해결하려고 해봤는데 효과 없음
			for (int i = 0; i < 50; ++i)
				for (int j = 0; j < 101; ++j)
					data[i][j] = '\0';

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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

void CSchemaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCHEMA, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCBox);

	m_ctrlCBox.AddString(_T("member"));
	m_ctrlCBox.AddString(_T("trainer"));
	m_ctrlCBox.AddString(_T("program"));
	m_ctrlCBox.AddString(_T("fitness_equipment"));
	m_ctrlCBox.AddString(_T("product"));
	m_ctrlCBox.AddString(_T("purchase_history"));
	m_ctrlCBox.AddString(_T("personal_locker"));
	m_ctrlCBox.AddString(_T("participate"));

	m_ctrlCBox.SetCurSel(0);


	CRect rt;
	int numColumn = 5;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("Column_Name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("Column_Name_len"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("Data_Type"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("Data_Size"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("Data_Nullable"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
}

BEGIN_MESSAGE_MAP(CSchemaDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSchemaDlg::OnCbnSelchangeCombo1)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SCHEMA, &CSchemaDlg::OnLvnItemchangedListSchema)
END_MESSAGE_MAP()


// CSchemaDlg 메시지 처리기



void CSchemaDlg::OnCbnSelchangeCombo1()
{
	CString selectedTable;
	m_ctrlCBox.GetWindowTextA(selectedTable);

	//// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//int curSel = m_ctrlCBox.GetCurSel();

	//if (curSel >= 0 && curSel < 8) {
	//	if (curSel == 0) showTableMember();
	//	else if (curSel == 1) showTableTrainer();
	//	else if (curSel == 2) showTableProgram();
	//	else if (curSel == 3) showTableFitnessEquipment();
	//	else if (curSel == 4) showTableProduct();
	//	else if (curSel == 5) showTablePurchaseHistory();
	//	else if (curSel == 6) showTablePersonalLocker();
	//	else if (curSel == 7) showTableParticipate();
	//}


	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		m_ListCtrl.DeleteAllItems();


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT Column_Name, len(COLUMN_NAME) AS Column_Name_len, Data_Type, CHARACTER_MAXIMUM_LENGTH AS Data_Size, IS_NULLABLE As Data_Nullable "
				"FROM INFORMATION_SCHEMA.COLUMNS "
				"WHERE TABLE_NAME = '%s'", selectedTable);
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);
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


void CSchemaDlg::OnLvnItemchangedListSchema(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
