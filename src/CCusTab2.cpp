// CCusTab2.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CCusTab2.h"
#include "cctype"
#include "DBController.h"


// CCusTab2 대화 상자

IMPLEMENT_DYNAMIC(CCusTab2, CDialogEx)

CCusTab2::CCusTab2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_2, pParent)
{

}

CCusTab2::~CCusTab2()
{
}

void CCusTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEMBER_NO, m_editMemberNo);
	DDX_Control(pDX, IDC_EDIT_PROGRAM_NO, m_editProgramNo);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_EditSQL);
}


BEGIN_MESSAGE_MAP(CCusTab2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CUS_1_CREATE, &CCusTab2::OnBnClickedButtonCus1Create)
	ON_EN_CHANGE(IDC_EDIT_PROGRAM_NO, &CCusTab2::OnEnChangeEditProgramNo)
	ON_BN_CLICKED(IDC_BUTTON_CUS_EXECUTE, &CCusTab2::OnBnClickedButtonCusExecute)
END_MESSAGE_MAP()


// CCusTab2 메시지 처리기


void CCusTab2::OnBnClickedButtonCus1Create()
{
	m_EditSQL.SetWindowTextA("");

	m_editMemberNo.GetWindowTextA(memberNo);
	m_editProgramNo.GetWindowTextA(programNo);

	if (memberNo.IsEmpty() || programNo.IsEmpty()) {
		MessageBox("Please input number", "ERROR", MB_YESNO | MB_ICONERROR);
		return;
	}

	bool bMemberNoIsNum = true;
	for (int i = 0; i < memberNo.GetLength(); ++i) {
		if (0 >= memberNo[i] || 127 < memberNo[i]) {
			bMemberNoIsNum = false;
			break;
		}
		if (!isdigit(memberNo[i])) {
			bMemberNoIsNum = false;
			break;
		}
	}

	bool bProgramNoIsNum = true;
	for (int i = 0; i < programNo.GetLength(); ++i) {
		if (0 >= programNo[i] || 127 < programNo[i]) {
			bProgramNoIsNum = false;
			break;
		}

		if (!isdigit(programNo[i])) {
			bProgramNoIsNum = false;
			break;
		}
	}

	if (bMemberNoIsNum == false || bProgramNoIsNum == false) {
		MessageBox("Please input number", "ERROR", MB_YESNO | MB_ICONERROR);
		return;
	}

	CString topString = "DECLARE @P_TRAINER_NO INT,\r\n"
		"@P_MEMBER_NO INT,\r\n"
		"@P_PROGRAM_NO INT,\r\n"
		"@P_OVERLAP BIT,\r\n"
		"@P_cur_number INT,\r\n"
		"@P_limit_number INT\r\n";

	CString middleString1 = "SET @P_PROGRAM_NO = " + programNo + ";";
	CString middleString2 = "SET @P_MEMBER_NO = " + memberNo + ";";

	CString bottomString = "SET @P_TRAINER_NO = (SELECT DISTINCT trainer_no FROM participate WHERE program_no = @P_PROGRAM_NO);\r\n"
	"IF EXISTS(\r\n"
		"\tSELECT 1\r\n"
		"\tFROM participate "
		"\tWHERE member_no = @P_MEMBER_NO AND program_No = @P_PROGRAM_NO\r\n"
		")\r\n"
		"BEGIN\r\n"
		"\tSET @P_OVERLAP = 1;\r\n"
	"END\r\n"
		"ELSE\r\n"
		"BEGIN\r\n"
		"\tSET @P_OVERLAP = 0;\r\n"
	"END\r\n"
		"SET @P_cur_number = (SELECT current_number_of_member FROM program WHERE program_no = @P_PROGRAM_NO);\r\n"
	"SET @P_limit_number = (SELECT limit_number_of_member FROM program WHERE program_no = @P_PROGRAM_NO)\r\n"
	"IF(@P_OVERLAP < > 1 AND @P_cur_number < @P_limit_number)\r\n"
		"BEGIN\r\n"
		"\tUPDATE member SET amount_of_payment = amount_of_payment + (SELECT price FROM program WHERE program_no = @P_PROGRAM_NO) WHERE member_no = @P_MEMBER_NO;\r\n"
	"\tUPDATE program SET current_number_of_member = current_number_of_member + 1 WHERE program_no = @P_PROGRAM_NO;\r\n"
	"\tINSERT INTO participate VALUES(@P_MEMBER_NO, @P_TRAINER_NO, @P_PROGRAM_NO);\r\n"
	"END";

	

	CString sql;
	sql = bottomString;
	sql = topString + "\r\n" + middleString1 + "\r\n" + middleString2 + "\r\n" + bottomString;

	m_EditSQL.SetWindowTextA(sql);
}


void CCusTab2::OnEnChangeEditProgramNo()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CCusTab2::OnBnClickedButtonCusExecute()
{
	CString userQuery;
	m_EditSQL.GetWindowTextA(userQuery);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[1101];

		m_editMemberNo.GetWindowTextA(memberNo);
		m_editProgramNo.GetWindowTextA(programNo);

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			if (userQuery.IsEmpty()) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;

			//해당 멤버가 프로그램에 존재하는 지 확인하는 코드
			SQLCHAR queryMemberExist[201];
			sprintf_s((char*)queryMemberExist, 201, "SELECT member_no "
				"FROM member "
				"WHERE member_no = %s;", memberNo);

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

			SQLCHAR queryOverlap[201];
			//이미 프로그램에 들어가 있는지 확인하는 코드
			sprintf_s((char*)queryOverlap, 201, "SELECT member_no "
				"FROM participate "
				"WHERE member_no = %s AND program_No = %s; ", memberNo, programNo);

			SQLExecDirect(hStmt, queryOverlap, SQL_NTS);
			

			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			cnt = 0;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				cnt++;
			}
			SQLCloseCursor(hStmt);


			//이미 들어가 있음!
			if (cnt >= 1) {
				MessageBox("The member is already enrolled in the program.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			// 들어갈 자리가 있는지 확인
			SQLCHAR querySpare[201];

			sprintf_s((char*)querySpare, 201, "SELECT current_number_of_member, limit_number_of_member "
				"FROM program "
				"WHERE program_No = %s; ", programNo);

			SQLExecDirect(hStmt, querySpare, SQL_NTS);
			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			CString currentNum = "-1";
			CString limitNum = "-1";
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				if (nullData[0] == SQL_NULL_DATA) currentNum = "-1000000";
				else currentNum = (const char*)(data[0]);

				if (nullData[1] == SQL_NULL_DATA) limitNum = "1000000";
				else limitNum = (const char*)(data[1]);
			}
			SQLCloseCursor(hStmt);

			int i_currentNum = _ttoi(currentNum);
			int i_limitNum = _ttoi(limitNum);

			//프로그램이 존재하지 않음
			if (i_currentNum == -1 && i_limitNum == -1) {
				MessageBox("The program is not exist.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			if (i_limitNum <= i_currentNum) {
				MessageBox("The program is already full.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}
			//들어갈 자리 확인 끝


			sprintf_s((char*)query, 1101, userQuery);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);


			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO | MB_ICONERROR);
			}
			else {
				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

				MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
			}
		}
		dbConroller.db_disconnect();
	}
}
