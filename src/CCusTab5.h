#pragma once
#include "afxdialogex.h"


// CCusTab5 대화 상자

class CCusTab5 : public CDialogEx
{
	DECLARE_DYNAMIC(CCusTab5)

public:
	CCusTab5(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCusTab5();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CUS_5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
