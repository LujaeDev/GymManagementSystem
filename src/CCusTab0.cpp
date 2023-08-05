// CCusTab0.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CCusTab0.h"
#include "DBController.h"

// CCusTab0 대화 상자

IMPLEMENT_DYNAMIC(CCusTab0, CDialogEx)

CCusTab0::CCusTab0(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_0, pParent)
{

}

CCusTab0::~CCusTab0()
{
}

void CCusTab0::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CUS_0, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_editQuery);
}


BEGIN_MESSAGE_MAP(CCusTab0, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CUS_0, &CCusTab0::OnLvnItemchangedListCus0)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &CCusTab0::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// CCusTab0 메시지 처리기


void CCusTab0::OnLvnItemchangedListCus0(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void CCusTab0::OnBnClickedButtonQuery()
{
	CString userQuery;
	m_editQuery.GetWindowTextA(userQuery);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, userQuery);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);

			if (userQuery.IsEmpty() || retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO|MB_ICONERROR);
			}
			else {

				CString command = userQuery.Left(6);

				if (command.CompareNoCase("SELECT") == 0) {
					SQLINTEGER nullData[50];
					SQLCHAR data[50][201] = { NULL };
					SQLCHAR columnName[50][31];
					SQLSMALLINT columnNameLen[50];
					SQLSMALLINT columnDataType[50];
					SQLULEN columnDataSize[50];
					SQLSMALLINT columnDataDecimalDigits[50];
					SQLSMALLINT columnDataNullable[50];

					m_ListCtrl.DeleteAllItems();

					SQLSMALLINT colCount = -1;
					SQLNumResultCols(hStmt, &colCount);

					for (int i = 0; i < colCount; ++i) {
						SQLDescribeCol(hStmt, i + 1, columnName[i], 30, &columnNameLen[i], &columnDataType[i],
							&columnDataSize[i], &columnDataDecimalDigits[i], &columnDataNullable[i]);
					}

					/*< 리스트 컨트롤 헤더 인스턴스의 포인터 */
					CHeaderCtrl* pHeaderCtrl;      

					pHeaderCtrl = m_ListCtrl.GetHeaderCtrl();
					int columnNumber = pHeaderCtrl->GetItemCount();

					m_ListCtrl.DeleteAllItems();
					for (int i = 0; i < columnNumber; ++i)
						m_ListCtrl.DeleteColumn(0);


					CRect rt;
					int numColumn = colCount;

					m_ListCtrl.GetWindowRect(&rt);
					m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

					for (int i = 0; i < numColumn; ++i) {
						m_ListCtrl.InsertColumn(i, TEXT((const char*)columnName[i]), LVCFMT_LEFT, rt.Width() / (double)numColumn);
					}

					for (int i = 0; i < numColumn; ++i)
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
				MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			}
		}

		dbConroller.db_disconnect();
	}

}
