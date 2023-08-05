// CSelTab5.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelTab5.h"
#include "DBController.h"

// CSelTab5 대화 상자

IMPLEMENT_DYNAMIC(CSelTab5, CDialogEx)

CSelTab5::CSelTab5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEL_5, pParent)
{

}

CSelTab5::~CSelTab5()
{
}

void CSelTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1_SEL_5, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1_SEL_5, m_editProgramName);

	CRect rt;
	int numColumn = 6;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("program_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("program_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.4);
	m_ListCtrl.InsertColumn(2, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("member_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("member_phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(5, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
}


BEGIN_MESSAGE_MAP(CSelTab5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEL_4, &CSelTab5::OnBnClickedButtonSel4)
END_MESSAGE_MAP()


// CSelTab5 메시지 처리기

void CSelTab5::OnBnClickedButtonSel4()
{
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		CString input_programName;
		m_editProgramName.GetWindowTextA(input_programName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		input_programName = "%" + input_programName + "%";

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT DISTINCT p.program_no, p.program_name, m.member_no, m.name, m.phone_number, pt.trainer_no "
				"FROM program AS p "
				"JOIN participate As pt ON p.program_no = pt.program_no "
				"JOIN member m ON pt.member_no = m.member_no "
				"WHERE p.program_name LIKE '%s' "
				"ORDER BY program_no; ", input_programName);

			SQLExecDirect(hStmt, query, SQL_NTS);

			MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			SQLNumResultCols(hStmt, &colCount);

			colCount = 6;
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
