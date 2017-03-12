
// Dialog_Sertial_ToolDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Dialog_Sertial_Tool.h"
#include "Dialog_Sertial_ToolDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CDialog_Sertial_ToolDlg ��ȭ ����




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


// CDialog_Sertial_ToolDlg �޽��� ó����

BOOL CDialog_Sertial_ToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Comm.SetHwnd(this->m_hWnd);

	for(int i = 0; i<6; i++)
	{
		m_Graph[i] = new CtestDial();
		m_Graph[i]->Create(IDD_GRAPH, this);
		m_Graph[i]->timer_id = i;
	}
	packet_cnt = 0;
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CDialog_Sertial_ToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CDialog_Sertial_ToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDialog_Sertial_ToolDlg::OnBnClickedCheckOpen()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
//}


void CDialog_Sertial_ToolDlg::OnBnClickedGraph1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
