// CSelectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CSelectDlg.h"
#include "CSelTab1.h"
#include "CSelTab2.h"
#include "CSelTab3.h"
#include "CSelTab4.h"
#include "CSelTab5.h"


// CSelectDlg 대화 상자
IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT, pParent)
{
	
}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, mSelTab);

	this->mSelTab.InsertItem(0, _T("Select 1"));
	this->mSelTab.InsertItem(1, _T("Select 2"));
	this->mSelTab.InsertItem(2, _T("Select 3"));
	this->mSelTab.InsertItem(3, _T("Select 4"));
	this->mSelTab.InsertItem(4, _T("Select 5"));

	mSelTab.SetCurSel(0);

	CRect rect;
	mSelTab.GetWindowRect(&rect);

	int moveY = 30;
	pDlg1 = new CSelTab1;
	pDlg1->Create(IDD_DIALOG_SEL_1, &mSelTab);
	pDlg1->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_SHOW);
	
	pDlg2 = new CSelTab2;
	pDlg2->Create(IDD_DIALOG_SEL_2, &mSelTab);
	pDlg2->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CSelTab3;
	pDlg3->Create(IDD_DIALOG_SEL_3, &mSelTab);
	pDlg3->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CSelTab4;
	pDlg4->Create(IDD_DIALOG_SEL_4, &mSelTab);
	pDlg4->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);

	pDlg5 = new CSelTab5;
	pDlg5->Create(IDD_DIALOG_SEL_5, &mSelTab);
	pDlg5->MoveWindow(0, moveY,  rect.Width(), rect.Height());
	pDlg5->ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSelectDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CSelectDlg 메시지 처리기

void CSelectDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int sel = mSelTab.GetCurSel();
	CDialogEx* arrTab[5] = {pDlg1, pDlg2, pDlg3, pDlg4, pDlg5};
	
	for (int i = 0; i < 5; ++i) {
		if (i == sel)
			arrTab[i]->ShowWindow(SW_SHOW);
		else
			arrTab[i]->ShowWindow(SW_HIDE);
	}
}
