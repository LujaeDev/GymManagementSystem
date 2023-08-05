// CSelTab3.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelTab3.h"
#include "DBController.h"


// CSelTab3 대화 상자

IMPLEMENT_DYNAMIC(CSelTab3, CDialogEx)

CSelTab3::CSelTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEL_3, pParent)
{

}

CSelTab3::~CSelTab3()
{
}

void CSelTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEL_3, m_ListCtrl);
	CRect rt;
	int numColumn = 6;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.2);
	m_ListCtrl.InsertColumn(3, TEXT("equipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(4, TEXT("abnormality_content"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 2);
	m_ListCtrl.InsertColumn(5, TEXT("abnormality_occur_date"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
}


BEGIN_MESSAGE_MAP(CSelTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEL_3, &CSelTab3::OnBnClickedButtonSel3)
END_MESSAGE_MAP()


// CSelTab3 메시지 처리기
void CSelTab3::OnBnClickedButtonSel3()
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
			sprintf_s((char*)query, 301, "SELECT * FROM fitness_equipment WHERE abnormality_content is NOT NULL;");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101];

			MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);

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
