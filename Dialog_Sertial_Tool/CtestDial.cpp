// CtestDial.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Dialog_Sertial_Tool.h"
#include "CtestDial.h"
#include "afxdialogex.h"
#include "ntgraph.h"

// CtestDial 대화 상자입니다.

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


// CtestDial 메시지 처리기입니다.


int CtestDial::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}


void CtestDial::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
//}


BOOL CtestDial::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

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
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
