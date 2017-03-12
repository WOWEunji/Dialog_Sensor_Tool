#pragma once
#include "resource.h"
#include "ntgraphctrl1.h"

// CtestDial 대화 상자입니다.

class CtestDial : public CDialogEx
{
	DECLARE_DYNAMIC(CtestDial)

public:
	CtestDial(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CtestDial();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()

public:
	bool start_flag;
	int timer_id;
	float m_Time;
	float m_data;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CNtgraphctrl1 m_NTGraph;
//	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
