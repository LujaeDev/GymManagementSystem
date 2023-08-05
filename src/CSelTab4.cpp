// CSelTab4.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelTab4.h"
#include "DBController.h"


// CSelTab4 대화 상자

IMPLEMENT_DYNAMIC(CSelTab4, CDialogEx)

CSelTab4::CSelTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEL_4, pParent)
{

}

CSelTab4::~CSelTab4()
{
}

void CSelTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SEL_4, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT_PROGRAM, m_editBrand);

	CRect rt;
	int numColumn = 6;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("equipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("trainer_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(5, TEXT("phone_number"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
}


BEGIN_MESSAGE_MAP(CSelTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEL_4, &CSelTab4::OnBnClickedButtonSel4)
END_MESSAGE_MAP()


// CSelTab4 메시지 처리기
void CSelTab4::OnBnClickedButtonSel4()
{
	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		CString input_brandName;
		m_editBrand.GetWindowTextA(input_brandName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		input_brandName = "%" + input_brandName + "%";

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT fe.serial_no, fe.brand, fe.equipment_name, t.trainer_no, t.name, t.phone_number "
				"FROM fitness_equipment AS fe "
				"JOIN trainer AS t ON fe.trainer_no = t.trainer_no "
				"WHERE fe.brand LIKE '%s'", input_brandName);

			SQLExecDirect(hStmt, query, SQL_NTS);

			MessageBox("Query Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
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