// CUpdTab4.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CUpdTab4.h"
#include "DBController.h"

// CUpdTab4 대화 상자

IMPLEMENT_DYNAMIC(CUpdTab4, CDialogEx)

CUpdTab4::CUpdTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPD_4, pParent)
{

}

CUpdTab4::~CUpdTab4()
{
}

void CUpdTab4::showMemberInfo() {
	DBController dbConroller;


	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT m.member_no, m.name, COUNT(*) AS '# of program' "
				"FROM member AS m "
				"JOIN participate As p ON m.member_no = p.member_no "
				"GROUP BY m.member_no, m.name, m.amount_of_payment "
				"ORDER BY COUNT(*) DESC, m.amount_of_payment DESC, member_no; ");

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
					if (nullData[i] == SQL_NULL_DATA) m_ListCtrl.SetItem(index, i, LVIF_TEXT, TEXT("NULL"), NULL, NULL, NULL, NULL);
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

void CUpdTab4::showLockerInfo() {
	DBController dbConroller;


	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT * FROM personal_locker;");

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };


			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);

			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			m_ListCtrl1.DeleteAllItems();
			int index = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				m_ListCtrl1.InsertItem(index, _T("index"));

				for (int i = 0; i < colCount; ++i)
				{
					if (nullData[i] == SQL_NULL_DATA) m_ListCtrl1.SetItem(index, i, LVIF_TEXT, TEXT("NULL"), NULL, NULL, NULL, NULL);
					else m_ListCtrl1.SetItem(index, i, LVIF_TEXT, TEXT((const char*)data[i]), NULL, NULL, NULL, NULL);
				}

				index++;
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}


void CUpdTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1_UPD_4, m_ListCtrl);
	DDX_Control(pDX, IDC_LIST1_LOCKER, m_ListCtrl1);
	DDX_Control(pDX, IDC_EDIT_LOCKER, m_EditLocker);

	CRect rt;
	int numColumn = 3;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("# of program"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	CRect rt1;
	numColumn = 3;

	m_ListCtrl1.GetWindowRect(&rt1);
	m_ListCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl1.InsertColumn(0, TEXT("locker_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl1.InsertColumn(1, TEXT("abnormality"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl1.InsertColumn(2, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	showMemberInfo();
	showLockerInfo();
}


BEGIN_MESSAGE_MAP(CUpdTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPD_4, &CUpdTab4::OnBnClickedButtonUpd4)
END_MESSAGE_MAP()


// CUpdTab4 메시지 처리기

void CUpdTab4::OnBnClickedButtonUpd4()
{
	DBController dbController;
	CString lockerNo;


	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			m_EditLocker.GetWindowText(lockerNo);

			int len = lockerNo.GetLength();
			if (len == 0) {
				MessageBox("Check your Input!", "Error", MB_OKCANCEL | MB_ICONERROR);
				return;
			}

			for (int i = 0; i < len; ++i) {
				if (0 >= lockerNo.GetAt(i) || 127 < lockerNo.GetAt(i)) {
					MessageBox("Check your locker number!", "Error", MB_OKCANCEL | MB_ICONERROR);
					return;
				}

				if (!isdigit(lockerNo[i])) {
					MessageBox("Check your locker number!", "Error", MB_OKCANCEL | MB_ICONERROR);
					return;
				}
			}

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			//해당 멤버가 시스템에 존재하는 지 확인하는 코드
			SQLCHAR querySerialExist[201];

			sprintf_s((char*)querySerialExist, 201, "SELECT locker_no, member_no "
				"FROM personal_locker "
				"WHERE locker_no = %s;", lockerNo);

			SQLExecDirect(hStmt, querySerialExist, SQL_NTS);

			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			int cnt = 0;
			CString ownerMemberNo;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				if (nullData[1] == SQL_NULL_DATA) ownerMemberNo = "NULL";
				else ownerMemberNo = data[1];
				cnt++;
			}
			SQLCloseCursor(hStmt);

			if (cnt == 0) {
				MessageBox("The locker is not exist.\nCheck locker number", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}
			if (ownerMemberNo.Compare("NULL") != 0) {
				MessageBox("The locker is alreay used.\nselect other locker", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			sprintf_s((char*)query, 301, "UPDATE personal_locker "
				"SET member_no = (SELECT TOP 1 m.member_no "
					"FROM member AS m "
					"JOIN participate As p ON m.member_no = p.member_no "
					"GROUP BY m.member_no, m.name, m.amount_of_payment "
					"ORDER BY COUNT(*) DESC, m.amount_of_payment DESC, member_no) "
				"WHERE locker_no = %s; ", lockerNo);

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			MessageBox("Update Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
		}

		dbController.db_disconnect();
	}

	showLockerInfo();
}
