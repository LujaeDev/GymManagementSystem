// CCusTab4.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CCusTab4.h"
#include "DBController.h"
#include "cctype"

// CCusTab4 대화 상자
IMPLEMENT_DYNAMIC(CCusTab4, CDialogEx)

CCusTab4::CCusTab4(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUS_4, pParent)
{

}

CCusTab4::~CCusTab4()
{
}

void CCusTab4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MEMBER_NO, m_editMemberNo);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_NO, m_editProductNo);
	DDX_Control(pDX, IDC_EDIT_PRODUCT_NO2, m_editQuantity);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_EditSQL);
}


BEGIN_MESSAGE_MAP(CCusTab4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CUS_1_CREATE, &CCusTab4::OnBnClickedButtonCus1Create)
	ON_BN_CLICKED(IDC_BUTTON_CUS_EXECUTE, &CCusTab4::OnBnClickedButtonCusExecute)
END_MESSAGE_MAP()


// CCusTab4 메시지 처리기


void CCusTab4::OnBnClickedButtonCus1Create()
{
	m_EditSQL.SetWindowTextA("");

	m_editMemberNo.GetWindowTextA(memberNo);
	m_editProductNo.GetWindowTextA(productNo);
	m_editQuantity.GetWindowTextA(quantity);

	if (memberNo.IsEmpty() || productNo.IsEmpty() || quantity.IsEmpty()) {
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

	bool bProductNoIsNum = true;
	for (int i = 0; i < productNo.GetLength(); ++i) {
		if (0 >= productNo[i] || 127 < productNo[i]) {
			bProductNoIsNum = false;
			break;
		}

		if (!isdigit(productNo[i])) {
			bProductNoIsNum = false;
			break;
		}
	}

	bool bQuantityIsNum = true;
	for (int i = 0; i < quantity.GetLength(); ++i) {
		if (0 >= quantity[i] || 127 < quantity[i]) {
			bQuantityIsNum = false;
			break;
		}

		if (!isdigit(quantity[i])) {
			bQuantityIsNum = false;
			break;
		}
	}

	int i_quantity = _ttoi(quantity);

	if (bMemberNoIsNum == false || bProductNoIsNum == false || bQuantityIsNum == false) {
		MessageBox("Please input correct number", "ERROR", MB_YESNO | MB_ICONERROR);
		return;
	}

	if (i_quantity < 0) {
		MessageBox("Quantity must be larger than 0", "ERROR", MB_YESNO | MB_ICONERROR);
		return;
	}


	CString topString = "DECLARE @P_PRODUCT_NO INT,\r\n"
		"\t@P_MEMBER_NO INT,\r\n"
		"\t@P_PRODUCT_QUANTITY INT,\r\n"
		"\t@P_PURCHASE_QUANTITY INT,\r\n"
		"\t@P_PRODUCT_NAME VARCHAR(50),\r\n"
		"\t@P_PRODUCT_PRICE INT;\r\n";

	CString middleString1 = "SET @P_MEMBER_NO = " + memberNo + ";";
	CString middleString2 = "SET @P_PRODUCT_NO = " + productNo + ";";
	CString middleString3 = "SET @P_PURCHASE_QUANTITY = " + quantity + ";";


	CString bottomString = "SET @P_PRODUCT_QUANTITY = (SELECT quantity\r\n"
		"\tFROM product\r\n"
		"\tWHERE product_no = @P_PRODUCT_NO)\r\n"
		"IF(@P_PRODUCT_QUANTITY >= @P_PURCHASE_QUANTITY)\r\n"
		"BEGIN\r\n"
		"\tSET @P_PRODUCT_NAME = (SELECT product_name\r\n"
		"\t\t\tFROM product\r\n"
		"\t\t\tWHERE product_no = @P_PRODUCT_NO);\r\n"
		"\tSET @P_PRODUCT_PRICE = (SELECT price\r\n"
		"\t\t\tFROM product\r\n"
		"\t\t\tWHERE product_no = @P_PRODUCT_NO);\r\n"
		"\tIF EXISTS(SELECT 1\r\n"
		"\t\t\tFROM purchase_history\r\n"
		"\t\t\tWHERE member_no = @P_MEMBER_NO AND product_no = @P_PRODUCT_NO)\r\n"
		"\tBEGIN\r\n"
		"\tUPDATE purchase_history\r\n"
		"\tSET price = ph.price + @P_PURCHASE_QUANTITY * p.price\r\n"
		"\tFROM purchase_history AS ph\r\n"
		"\tJOIN product AS p ON ph.product_no = p.product_no\r\n"
		"\tWHERE ph.product_no = @P_PRODUCT_NO;\r\n"
		"\tEND\r\n"
		"\tELSE\r\n"
		"\tBEGIN\r\n"
		"\tINSERT INTO purchase_history VALUES(@P_MEMBER_NO, @P_PRODUCT_NO, @P_PRODUCT_NAME, @P_PRODUCT_PRICE * @P_PURCHASE_QUANTITY)\r\n"
		"\tEND\r\n"
		"\tUPDATE product\r\n"
		"\tSET quantity = @P_PRODUCT_QUANTITY - @P_PURCHASE_QUANTITY\r\n"
		"\tWHERE product_no = @P_PRODUCT_NO\r\n"
		"END";

	CString sql;
	sql = bottomString;
	sql = topString + "\r\n" + middleString1 + "\r\n" + middleString2 +"\r\n"+ middleString3 + "\r\n" + bottomString;

	m_EditSQL.SetWindowTextA(sql);
}


void CCusTab4::OnBnClickedButtonCusExecute()
{
	CString userQuery;
	m_EditSQL.GetWindowTextA(userQuery);

	DBController dbConroller;
	if (dbConroller.db_connect())
	{
		SQLHSTMT hStmt;	// Statement Handle
		SQLCHAR query[1501];


		/*m_editMemberNo.GetWindowTextA(memberNo);
		m_editProductNo.GetWindowTextA(productNo);
		m_editQuantity.GetWindowTextA(quantity);*/

		if (SQLAllocHandle(SQL_HANDLE_STMT, dbConroller.hDbc, &hStmt) == SQL_SUCCESS)
		{
			if (userQuery.IsEmpty()) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			SQLINTEGER nullData[50];
			SQLCHAR data[50][101] = { NULL };
			SQLSMALLINT colCount = -1;

			//해당 멤버가 시스템에 존재하는 지 확인하는 코드
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

			//해당 product가 시스템에 존재하는지 확인하는 코드
			SQLCHAR queryProgductExist[201];
			sprintf_s((char*)queryProgductExist, 201, "SELECT product_no "
				"FROM product "
				"WHERE product_no = %s;", productNo);

			SQLExecDirect(hStmt, queryProgductExist, SQL_NTS);
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

			if (cnt == 0) {
				MessageBox("The product is not exist.", "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}

			SQLCHAR queryQuantity[201];
			//해당 제품의 재고량을 확인하는 코드
			sprintf_s((char*)queryQuantity, 201, "SELECT quantity "
				"FROM product "
				"WHERE product_no = %s", productNo);

			SQLExecDirect(hStmt, queryQuantity, SQL_NTS);


			SQLNumResultCols(hStmt, &colCount);
			for (int i = 0; i < colCount; ++i)
			{
				SQLBindCol(hStmt, i + 1, SQL_C_CHAR, data[i], sizeof(data[i]), (SQLLEN*)&nullData[i]);
			}

			cnt = 0;
			CString currentProductQuantity;
			int i_currentProductQuantity;
			while (SQLFetch(hStmt) != SQL_NO_DATA) {
				cnt++;
				currentProductQuantity = data[0];
			}
			SQLCloseCursor(hStmt);
			int i_purchaseQuantity = _ttoi(quantity);
			i_currentProductQuantity = _ttoi(currentProductQuantity);

			//수량이 부족함!
			if (i_currentProductQuantity < i_purchaseQuantity) {
				MessageBox("Quantity of the product is short\nrequest quantity must be less than or equal " + currentProductQuantity, "ERROR", MB_YESNO | MB_ICONERROR);
				return;
			}



			SQLSetConnectAttr(dbConroller.hDbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, NULL);
			sprintf_s((char*)query, 1501, userQuery);
			int retCode = SQLExecDirect(hStmt, query, SQL_NTS);


			if (retCode == SQL_ERROR || retCode == SQL_NO_DATA_FOUND) {
				MessageBox("Check your query statement!", "ERROR", MB_YESNO | MB_ICONERROR);
				SQLEndTran(SQL_HANDLE_DBC, dbConroller.hDbc, SQL_ROLLBACK);
			}
			else {
				SQLCloseCursor(hStmt);
				SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

				MessageBox("your query is completed!", "INFORMATION", MB_YESNO | MB_ICONINFORMATION);
				SQLEndTran(SQL_HANDLE_DBC, dbConroller.hDbc, SQL_COMMIT);
			}
		}
		dbConroller.db_disconnect();
	}
}
