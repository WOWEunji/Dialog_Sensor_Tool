
// Dialog_Sertial_ToolDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "CtestDial.h"

class SENSORPACKET{
public:
	SENSORPACKET()
	{
		start[0] = start[1] = 0xff;
		x = y = 0;
	}
	BYTE start[2];
	short x;
	short y;
};

// CDialog_Sertial_ToolDlg 대화 상자
class CDialog_Sertial_ToolDlg : public CDialogEx
{
// 생성입니다.
public:
	CDialog_Sertial_ToolDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_SERTIAL_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CComm m_Comm;
	int m_ComPort;
	int m_ComRate;
	CButton m_BtnCommOpen;
	afx_msg void OnBnClickedCheckOpen();
	CtestDial *m_Graph[6];

protected:
	afx_msg LRESULT OnReceivedata(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedGraph1();
	CButton m_checkG1;
	afx_msg void OnBnClickedGraph2();
	CButton m_checkG2;
	CButton m_checkG3;
	CButton m_checkG4;
	CButton m_checkG5;
	CButton m_checkG6;
	afx_msg void OnBnClickedGraph3();
	afx_msg void OnBnClickedGraph4();
	afx_msg void OnBnClickedGraph6();
	afx_msg void OnBnClickedGraph5();
	int packet_cnt;
	SENSORPACKET *m_Packet;
	float m_x;
	float m_y;
	float graph_data[6];
};

