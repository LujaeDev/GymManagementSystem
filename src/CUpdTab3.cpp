// CUpdTab3.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CUpdTab3.h"
#include "DBController.h"


// CUpdTab3 대화 상자

IMPLEMENT_DYNAMIC(CUpdTab3, CDialogEx)

CUpdTab3::CUpdTab3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPD_3, pParent)
{

}

CUpdTab3::~CUpdTab3()
{
}

void CUpdTab3::showList() {
	DBController dbConroller;


	if (dbConroller.db_connect())
	{
		printf("Connected to %s!\n\n", dbConroller.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[401];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 401, "SELECT ph.product_no, ph.product_name, p.quantity, p.price, sum(ph.price) AS cumculative_sales, ROUND(convert(float, sum(ph.price)) / p.price, 3) AS 'sales_quantity' "
				"FROM purchase_history AS ph "
				"JOIN product AS p ON p.product_no = ph.product_no "
				"GROUP BY ph.product_no, ph.product_name, p.price, p.quantity "
				"ORDER BY convert(float, sum(ph.price)) / p.price, product_no; ");

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

void CUpdTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UPD_3, m_ListCtrl);

	CRect rt;
	int numColumn = 6;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("product_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("product_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("current_quantity"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("price"), LVCFMT_LEFT, rt.Width() / (double)numColumn / 1.5);
	m_ListCtrl.InsertColumn(4, TEXT("cumculative_sales"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.3);
	m_ListCtrl.InsertColumn(5, TEXT("sales_quantity"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.3);

	showList();
}

BEGIN_MESSAGE_MAP(CUpdTab3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPD_3, &CUpdTab3::OnBnClickedButtonUpd3)
END_MESSAGE_MAP()


// CUpdTab3 메시지 처리기


void CUpdTab3::OnBnClickedButtonUpd3()
{
	DBController dbController;

	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "UPDATE product "
				"SET price = ROUND(price * 0.9, -2) "
				"WHERE product_no = (SELECT TOP 1 ph.product_no FROM purchase_history AS ph "
					"JOIN product AS p ON p.product_no = ph.product_no "
					"GROUP BY ph.product_no, ph.product_name, p.price, p.quantity "
					"ORDER BY(convert(float, sum(ph.price)) / p.price), product_no);");
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

			MessageBox("Update Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
		}

		dbController.db_disconnect();
	}

	showList();
}
