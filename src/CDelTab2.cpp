// CDelTab2.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CDelTab2.h"
#include "DBController.h"
#include "sql.h"

// CDelTab2 대화 상자

IMPLEMENT_DYNAMIC(CDelTab2, CDialogEx)

CDelTab2::CDelTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL_2, pParent)
{

}

CDelTab2::~CDelTab2()
{
}

void CDelTab2::showList() {



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

void CDelTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_MEMBER_NUMBER2, CEditTrainerNo);

	showList();
}


BEGIN_MESSAGE_MAP(CDelTab2, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CDelTab2::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON_DEL2, &CDelTab2::OnBnClickedButtonDel2)
END_MESSAGE_MAP()


// CDelTab2 메시지 처리기


void CDelTab2::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CDelTab2::OnBnClickedButtonDel2()
{
	CString trainer_no;
	CEditTrainerNo.GetWindowTextA(trainer_no);

	DBController dbController;
	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[501];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 501, "DECLARE @P_LOWEST_TRAINER_NO INT, "
				"@P_DELETE_TRAINER_NO INT "
				"SET @P_DELETE_TRAINER_NO = %s "
				"SET @P_LOWEST_TRAINER_NO = (SELECT TOP 1 trainer_NO FROM trainer "
				"WHERE trainer_no <> @P_DELETE_TRAINER_NO "
				"ORDER BY trainer_no); "
				"UPDATE fitness_equipment "
				"SET trainer_no = @P_LOWEST_TRAINER_NO "
				"WHERE trainer_no = @P_DELETE_TRAINER_NO; "
				"UPDATE participate "
				"SET trainer_no = @P_LOWEST_TRAINER_NO "
				"WHERE trainer_no = @P_DELETE_TRAINER_NO; "
				"DELETE FROM trainer WHERE trainer_no = @P_DELETE_TRAINER_NO;", trainer_no);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);

			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Please check trainer_no", "ERROR", MB_YESNO | MB_ICONERROR);
			}
			else {
				MessageBox("Deletion is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			}
			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbController.db_disconnect();
	}
	showList();
}
