// CusTab5.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CusTab5.h"
#include "DBController.h"


// CusTab5 대화 상자

IMPLEMENT_DYNAMIC(CusTab5, CDialogEx)

CusTab5::CusTab5(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_5, pParent)
{

}

CusTab5::~CusTab5()
{
}

void CusTab5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editAddress);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlCBox);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);

	m_ctrlCBox.AddString(_T("member"));
	m_ctrlCBox.AddString(_T("trainer"));

	m_ctrlCBox.SetCurSel(0);
}


BEGIN_MESSAGE_MAP(CusTab5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CusTab5::OnBnClickedButton1)
END_MESSAGE_MAP()


// CusTab5 메시지 처리기


void CusTab5::OnBnClickedButton1()
{	
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[1001];
		CString table;
		CString address;
		m_editAddress.GetWindowTextA(address);
		m_ctrlCBox.GetWindowTextA(table);

		address = "%" + address + "%";
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 1001, "DECLARE @P_TABLE VARCHAR(10); "
				"SET @P_TABLE = '%s';"
				"IF(@P_TABLE = 'member') "
				"BEGIN "
				"SELECT member_no, name, phone_number, address, amount_of_payment   FROM member "
				"WHERE address like '%s' "
				"ORDER BY amount_of_payment DESC, member_no ASC "
				"END "
				"ELSE IF(@P_TABLE = 'trainer') "
				"BEGIN "
				"SELECT trainer_no, name, phone_number, address, salary FROM trainer "
				"WHERE address like '%s' "
				"ORDER BY salary DESC, trainer_no ASC "
				"END", table, address, address);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);

			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Check your input!", "ERROR", MB_YESNO | MB_ICONERROR);
			}
			else {

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
					double tmp = 1;
					if (i == 0 || i == 1)
						tmp = 1.5;
					else if (i == 3)
						tmp = 0.5;
					m_ListCtrl.InsertColumn(i, TEXT((const char*)columnName[i]), LVCFMT_LEFT, (double)rt.Width() / tmp / (double)numColumn);
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
				MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			}
		}

		dbConroller.db_disconnect();
	}
}
