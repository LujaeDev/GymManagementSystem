// CUpdTab2.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CUpdTab2.h"
#include "DBController.h"


// CUpdTab2 대화 상자

IMPLEMENT_DYNAMIC(CUpdTab2, CDialogEx)

CUpdTab2::CUpdTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPD_2, pParent)
{

}

CUpdTab2::~CUpdTab2()
{
}

void CUpdTab2::showList() {
	DBController dbConroller;


	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT t.trainer_no, t.name, t.phone_number, t.salary, COUNT(pt.trainer_no) AS numberOfStudent "
				"FROM participate AS pt "
				"RIGHT JOIN trainer AS t ON pt.trainer_no = t.trainer_no "
				"GROUP BY t.trainer_no, t.name, t.phone_number, t.salary "
				"ORDER BY numberOfStudent DESC, trainer_no ASC; ");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };

			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);

			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			m_ListCtrl.DeleteAllItems();
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

void CUpdTab2::sqlUpdate() {
	DBController dbController;

	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];
		MessageBox("Update Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "UPDATE t "
				"SET t.salary = t.salary * 1.1 "
				"FROM trainer AS t "
				"JOIN( "
					"SELECT pt.trainer_no, COUNT(*) AS number_of_member "
					"FROM participate AS pt "
					"GROUP BY pt.trainer_no "
					"ORDER BY number_of_member DESC, trainer_no "
					"OFFSET 0 ROWS FETCH FIRST 1 ROWS ONLY "
				") AS sub ON t.trainer_no = sub.trainer_no; ");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbController.db_disconnect();
	}
}

void CUpdTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UPD_2, m_ListCtrl);

	CRect rt;
	int numColumn = 5;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn );
	m_ListCtrl.InsertColumn(3, TEXT("salary"), LVCFMT_LEFT, rt.Width() / (double)numColumn / 1.5);
	m_ListCtrl.InsertColumn(4, TEXT("number_of_member"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.3);

	showList();
}


BEGIN_MESSAGE_MAP(CUpdTab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUpdTab2::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUpdTab2 메시지 처리기


void CUpdTab2::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	sqlUpdate();
	showList();
}
