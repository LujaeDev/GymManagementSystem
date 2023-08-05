// CUpdTab1.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CUpdTab1.h"
#include "DBController.h"


// CUpdTab1 대화 상자

IMPLEMENT_DYNAMIC(CUpdTab1, CDialogEx)

CUpdTab1::CUpdTab1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPD_1, pParent)
{

}

CUpdTab1::~CUpdTab1()
{
}

void CUpdTab1::showTableFitnessEquipment() {

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

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(2, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("eqipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("abnormality_content"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(5, TEXT("abnormality_occur_date"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.7);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{


		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[301];

		m_ListCtrl.DeleteAllItems();
		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			sprintf_s((char*)query, 301, "SELECT * FROM fitness_equipment;");
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


void CUpdTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UPD_1, m_ListCtrl);

	/*CRect rt;
	int numColumn = 5;

	m_ListCtrl.GetWindowRect(&rt);
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_ListCtrl.InsertColumn(0, TEXT("serial_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn / 1.5);
	m_ListCtrl.InsertColumn(1, TEXT("trainer_no"), LVCFMT_LEFT, rt.Width() / (double)numColumn / 1.5);
	m_ListCtrl.InsertColumn(2, TEXT("brand"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(3, TEXT("equipment_name"), LVCFMT_LEFT, rt.Width() / (double)numColumn);
	m_ListCtrl.InsertColumn(4, TEXT("abnormality_content"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.5);
	m_ListCtrl.InsertColumn(5, TEXT("abnormality_occur_date"), LVCFMT_LEFT, rt.Width() / (double)numColumn * 1.7);*/
	showTableFitnessEquipment();
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dateTime);
	DDX_Control(pDX, IDC_EDIT_SERIAL, m_editSerial);
	DDX_Control(pDX, IDC_EDIT_CONTENT, m_editContent);
}


BEGIN_MESSAGE_MAP(CUpdTab1, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, &CUpdTab1::OnDtnDatetimechangeDatetimepicker2)
	ON_BN_CLICKED(IDC_BUTTON_UPD1, &CUpdTab1::OnBnClickedButtonUpd1)
END_MESSAGE_MAP()


// CUpdTab1 메시지 처리기


void CUpdTab1::OnDtnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CUpdTab1::OnBnClickedButtonUpd1()
{
	DBController dbController;

	CString serial;
	m_editSerial.GetWindowTextA(serial);

	CString content;
	m_editContent.GetWindowTextA(content);

	CTime sel_date;
	m_dateTime.GetTime(sel_date);
	
	CString strYear;
	CString strMonth;
	CString strDay;
	CString strDateFormat;

	strYear.Format(_T("%d"), sel_date.GetYear());
	strMonth.Format(_T("%d"), sel_date.GetMonth());
	strDay.Format(_T("%d"), sel_date.GetDay());
	strDateFormat = strYear + _T("-") + strMonth + _T("-") + strDay;

	if (serial.IsEmpty()) {
		MessageBox("Please enter serial_no.", "ERROR", MB_YESNO | MB_ICONERROR);
		return;
	}

	for (int i = 0; i < serial.GetLength(); ++i) {
		if (0 >= serial.GetAt(i) || 127 < serial.GetAt(i) || !isdigit(serial.GetAt(i))) {
			MessageBox("Check your serial!", "Error", MB_OKCANCEL | MB_ICONERROR);
			return;
		}
	}

	if (content.IsEmpty())
		content = "NULL";

	serial = '\'' + serial + '\'';
	content = '\'' + content + '\'';
	strDateFormat = '\'' + strDateFormat + '\'';

	if (content.Compare("'NULL'") == 0)
		content = "NULL";

	if (dbController.db_connect())
	{
		printf("Connected to %s!\n\n", dbController.dataSourceName);

		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[201];

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbController.hDbc, &hStmt) == SQL_SUCCESS)
		{
			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;
			//해당 멤버가 시스템에 존재하는 지 확인하는 코드
			SQLCHAR querySerialExist[201];

			sprintf_s((char*)querySerialExist, 201, "SELECT serial_no "
				"FROM fitness_equipment "
				"WHERE serial_no = %s;", serial);

			SQLExecDirect(hStmt, querySerialExist, SQL_NTS);

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
				MessageBox("The equipment is not exist.\nCheck serial number", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			sprintf_s((char*)query, 201, "UPDATE fitness_equipment SET abnormality_content = %s, abnormality_occur_date = %s WHERE serial_no = %s;", content, strDateFormat, serial);
			SQLExecDirect(hStmt, query, SQL_NTS);

			SQLCloseCursor(hStmt);
			SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
			MessageBox("Update Completed!", "Information", MB_OKCANCEL | MB_ICONINFORMATION);
		}

		dbController.db_disconnect();
	}


	showTableFitnessEquipment();
}
