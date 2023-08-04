// CDelDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CDelDlg.h"
#include "CDelTab1.h"
#include "CDelTab2.h"
#include "CDelTab3.h"
#include "CDelTab4.h"


// CDelDlg 대화 상자

IMPLEMENT_DYNAMIC(CDelDlg, CDialogEx)

CDelDlg::CDelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE, pParent)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_DEL, mDelTab);

	this->mDelTab.InsertItem(0, _T("Delete 1"));
	this->mDelTab.InsertItem(1, _T("Delete 2"));
	this->mDelTab.InsertItem(2, _T("Delete 3"));
	this->mDelTab.InsertItem(3, _T("Delete 4"));

	mDelTab.SetCurSel(0);

	CRect rect;
	mDelTab.GetWindowRect(&rect);

	int moveY = 30;
	pDlg1 = new CDelTab1;
	pDlg1->Create(IDD_DIALOG_DEL_1, &mDelTab);
	pDlg1->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);

	pDlg2 = new CDelTab2;
	pDlg2->Create(IDD_DIALOG_DEL_2, &mDelTab);
	pDlg2->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CDelTab3;
	pDlg3->Create(IDD_DIALOG_DEL_3, &mDelTab);
	pDlg3->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CDelTab4;
	pDlg4->Create(IDD_DIALOG_DEL_4, &mDelTab);
	pDlg4->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(CDelDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DEL, &CDelDlg::OnTcnSelchangeTabDel)
END_MESSAGE_MAP()


// CDelDlg 메시지 처리기


void CDelDlg::OnTcnSelchangeTabDel(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int sel = mDelTab.GetCurSel();
	CDialogEx* arrTab[4] = { pDlg1, pDlg2, pDlg3, pDlg4};

	for (int i = 0; i < 4; ++i) {
		if (i == sel)
			arrTab[i]->ShowWindow(SW_SHOW);
		else
			arrTab[i]->ShowWindow(SW_HIDE);
	}
}
