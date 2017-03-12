#pragma once
#include "resource.h"
#include "ntgraphctrl1.h"

// CtestDial ��ȭ �����Դϴ�.

class CtestDial : public CDialogEx
{
	DECLARE_DYNAMIC(CtestDial)

public:
	CtestDial(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CtestDial();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GRAPH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
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
