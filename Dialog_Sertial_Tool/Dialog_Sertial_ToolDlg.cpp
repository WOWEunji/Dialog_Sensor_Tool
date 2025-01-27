
// Dialog_Sertial_ToolDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Dialog_Sertial_Tool.h"
#include "Dialog_Sertial_ToolDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialog_Sertial_ToolDlg 대화 상자




CDialog_Sertial_ToolDlg::CDialog_Sertial_ToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Sertial_ToolDlg::IDD, pParent)
	, m_ComPort(0)
	, m_ComRate(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDialog_Sertial_ToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COM, m_ComPort);
	DDX_Text(pDX, IDC_EDIT_BAUD, m_ComRate);
	DDX_Control(pDX, IDC_CHECK_OPEN, m_BtnCommOpen);
	DDX_Control(pDX, IDC_GRAPH1, m_checkG1);
	DDX_Control(pDX, IDC_GRAPH2, m_checkG2);
	DDX_Control(pDX, IDC_GRAPH3, m_checkG3);
	DDX_Control(pDX, IDC_GRAPH4, m_checkG4);
	DDX_Control(pDX, IDC_GRAPH6, m_checkG5);
	DDX_Control(pDX, IDC_GRAPH5, m_checkG6);
}

BEGIN_MESSAGE_MAP(CDialog_Sertial_ToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_OPEN, &CDialog_Sertial_ToolDlg::OnBnClickedCheckOpen)
	ON_MESSAGE(WM_RECEIVEDATA, &CDialog_Sertial_ToolDlg::OnReceivedata)
	ON_BN_CLICKED(IDC_GRAPH1, &CDialog_Sertial_ToolDlg::OnBnClickedGraph1)
	ON_BN_CLICKED(IDC_GRAPH2, &CDialog_Sertial_ToolDlg::OnBnClickedGraph2)
	ON_BN_CLICKED(IDC_GRAPH3, &CDialog_Sertial_ToolDlg::OnBnClickedGraph3)
	ON_BN_CLICKED(IDC_GRAPH4, &CDialog_Sertial_ToolDlg::OnBnClickedGraph4)
	ON_BN_CLICKED(IDC_GRAPH6, &CDialog_Sertial_ToolDlg::OnBnClickedGraph6)
	ON_BN_CLICKED(IDC_GRAPH5, &CDialog_Sertial_ToolDlg::OnBnClickedGraph5)
END_MESSAGE_MAP()


// CDialog_Sertial_ToolDlg 메시지 처리기

BOOL CDialog_Sertial_ToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Comm.SetHwnd(this->m_hWnd);

	for(int i = 0; i<6; i++)
	{
		m_Graph[i] = new CtestDial();
		m_Graph[i]->Create(IDD_GRAPH, this);
		m_Graph[i]->timer_id = i;
	}
	packet_cnt = 0;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDialog_Sertial_ToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDialog_Sertial_ToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDialog_Sertial_ToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialog_Sertial_ToolDlg::OnBnClickedCheckOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	bool graph_flag;
	BOOL bCheck = m_BtnCommOpen.GetCheck();

	if(bCheck)
	{
		TTYSTRUCT tty;
		tty.byByteSize = _nDataValues[1];
		tty.byCommPort = m_ComPort;
		tty.byFlowCtrl = 0;
		tty.byParity = FALSE;
		tty.byStopBits = _nStopBits[0];
		tty.byXonXoff = 0;
		tty.dwBaudRate = m_ComRate;

		if(m_Comm.OpenCommPort(&tty))
		{
			m_BtnCommOpen.SetWindowText("Close");
			graph_flag = TRUE;
		}
		else
		{
			AfxMessageBox("Can't Open Com Port!");
			m_BtnCommOpen.SetCheck(FALSE);
			graph_flag = FALSE;
		}
	}
	else
	{
		m_Comm.CloseConnection();
		m_BtnCommOpen.SetWindowText("OPEN");
		graph_flag = FALSE;
	}

	for(int i = 0; i<6; i++)
	{
		m_Graph[i]->start_flag = graph_flag;
	}

	UpdateData(FALSE);
}


afx_msg LRESULT CDialog_Sertial_ToolDlg::OnReceivedata(WPARAM wParam, LPARAM lParam)
{
	BYTE m_packet_buffer[4];
	int data_size = wParam;

	for(register int i = 0; i<data_size; i++)
	{
		m_packet_buffer[packet_cnt] = m_Comm.abIn[i];
		packet_cnt ++;
		if(packet_cnt>1)
		{
			if((m_packet_buffer[0] == 0xff) && (m_packet_buffer[1] = 0xff))
			{
				if(packet_cnt>4)
				{
					m_Packet = (SENSORPACKET*)m_packet_buffer;
					m_x = m_Packet->x;
					m_y = m_Packet->y;

					packet_cnt = 0;
				}
			}
		}
		else if(packet_cnt>0 && m_packet_buffer[0] == 0xff)
		{
			if(packet_cnt > 1 && m_packet_buffer[1]!=0xff)
			{
				packet_cnt=m_packet_buffer[0] = m_packet_buffer[1] = 0;
			}
			else if(packet_cnt > 1 && m_packet_buffer[1] == 0xff)
			{
				if(packet_cnt > 4)
				{
					m_Packet = (SENSORPACKET*)m_packet_buffer;
					m_x = m_Packet->x;
					m_y = m_Packet->y;
					packet_cnt = 0;
				}
				packet_cnt = 0;
			}
		}
		else
		{
			packet_cnt = m_packet_buffer[0] = m_packet_buffer[1] = 0;
		}
	}
	return 0;
}


//void CAboutDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
//}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_checkG1.GetCheck();
	if(bCheck)
	{
		m_Graph[0]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[0]->ShowWindow(SW_HIDE);
	}
	m_Graph[0]->SetWindowText("IMU-Position-X");
	m_Graph[0]->m_NTGraph.SetCaption("IMU-Position-X");
}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_checkG2.GetCheck();
	if(bCheck)
	{
		m_Graph[1]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[1]->ShowWindow(SW_HIDE);
	}
	m_Graph[1]->SetWindowText("IMU-Position-Y");
	m_Graph[1]->m_NTGraph.SetCaption("IMU-Position-Y");
}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_checkG3.GetCheck();
	if(bCheck)
	{
		m_Graph[2]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[2]->ShowWindow(SW_HIDE);
	}
	m_Graph[2]->SetWindowText("IMU-Rotation-X");
	m_Graph[2]->m_NTGraph.SetCaption("IMU-Rotation-X");
}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		BOOL bCheck = m_checkG4.GetCheck();
	if(bCheck)
	{
		m_Graph[3]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[3]->ShowWindow(SW_HIDE);
	}
	m_Graph[3]->SetWindowText("IMU-Rotation-Y");
	m_Graph[3]->m_NTGraph.SetCaption("IMU-Rotation-Y");
}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_checkG5.GetCheck();
	if(bCheck)
	{
		m_Graph[4]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[4]->ShowWindow(SW_HIDE);
	}
	m_Graph[4]->SetWindowText("MPU-Rotation-X");
	m_Graph[4]->m_NTGraph.SetCaption("MPU-Rotation-X");
}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bCheck = m_checkG6.GetCheck();
	if(bCheck)
	{
		m_Graph[5]->ShowWindow(SW_SHOW);
	}
	else
	{
		m_Graph[5]->ShowWindow(SW_HIDE);
	}
	m_Graph[5]->SetWindowText("MPU-Rotation-Y");
	m_Graph[5]->m_NTGraph.SetCaption("MPU-Rotation-Y");
}
