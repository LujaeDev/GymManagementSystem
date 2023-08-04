// CDelTab1.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CDelTab1.h"
#include "DBController.h"
#include "sql.h"


// CDelTab1 대화 상자

IMPLEMENT_DYNAMIC(CDelTab1, CDialogEx)

CDelTab1::CDelTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL_4, pParent)
{

}

CDelTab1::~CDelTab1()
{
}

void CDelTab1::showList() {
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
			SQLCHAR data[50][101] = { NULL };

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

void CDelTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEL_1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_MEMBER_NUMBER, CEditMemberNo);
	showList();
}


BEGIN_MESSAGE_MAP(CDelTab1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL1, &CDelTab1::OnBnClickedButtonDel1)
END_MESSAGE_MAP()


// CDelTab1 메시지 처리기
void CDelTab1::OnBnClickedButtonDel1()
{
	CString member_no;
	CEditMemberNo.GetWindowTextA(member_no);

	DBController dbController;
	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{

			sprintf_s((char*)query, 201, "UPDATE member "
				"SET recommender = NULL "
				"WHERE recommender = %s; "
				"DELETE FROM member WHERE member_no = %s;" , member_no, member_no);

			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);
			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Please check member_no", "ERROR", MB_YESNO | MB_ICONERROR);
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
