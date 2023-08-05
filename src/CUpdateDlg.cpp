// CUpdateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CUpdateDlg.h"
#include "CUpdTab1.h"
#include "CUpdTab2.h"
#include "CUpdTab3.h"
#include "CUpdTab4.h"



// CUpdateDlg 대화 상자

IMPLEMENT_DYNAMIC(CUpdateDlg, CDialogEx)

CUpdateDlg::CUpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE, pParent)
{
	
}

CUpdateDlg::~CUpdateDlg()
{
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_UPDATE, mUpdTab);

	this->mUpdTab.InsertItem(0, _T("Update 1"));
	this->mUpdTab.InsertItem(1, _T("Update 2"));
	this->mUpdTab.InsertItem(2, _T("Update 3"));
	this->mUpdTab.InsertItem(3, _T("Update 4"));


	mUpdTab.SetCurSel(0);

	CRect rect;
	mUpdTab.GetWindowRect(&rect);

	int moveY = 30;
	pDlg1 = new CUpdTab1;
	pDlg1->Create(IDD_DIALOG_UPD_1, &mUpdTab);
	pDlg1->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CUpdTab2;
	pDlg2->Create(IDD_DIALOG_UPD_2, &mUpdTab);
	pDlg2->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CUpdTab3;
	pDlg3->Create(IDD_DIALOG_UPD_3, &mUpdTab);
	pDlg3->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CUpdTab4;
	pDlg4->Create(IDD_DIALOG_UPD_4, &mUpdTab);
	pDlg4->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(CUpdateDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_UPDATE, &CUpdateDlg::OnTcnSelchangeTabUpdate)
END_MESSAGE_MAP()


// CUpdateDlg 메시지 처리기


void CUpdateDlg::OnTcnSelchangeTabUpdate(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int sel = mUpdTab.GetCurSel();
	CDialogEx* arrTab[4] = { pDlg1, pDlg2, pDlg3, pDlg4 };

	for (int i = 0; i < 4; ++i) {
		if (i == sel)
			arrTab[i]->ShowWindow(SW_SHOW);
		else
			arrTab[i]->ShowWindow(SW_HIDE);
	}
}
