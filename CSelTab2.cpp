// CSelTab2.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelTab2.h"
#include "DBController.h"
#include "ctype.h"


// CSelTab2 대화 상자

IMPLEMENT_DYNAMIC(CSelTab2, CDialogEx)

CSelTab2::CSelTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEL_2, pParent)
{

}

CSelTab2::~CSelTab2()
{
}

void CSelTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEL_2, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_SEL_2, CEditMemberNo);

	CRect rt;
	int numColumn = 5;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("member_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("program_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("program_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
}


BEGIN_MESSAGE_MAP(CSelTab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEL_2, &CSelTab2::OnBnClickedButtonSel2)
END_MESSAGE_MAP()


// CSelTab2 메시지 처리기


void CSelTab2::OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CSelTab2::OnBnClickedButtonSel2()
{
	DBController dbConroller;
	

	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			CString member_no;
			CEditMemberNo.GetWindowText(member_no);

			int len = member_no.GetLength();
			if (len == 0) {
				MessageBox("Check your Input!", "Error", MB_OKCANCEL | MB_ICONERROR);
				return;
			}

			for (int i = 0; i < len; ++i) {
				if (0 >= member_no.GetAt(i) || 127 < member_no.GetAt(i)) {
					MessageBox("Check your Input!", "Error", MB_OKCANCEL | MB_ICONERROR);
					return;
				}

				if (!isdigit(member_no.GetAt(i))) {
					MessageBox("Check your Input!", "Error", MB_OKCANCEL | MB_ICONERROR);
					return;
				}
			}



			//해당 멤버가 시스템에 존재하는 지 확인하는 코드
			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			SQLCHAR queryMemberExist[201];
			sprintf_s((char*)queryMemberExist, 201, "SELECT member_no "
				"FROM member "
				"WHERE member_no = %s;", member_no);

			SQLExecDirect(hStmt, queryMemberExist, SQL_NTS);

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
				MessageBox("The member is not exist.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			// member_no 예외처리 필요
			sprintf_s((char*)query, 301, "SELECT m.member_no, m.name, p.program_no, p.program_name, pt.trainer_no "
				"FROM member AS m "
				"JOIN participate AS pt ON m.member_no = pt.member_no "
				"JOIN program AS p ON pt.program_no = p.program_no "
				"WHERE m.member_no = % s; ", member_no);
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCHAR member_name[20];
			SQLCHAR program_name[20];
			SQLCHAR program_no[20];
			SQLCHAR trainer_no[30];
			SQLCHAR trainer_name[30];

			MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
			SQLBindCol(hStmt, 1, SQL_C_CHAR, member_name, 20, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, program_no, 20, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, program_name, 20, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, trainer_no, 30, NULL);
			SQLBindCol(hStmt, 5, SQL_C_CHAR, trainer_name, 30, NULL);

			int index = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				m_ListCtrl.InsertItem(index, _T("index"));
				m_ListCtrl.SetItem(index, 0, LVIF_TEXT, TEXT((const char*)member_name), NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(index, 1, LVIF_TEXT, TEXT((const char*)program_no), NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(index, 2, LVIF_TEXT, TEXT((const char*)program_name), NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(index, 3, LVIF_TEXT, TEXT((const char*)trainer_no), NULL, NULL, NULL, NULL);
				m_ListCtrl.SetItem(index, 4, LVIF_TEXT, TEXT((const char*)trainer_name), NULL, NULL, NULL, NULL);

				index++;
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}
