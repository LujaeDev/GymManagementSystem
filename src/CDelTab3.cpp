// CDelTab3.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CDelTab3.h"
#include "DBController.h"


// CDelTab3 대화 상자

IMPLEMENT_DYNAMIC(CDelTab3, CDialogEx)

CDelTab3::CDelTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DEL_3, pParent)
{

}

CDelTab3::~CDelTab3()
{
}

void CDelTab3::showProduct() {
	DBController dbConroller;

	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT * FROM product;");

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

void CDelTab3::showPurchaseHistory() {
	DBController dbConroller;


	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT DISTINCT product_no, product_name FROM purchase_history");

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


void CDelTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1_DEL_3, m_ListCtrl);
	DDX_Control(pDX, IDC_LIST1_DEL_3_PH, m_ListCtrl1);

	CRect rt;
	int numColumn = 4;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("product_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("price"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("prduct_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("quantity"), LVCFMT_LEFT, rt.Width() / (double)numColumn);

	CRect rt1;
	numColumn = 2;

	m_ListCtrl1.GetWindowRect(&rt1);
	m_ListCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl1.InsertColumn(1, TEXT("product_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn / 1.5);
	m_ListCtrl1.InsertColumn(2, TEXT("prduct_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);

	showProduct();
	showPurchaseHistory();
}


BEGIN_MESSAGE_MAP(CDelTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DEL_3, &CDelTab3::OnBnClickedButtonDel3)
END_MESSAGE_MAP()


// CDelTab3 메시지 처리기


void CDelTab3::OnBnClickedButtonDel3()
{
	DBController dbController;
	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[101];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 101, "DELETE FROM product "
				"WHERE product_no NOT IN( "
					"SELECT DISTINCT product_no "
					"FROM purchase_history); ");

			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		}

		dbController.db_disconnect();
	}
	showProduct();
	showPurchaseHistory();
}
