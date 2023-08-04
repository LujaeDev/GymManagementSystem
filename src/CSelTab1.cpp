// CSelTab1.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelTab1.h"
#include "DBController.h"


// CSelTab1 대화 상자

IMPLEMENT_DYNAMIC(CSelTab1, CDialogEx)

CSelTab1::CSelTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEL_1, pParent)
{
	
}

CSelTab1::~CSelTab1()
{
}

void CSelTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEL_1, m_ListCtrl);

	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("member_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("member_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("cnt_recommended"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
}


BEGIN_MESSAGE_MAP(CSelTab1, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CSelTab1::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSelTab1 메시지 처리기


void CSelTab1::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CSelTab1::OnBnClickedButton1()
{
	DBController dbConroller;
	MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);

	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT member_no, name, phone_number, COUNT(recommender) AS RecommendationCount "
				"FROM member "
				"GROUP BY member_no, Name, phone_number "
				"ORDER BY RecommendationCount DESC, member_no ASC;");
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

			/*SQLBindCol(hStmt, 1, SQL_C_CHAR, member_no, 20, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, name, 20, NULL);
			SQLBindCol(hStmt, 3, SQL_C_CHAR, phone_number, 30, NULL);
			SQLBindCol(hStmt, 4, SQL_C_CHAR, recommendationCount, 30, NULL);*/

			int index = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA)
			{
				m_ListCtrl.InsertItem(index, _T("index"));
				for (int i = 0; i < colCount; ++i)
				{
					if (nullData[i] == SQL_NULL_DATA) m_ListCtrl.SetItem(index, i, LVIF_TEXT, TEXT("NULL"), NULL, NULL, NULL, NULL); ///결과로 ...이 왜 생긱지??
					else m_ListCtrl.SetItem(index, i, LVIF_TEXT, TEXT((const char *)data[i]), NULL, NULL, NULL, NULL);
				}
				index++;
			}

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbConroller.db_disconnect();
	}
}