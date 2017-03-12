// CtestDial.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Dialog_Sertial_Tool.h"
#include "CtestDial.h"
#include "afxdialogex.h"
#include "ntgraph.h"

// CtestDial ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CtestDial, CDialogEx)

CtestDial::CtestDial(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDial::IDD, pParent)
{
	start_flag = 0;
	m_Time = .0f;
}

CtestDial::~CtestDial()
{
}

void CtestDial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_NTGraph);
}


BEGIN_MESSAGE_MAP(CtestDial, CDialogEx)
	ON_WM_CREATE()
	ON_WM_TIMER()
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// CtestDial �޽��� ó�����Դϴ�.


int CtestDial::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	return 0;
}


void CtestDial::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(start_flag)
	{
		m_Time+=0.1;

		m_NTGraph.PlotXY(m_Time, m_data, 0);

		if(m_Time > 5)
		{
			m_NTGraph.SetRange(m_Time -5, m_Time, -1.5, 1.5);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


//void CtestDial::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
//}


BOOL CtestDial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_NTGraph.AddElement();
	m_NTGraph.SetFrameStyle(0);
	m_NTGraph.SetPlotAreaColor(WHITE);
	m_NTGraph.SetShowGrid(TRUE);
	m_NTGraph.SetFormatAxisBottom("%2.f");
	m_NTGraph.SetYGridNumber(10);
	m_NTGraph.SetRange(0, 5, -1.5, 1.5);
	m_NTGraph.SetElementWidth(1);
	m_NTGraph.SetElementLineColor(RED);
	m_NTGraph.SetCaption("(RED)");
	m_NTGraph.SetXLabel("time");
	m_NTGraph.SetYLabel("Amp");

	SetTimer(timer_id, 1, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
