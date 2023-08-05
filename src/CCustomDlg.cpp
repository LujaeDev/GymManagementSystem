// CCustomDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GymManagementSystem.h"
#include "afxdialogex.h"
#include "CCustomDlg.h"
#include "CCusTab0.h"
#include "CCusTab1.h"
#include "CCusTab2.h"
#include "CCusTab3.h"
#include "CCusTab4.h"
#include "CusTab5.h"


// CCustomDlg 대화 상자

IMPLEMENT_DYNAMIC(CCustomDlg, CDialogEx)

CCustomDlg::CCustomDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CUSTOM, pParent)
{

}

CCustomDlg::~CCustomDlg()
{
}

void CCustomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, mCusTab);

	this->mCusTab.InsertItem(0, _T("Custom 1"));
	this->mCusTab.InsertItem(1, _T("Custom 2"));
	this->mCusTab.InsertItem(2, _T("Custom 3"));
	this->mCusTab.InsertItem(3, _T("Custom 4"));
	this->mCusTab.InsertItem(4, _T("Custom 5"));
	this->mCusTab.InsertItem(5, _T("Custom 6"));
	

	mCusTab.SetCurSel(0);

	CRect rect;
	mCusTab.GetWindowRect(&rect);

	int moveY = 30;

	pDlg0 = new CCusTab0;
	pDlg0->Create(IDD_DIALOG_CUS_0, &mCusTab);
	pDlg0->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg0->ShowWindow(SW_SHOW);

	pDlg1 = new CCusTab1;
	pDlg1->Create(IDD_DIALOG_CUS_1, &mCusTab);
	pDlg1->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg1->ShowWindow(SW_HIDE);

	pDlg2 = new CCusTab2;
	pDlg2->Create(IDD_DIALOG_CUS_2, &mCusTab);
	pDlg2->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg2->ShowWindow(SW_HIDE);

	pDlg3 = new CCusTab3;
	pDlg3->Create(IDD_DIALOG_CUS_3, &mCusTab);
	pDlg3->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg3->ShowWindow(SW_HIDE);

	pDlg4 = new CCusTab4;
	pDlg4->Create(IDD_DIALOG_CUS_4, &mCusTab);
	pDlg4->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg4->ShowWindow(SW_HIDE);

	pDlg5 = new CusTab5;
	pDlg5->Create(IDD_DIALOG_CUS_5, &mCusTab);
	pDlg5->MoveWindow(0, moveY, rect.Width(), rect.Height());
	pDlg5->ShowWindow(SW_HIDE);
}


BEGIN_MESSAGE_MAP(CCustomDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CCustomDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CCustomDlg 메시지 처리기


void CCustomDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	int sel = mCusTab.GetCurSel();
	CDialogEx* arrTab[6] = { pDlg0, pDlg1, pDlg2, pDlg3, pDlg4, pDlg5};

	for (int i = 0; i < 6; ++i) {
		if (i == sel)
			arrTab[i]->ShowWindow(SW_SHOW);
		else
			arrTab[i]->ShowWindow(SW_HIDE);
	}
}
