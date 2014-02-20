// MDXMachineChart.cpp : implementation file
//

#include "stdafx.h"

#include "MDXMachineChart.h"
#include"MemDC.h"
#include<math.h>

using namespace CMachineMemDC;
// CMDXMachineChart

IMPLEMENT_DYNAMIC(CMDXMachineChart, CWnd)

CMDXMachineChart::CMDXMachineChart()
{
	Initialize();
}

CMDXMachineChart::~CMDXMachineChart()
{
}


BEGIN_MESSAGE_MAP(CMDXMachineChart, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMDXMachineChart message handlers




int CMDXMachineChart::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
    ModifyStyleEx(0, WS_EX_STATICEDGE);
    ModifyStyle(0, WS_BORDER);

    //
    m_XFont.CreateFont( -16, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("System"));
    //
    m_YFont.CreateFont( -16, 0, 900, 900, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("System"));

    m_ValueFont.CreateFont( -12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Arial"));

	return 0;
}


void CMDXMachineChart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages

	DrawChart(&dc);


}
void CMDXMachineChart::DrawChart(CDC *pDC)
{
    if( pDC == NULL || m_WndRect.IsRectEmpty() )
    {
        return;
    }
    CMachineMemDC::CMemDC MemDC( pDC, &m_WndRect );
    if( m_dcChartBitmap.GetSafeHdc() == NULL && m_ChartBitmap.m_hObject == NULL )
    {
        m_dcChartBitmap.CreateCompatibleDC( pDC );
        m_ChartBitmap.CreateCompatibleBitmap( pDC, m_WndRect.Width(), m_WndRect.Height() );
        m_pOldChartBitmap = m_dcChartBitmap.SelectObject( &m_ChartBitmap );
    }
    MemDC.BitBlt( 0, 0, m_WndRect.Width(), m_WndRect.Height(), &m_dcChartBitmap, 0, 0, SRCCOPY );


    DrawBackground( &MemDC );
	DrawChartBKColor( &MemDC );
    DrawXYCaption( &MemDC );
    DrawValueText( &MemDC );
    DrawProfile( &MemDC );
    DrawGridline( &MemDC );
    DrawFocusNode( &MemDC );


}
void CMDXMachineChart::DrawBackground(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }

	CRect rect;
	this->GetWindowRect( &rect );
	this->ScreenToClient( &rect );

	// 畫整個背景
	pDC->Rectangle( rect );
	// 畫圖的背景
	pDC->Rectangle( m_Rect );



}
void CMDXMachineChart::DrawXYCaption(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }


    CFont fontX, fontY;
    CFont *pOldFont, *pFont = GetParent()->GetFont();
    int iOldMode;
    UINT iOldTextAlign;
    COLORREF crOldClr;

    //
    pOldFont = pDC->SelectObject( pFont );

    iOldTextAlign = pDC->SetTextAlign( TA_CENTER );
    crOldClr = pDC->SetTextColor( RGB(0, 0, 255) );
	//
	iOldMode = pDC->SetGraphicsMode( GM_ADVANCED ); // 2008-06-24


	pDC->SelectObject( &m_XFont );
	pDC->TextOut( (int)(0.5*(m_Rect.left+m_Rect.right)), (m_Rect.bottom+30), m_strXCaption );

	//
	pDC->SelectObject( &m_YFont );
	pDC->TextOut(m_Rect.left-75, (int)(0.5*(m_Rect.top+m_Rect.bottom)), m_strYCaption );


    pDC->SetTextAlign( TA_LEFT );
    pDC->SelectObject( pFont );
    //
    pDC->SelectObject( pOldFont );
    pDC->SetTextAlign( iOldTextAlign );
    pDC->SetGraphicsMode( iOldMode );
    pDC->SetTextColor( crOldClr );
}
void CMDXMachineChart::DrawValueText(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }

    // -1. Value //
    CFont *pOldFont;
    int iOldTextAlign;
    UINT iOldBkMode;

    iOldBkMode = pDC->SetBkMode( TRANSPARENT );
    iOldTextAlign = pDC->SetTextAlign( TA_CENTER );

    pOldFont = pDC->SelectObject( &m_ValueFont );

    double dValue;
//    // X-Axis
    CString strTemp("");

	//畫X軸與畫Y的副座標軸文字

	//畫X軸
	for(int i = 0; i < 10+1; i++)
	{
		// min -> max
        //strTemp.Format( "%6.2f", (m_dXmin + (m_dXmax - m_dXmin)*i*0.1) );
		// max -> min
		dValue = (m_dXmax - (m_dXmax - m_dXmin)*i*0.1)*m_dXFactor;

		if( GetXAxisDrawingMode() == 0 )
		{
			dValue = ((m_dXmax - m_dXmin)*i*0.1)*m_dXFactor;
		}
		else
		{
			dValue = (m_dXmax - (m_dXmax - m_dXmin)*i*0.1)*m_dXFactor;
		}

		if( fabs(dValue) <= 1.0E-6 )
		{
			dValue = 0.;
		}
//        strTemp.Format( "%6.2f", (m_dXmax - (m_dXmax - m_dXmin)*i*0.1)*m_dXFactor );
		//if (IsSolidGasInProject())//2010-02-10
		//{
		//	strTemp.Format( "%6.0f", dValue);
		//}
		//else
		{
			strTemp.Format( _T("%6.2f"), dValue);
		}
			
		//strTemp.Format( "%6.2f", dValue); //2010-02-10

		pDC->TextOut( m_Rect.left+(m_Rect.Width())*i/10 - 4, m_Rect.bottom+5, strTemp);
	}

	//畫Y的座標軸文字
	for(int i = 0; i < 10+1; i++)
	{
		dValue = (m_dYmin + (m_dYmax - m_dYmin)*i*0.1)*m_dYFactor;
		if( fabs(dValue) <= 1.0E-6 )
		{
			dValue = 0.;
		}
//        strTemp.Format( "%6.2f", (m_dYmin + (m_dYmax - m_dYmin)*i*0.1)*m_dYFactor );
	        

		strTemp.Format( _T("%6.2f"), dValue);	
	        
		pDC->TextOut( m_Rect.left - 25, m_Rect.bottom-m_Rect.Height()*i/10-8, strTemp );
	}
	
    //
    pDC->SetBkMode( iOldBkMode );
    pDC->SetTextAlign( iOldTextAlign );
    pDC->SelectObject( pOldFont );
}
void CMDXMachineChart::DrawProfile(CDC *pDC)
{


    switch( m_iProfileType )
    {
    default:
    case 0: DrawStepwiseProfile( pDC ); break;
    case 1: DrawPolylineProfile( pDC ); break;
    }

    if( IsLButtonDown() && HasMatchPoint() )
    {
        switch( m_iProfileType )
        {
        default:
        case 0: DrawDragStepwiseProfile( pDC ); break;
        case 1: DrawDragPolylineProfile( pDC ); break;
        }
    }
}
void CMDXMachineChart::DrawStepwiseProfile(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }


	DrawProifleData( pDC, m_vXData, m_vYData, 0, m_bProfileColor );
	DrawProifleData( pDC, m_vX2Data, m_vY2Data,1,m_bProfile2Color );


}
const int CMDXMachineChart::GetNodeCount(int nItem)
{


	switch( nItem )
	{
	case 0: // 第一組資料
		{
			if( m_vXData.size() != m_vYData.size() )
			{
				return -1;
			}
			 return static_cast<int>(m_vXData.size());
		}
		break;
	case 1:// 第二組資料
		{
			if( m_vX2Data.size() != m_vY2Data.size() )
			{
				return -1;
			}
			return static_cast<int>(m_vX2Data.size());
		}
		break;
	default:
		return 0; break;
	}



   
}
const int CMDXMachineChart::DataToXAxis(const double dx)
{
    if( GetXAxisDrawingMode() == 0 )
    {
        // min -> max
        return ( m_Rect.left + (int)((m_Rect.right - m_Rect.left)*(dx - m_dXmin)/(m_dXmax - m_dXmin)) );
    }
    else
    {
        // max -> min
        return ( m_Rect.left + (int)(m_Rect.Width()*(m_dXmax - dx*m_dXFactor)/(m_dXmax - m_dXmin)) );
    }
}

const int CMDXMachineChart::DataToYAxis(const double dy)
{
//    return ( m_Rect.bottom - (int)((m_Rect.bottom - m_Rect.top)*(dy*m_dYFactor - m_dYmin)/(m_dYmax - m_dYmin)) );
    return ( m_Rect.bottom - (int)(m_Rect.Height()*(dy*m_dYFactor - m_dYmin)/(m_dYmax - m_dYmin)) );
}

const double CMDXMachineChart::XAxisToData(const int x)
{
    if( GetXAxisDrawingMode() == 0 )
    {
        // min -> max
        return ( (m_dXmin + (m_dXmax - m_dXmin)*(x - m_Rect.left)/ (double)m_Rect.Width()) / m_dXFactor );
    }
    else
    {
        // max -> min
        return ( (m_dXmax - (m_dXmax - m_dXmin)*(x - m_Rect.left) / (double)m_Rect.Width()) / m_dXFactor );
    }
}

const double CMDXMachineChart::YAxisToData(const int y)
{
//    return ( m_dYmin + (m_dYmax - m_dYmin)*(m_Rect.bottom - y)/(m_Rect.bottom - m_Rect.top) );
    return ( m_dYmin + (m_dYmax - m_dYmin)*(m_Rect.bottom - y)/(m_Rect.Height() * m_dYFactor) );
}
COLORREF CMDXMachineChart::GetColor(const int iIndex)
{
    COLORREF color;

    // 208-02-18
    switch( iIndex%5 )
    {
    default:
    case 0:    color = RGB(200, 255, 255);    break;    // 淡藍色
    case 1:    color = RGB(232, 255, 232);    break;    // 淡綠色
    case 2:    color = RGB(255, 255, 230);    break;    // 淡黃色
    case 3:    color = RGB(255, 232, 221);    break;    // 淡粉紅色
    case 4:    color = RGB(235, 235, 235);    break;    // 淡灰色
    }


    return color;
}
BOOL CMDXMachineChart::HasMatchPoint()
{
    if( m_iCurrentPoint != -1 && m_bPointMatch == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}
void CMDXMachineChart::DrawDragStepwiseProfile(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }
    if( GetCurrentPoint() < 0 || GetCurrentPoint() >= GetNodeCount() )
    {
        return;
    }

    if( GetCurrentPoint() < 0 || GetCurrentPoint() >= GetNodeCount() )
    {
        return;
    }
    const int iCurPt = GetCurrentPoint();
    int x = DataToXAxis( GetPointXPos() );
    int y = DataToYAxis( GetPointYPos() );

    CPen pen, *pOldPen = NULL;
    int iOldDrawMode;
    //
    pen.CreatePen( PS_SOLID, 1, RGB(255, 0, 0) );
    pOldPen = pDC->SelectObject( &pen );
    //
    iOldDrawMode = pDC->SetROP2( R2_NOTXORPEN ); // set the drawing mode

    POINT lpPt[4];
    //
    if( iCurPt > 0 && iCurPt != GetNodeCount()-1 )
    {
        //
        lpPt[0].x = DataToXAxis( m_vXData[iCurPt+1] );
        lpPt[0].y = DataToYAxis( 0 );
        lpPt[1].x = DataToXAxis( m_vXData[iCurPt+1] );
        lpPt[1].y = y;
        lpPt[2].x = x;
        lpPt[2].y = y;
        lpPt[3].x = x;
        lpPt[3].y = DataToYAxis( 0 );

        // 畫圓圈
        pDC->Ellipse(x-4, y-4, x+4, y+4);
        // 畫方框
        pDC->Polyline( lpPt, 4 );
    }
    else
    if( iCurPt == 0 )
    {
        //
        lpPt[0].x = DataToXAxis( m_vXData[iCurPt+1] );
        lpPt[0].y = DataToYAxis( 0 );
        lpPt[1].x = DataToXAxis( m_vXData[iCurPt+1] );
        lpPt[1].y = y;
        lpPt[2].x = DataToXAxis( m_vXData[0] );
        lpPt[2].y = y;
        lpPt[3].x = DataToXAxis( m_vXData[0] );
        lpPt[3].y = DataToYAxis( 0 );

        // 畫圓圈
        pDC->Ellipse(lpPt[2].x-4, y-4, lpPt[2].x+4, y+4);
        // 畫方框
        pDC->Polyline( lpPt, 4 );
    }

    //
    pDC->SelectObject( pOldPen );
    pDC->SetROP2( iOldDrawMode );
}

void CMDXMachineChart::DrawDragPolylineProfile(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }
    if( GetCurrentPoint() < 0 || GetCurrentPoint() >= GetNodeCount() )
    {
        return;
    }
    const int iCurPt = GetCurrentPoint();

    CPen pen, *pOldPen = NULL;
    int iOldDrawMode;

    pen.CreatePen( PS_SOLID, 1, RGB(255, 0, 0) );
    pOldPen = pDC->SelectObject( &pen );
    //
    iOldDrawMode = pDC->SetROP2( R2_NOTXORPEN ); // set the drawing mode

    int x = DataToXAxis( GetPointXPos() );
    int y = DataToYAxis( GetPointYPos() );

    //
    if( iCurPt != 0 && iCurPt != GetNodeCount()-1 )
    {
        int iFrontPt = iCurPt-1;
        int iRearPt = iCurPt+1;

        // 畫圓圈
        pDC->Ellipse(x-4, y-4, x+4, y+4);
        // 畫線
        pDC->MoveTo( DataToXAxis( m_vXData[iFrontPt] ), DataToYAxis( m_vYData[iFrontPt] ) );
        pDC->LineTo( x, y );
        pDC->LineTo( DataToXAxis( m_vXData[iRearPt] ), DataToYAxis( m_vYData[iRearPt] ) );
    }
    else
    if( iCurPt == 0 )
    {
        x = DataToXAxis( m_vXData[0] );
        // 畫圓圈
        pDC->Ellipse(x-4, y-4, x+4, y+4);
        // 畫線
        pDC->MoveTo( DataToXAxis( m_vXData[0] ), y );
        pDC->LineTo( DataToXAxis( m_vXData[1] ), DataToYAxis( m_vYData[1] ) );
    }
    else // iCurPt == GetNodeCount()-1
    {
        x = DataToXAxis( m_vXData[iCurPt] );
        // 畫圓圈
        pDC->Ellipse(x-4, y-4, x+4, y+4);
        // 畫線
        pDC->MoveTo( DataToXAxis( m_vXData[iCurPt-1] ), DataToYAxis( m_vYData[iCurPt-1] ) );
        pDC->LineTo( DataToXAxis( m_vXData[iCurPt] ), y );
    }

    //
    pDC->SelectObject( pOldPen );
    pDC->SetROP2( iOldDrawMode );
}
void CMDXMachineChart::DrawPolylineProfile(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }


    CPoint point[4];

    if( m_vXData.size() != m_vYData.size() )
    {
        return;
    }

    int x, y;
    for(int i = 0; i < GetNodeCount(); i++)
    {
        x = DataToXAxis( m_vXData[i] );
        y = DataToYAxis( m_vYData[i] );

        //
        if( i < GetNodeCount()-1 )
        {
            CBrush brush, *pOldBrush;

            brush.CreateSolidBrush( GetColor( i ) );

            pOldBrush = pDC->SelectObject( &brush );

            //    0    1    //
            //    3    2    //
            point[0].x = point[3].x = x;            
            point[1].x = point[2].x = DataToXAxis( m_vXData[i+1] );

            point[0].y = y;
            point[1].y = DataToYAxis( m_vYData[i+1] );
            point[2].y = point[3].y = DataToYAxis( 0.0 );

            pDC->Polygon(point, 4);

            pDC->SelectObject( pOldBrush );
        }

        if( i != 0 )
        {
            pDC->LineTo( x, y );
        }
        else
        {
            pDC->MoveTo( x, y );
        }
        //
        CPen pen;
		
		
        pen.CreatePen( PS_SOLID, 1, RGB(255, 0, 0) );

        CPen *pOldPen = pDC->SelectObject( &pen );

        // 畫小圓圈
		
        pDC->Ellipse(x-3, y-3, x+3, y+3);

        pDC->SelectObject( pOldPen );
		
    }
}
void CMDXMachineChart::DrawGridline(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }

    CPen pen;
    pen.CreatePen(PS_SOLID, 1, RGB(192, 192, 192)); // gray
    CPen *pOldPen = pDC->SelectObject(&pen);
    //
    int iOldDrawMode = pDC->SetROP2( R2_NOTXORPEN ); // 2009-04-30 (case 12040)

    for(int i = 2; i <= 10; i++)
    {
        pDC->MoveTo(m_Rect.left, m_Rect.top+(i-1)*m_Rect.Height()/10);     // X 軸的虛線
        pDC->LineTo(m_Rect.right, m_Rect.top+(i-1)*m_Rect.Height()/10);    // X 軸的虛線
        
        pDC->MoveTo(m_Rect.left+(i-1)*m_Rect.Width()/10, m_Rect.top);      // Y 軸的虛線
        pDC->LineTo(m_Rect.left+(i-1)*m_Rect.Width()/10, m_Rect.bottom);   // Y 軸的虛線
    }

    pDC->SelectObject(pOldPen);
    pDC->SetROP2( iOldDrawMode ); // 2009-04-30 (case 12040)
}
void CMDXMachineChart::DrawFocusNode(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }
    if( !HasMatchPoint() )
    {
        return;
    }
    if( m_iCurrentPoint < 0 || m_iCurrentPoint >= GetNodeCount() )
    {
        return;
    }

    //CDC* pDC = GetDC();

    CPen pen;
    pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
    CPen *pOldPen = pDC->SelectObject(&pen);

    int iOffSet = 4;
    int iX = DataToXAxis( m_vXData[m_iCurrentPoint] );
    int iY = DataToYAxis( m_vYData[m_iCurrentPoint] );
    //
	pDC->Ellipse(iX-iOffSet, iY-iOffSet, iX+iOffSet, iY+iOffSet); // 2007-08-07

    pDC->SelectObject(pOldPen);

    //ReleaseDC(pDC);
}
void CMDXMachineChart::AddXYData(const double dx, const double dy, int nItem)
{

	switch( nItem)
	{
	case 0: 
		{
			m_vXData.push_back( dx );
			m_vYData.push_back( dy );
		}
		break;
	case 1:
		{
			m_vX2Data.push_back( dx );
			m_vY2Data.push_back( dy );
		}
		break;
	default:
		break;
	}


}
BOOL CMDXMachineChart::RemoveXYData(const int iIndex)
{
    if( iIndex < 0 || iIndex >= GetNodeCount() )
    {
        return FALSE;
    }

    //
    m_vXData.erase( m_vXData.begin()+iIndex );
    m_vYData.erase( m_vYData.begin()+iIndex );

    return TRUE;
}
void CMDXMachineChart::RemoveAllData()
{
    m_vXData.clear();
    m_vYData.clear();

	m_vXData.clear();
	m_vYData.clear();
}
void CMDXMachineChart::Initialize()
{
	m_bLButtonDown = FALSE;
	m_bPointMatch = FALSE;
	m_bReadOnly = FALSE;

	m_iProfileType = 0;
	m_iCurrentPoint =  -1;
	m_iFinalPoint = -1;
	m_iXDrawingMode = 1;

	m_dXmin = 0.0;
	m_dXmax = 100.0;
	m_dYmin = 0.0;
	m_dYmax = 100.0;

	//second porfile data
	m_dXmin2 = 0.0;
	m_dXmax2 = 100.0;
	m_dYmin2 = 0.0;
	m_dYmax2 = 100.0;

	m_dPointXPos = 0.;
	m_dPointYPos = 0.;
	m_dXFactor = 1.0;
	m_dYFactor = 1.0;
	m_dVPSwitchLoca = 10;

	m_strXCaption = _T("X-Axis");
	m_strYCaption =  _T("Y-Axis");
			
	m_bkColor = RGB(0,0,0);
	m_bProfileColor = RGB(0,0,0);
	m_bProfile2Color = RGB(0,0,0);
}
void CMDXMachineChart::SetXAxisCaption(CString str)
{
    m_strXCaption = str;

    Invalidate( FALSE );
}

void CMDXMachineChart::SetYAxisCaption(CString str)
{
    m_strYCaption = str;

    Invalidate( FALSE );
}
void CMDXMachineChart::SetXMinValue(const double dmin)
{
    m_dXmin = dmin;
}

void CMDXMachineChart::SetXMaxValue(const double dmax)
{
    m_dXmax = dmax;
}
void CMDXMachineChart::SetXMinMaxValue(const double dmin, const double dmax)
{
    m_dXmin = dmin;
    m_dXmax = dmax;
}

void CMDXMachineChart::SetYMinValue(const double dmin)
{
    m_dYmin = dmin;
}

void CMDXMachineChart::SetYMaxValue(const double dmax)
{
    m_dYmax = dmax;
}

void CMDXMachineChart::SetYMinMaxValue(const double dmin, const double dmax)
{
    m_dYmin = dmin;
    m_dYmax = dmax;
}
void CMDXMachineChart::SetX2MinValue(const double dmin)
{
    m_dXmin = dmin;
}

void CMDXMachineChart::SetX2MaxValue(const double dmax)
{
    m_dXmax = dmax;
}
void CMDXMachineChart::SetX2MinMaxValue(const double dmin, const double dmax)
{
    m_dXmin = dmin;
    m_dXmax = dmax;
}

void CMDXMachineChart::SetY2MinValue(const double dmin)
{
    m_dYmin = dmin;
}

void CMDXMachineChart::SetY2MaxValue(const double dmax)
{
    m_dYmax = dmax;
}

void CMDXMachineChart::SetY2MinMaxValue(const double dmin, const double dmax)
{
    m_dYmin = dmin;
    m_dYmax = dmax;
}
BOOL CMDXMachineChart::CreateChart(CRect &rect, CWnd *pParent)
{
    if( rect == CRect(0, 0, 0, 0) || pParent == NULL )
    {
        return FALSE;
    }

    this->Create( NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), pParent, 1 );
    this->SetWindowPos( NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW );

	//把範圍縮小
    m_Rect.left     = rect.left + 80;
    m_Rect.right    = rect.right - 35;
    m_Rect.top      = rect.top + 15;
    m_Rect.bottom   = rect.bottom - 60;

	//machine mode
    //m_Rect.left     = rect.left;// + 80;
    //m_Rect.right    = rect.right; //- 35;
    //m_Rect.top      = rect.top; //+ 15;
    //m_Rect.bottom   = rect.bottom;// - 60;

    m_WndRect = rect; // 2008-10-07

    return TRUE;
} 

void CMDXMachineChart::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( IsReadOnly() )
	{
		return ;
	}

    if( PtInChart( &point ) )
    {
        //
        double dx = XAxisToData( point.x );
        double dy = YAxisToData( point.y );

        // 滑鼠左鍵沒被按下
        if( !IsLButtonDown() )
        {
		    //SetCursor(AfxGetApp()->LoadCursor( IDC_HARROW )); // Set cursor
            //
            SearchMatchPoint( &point );
            DrawChart( GetDC() );
            //if( IsMatchPoint( &point ) )
            //{
            //    //m_bPointMatch = TRUE;

            //    DrawFocusNode();
            //}
            //else
            //{
            //    //m_bPointMatch = FALSE;
            //    //
            //    DrawChart( GetDC() );
            //}
        }
        else // 滑鼠左鍵被按下
        {
            //SetCursor(AfxGetApp()->LoadCursor( IDC_HANDPICK )); // Set cursor

            if( IsCrossPoint( dx, dy ) )
            {
                return;
            }
            //
            m_dPointXPos = dx;
            m_dPointYPos = dy;
            m_iFinalPoint = GetCurrentPoint();

            // draw chart
            DrawChart( GetDC() );

            //if( m_pParentWnd != NULL )
            //{
            //    m_pParentWnd->UpdateProfileData( GetCurrentPoint(), GetPointXPos(), GetPointYPos(), false );
            //    //
            //    m_bUpdateProfile = TRUE;
            //}
        }
        //
        //if( m_bUpdateProfile && !IsLButtonDown() )
        //{
        //    m_pParentWnd->UpdateProfileData( m_iFinalPoint, GetPointXPos(), GetPointYPos(), true );
        //    //
        //    m_bUpdateProfile = FALSE;
        //    m_iFinalPoint = -1;
        //}

        //
        //SetParentTitleText(dx, dy);
    }


	CWnd::OnMouseMove(nFlags, point);
}
BOOL CMDXMachineChart::PtInChart(CPoint *pPt)
{
    if( pPt == NULL )
    {
        return FALSE;
    }

    if( pPt->x >= m_Rect.left && pPt->x <= m_Rect.right &&
        pPt->y >= m_Rect.top  && pPt->y <= m_Rect.bottom )
    {
        return TRUE;
    }

    return FALSE;
}
BOOL CMDXMachineChart::SearchMatchPoint(CPoint *pPt)
{
    if( pPt == NULL || GetNodeCount() <= 0 )
    {
        return FALSE;
    }

    //
    m_iCurrentPoint = -1;
    m_bPointMatch = FALSE;
    //
    for(int i = 0; i < GetNodeCount(); i++)
    {
        if( IsMatchPos( pPt->x, DataToXAxis( m_vXData[i] ) ) &&
            IsMatchPos( pPt->y, DataToYAxis( m_vYData[i] ) ) )
        {
            m_iCurrentPoint = i;
            m_bPointMatch = TRUE;

            return TRUE;
        }
    }

    return FALSE;
}
BOOL CMDXMachineChart::IsMatchPos(const int iPos1, const int iPos2)
{
    // 
    int nPixel = 5;
    if( abs( iPos1-iPos2 ) <= nPixel )
    {
        return TRUE;
    }

    return FALSE;
}
BOOL CMDXMachineChart::IsCrossPoint(const double dx, const double dy)
{
    if( GetCurrentPoint() != 0 && GetCurrentPoint() != GetNodeCount()-1 )
    {
        if( dx >= m_vXData[GetCurrentPoint()-1] || dx <= m_vXData[GetCurrentPoint()+1] )
        {
            return TRUE;
        }
    }

    return FALSE;
}


void CMDXMachineChart::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ( IsReadOnly() )
	{
		return ;
	}

    if( PtInChart( &point ) && HasMatchPoint() )
    {
		//SetCursor(AfxGetApp()->LoadCursor( IDC_HANDPICK )); // Set cursor
    }
    else
    {
        //SetCursor(AfxGetApp()->LoadCursor( IDC_HARROW )); // Set cursor
    }

    if( HasMatchPoint() )
    {
        m_bLButtonDown = TRUE;
    }


	CWnd::OnLButtonDown(nFlags, point);
}


void CMDXMachineChart::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( IsReadOnly() )
	{
		return ;
	}

    //SetCursor(AfxGetApp()->LoadCursor( IDC_HARROW )); // Set cursor
    m_bLButtonDown = FALSE;
    m_bPointMatch = FALSE;
    m_iCurrentPoint = -1;

    //
    InvalidateRect( &m_Rect );

	CWnd::OnLButtonUp(nFlags, point);
}
void CMDXMachineChart::DrawChartBKColor(CDC *pDC)
{
    if( pDC == NULL )
    {
        return;
    }

    CPoint point[4];
	
	CBrush brush, *pOldBrush;

	//將profile 實體化
	brush.CreateSolidBrush( GetColorForBk() );

	pOldBrush = pDC->SelectObject( &brush );

	//    0    1    //
	//    3    2    //
	//point[0].x = point[3].x = DataToXAxis( 100);            
	//point[1].x = point[2].x = DataToXAxis( 0.);

	//point[0].y = DataToYAxis( 100 );
	//point[1].y = DataToYAxis( 100 );
	//point[2].y = point[3].y = DataToYAxis( 0.0 );

	CRect rect;
	//把範圍縮小
    rect.left     = m_Rect.left - 80;
    rect.right    = m_Rect.right + 85;
    rect.top      = m_Rect.top - 15;
    rect.bottom   = m_Rect.bottom + 60;


	point[0].x = point[3].x = rect.left;            
	point[1].x = point[2].x = rect.right;

	point[0].y = rect.top;
	point[1].y = rect.top;
	point[2].y = point[3].y = rect.bottom;

	pDC->Polygon(point, 4);



	pDC->SelectObject( pOldBrush );

	//
	pDC->MoveTo( point[0].x, point[0].y );
	pDC->LineTo( point[1].x, point[1].y );



/////
	//point[0].x = point[3].x = m_Rect.left-80;            
	//point[1].x = point[2].x = m_Rect.right+35;

	//point[0].y = m_Rect.top-15;
	//point[1].y = m_Rect.top-15;
	//point[2].y = point[3].y = m_Rect.bottom+60;

	//pDC->Polygon(point, 4);
	//pDC->SelectObject( pOldBrush );

	//
	CPen pen;
	pen.CreatePen( PS_SOLID, 1, RGB(255, 255, 0) );
			
	CPen *pOldPen = pDC->SelectObject( &pen );
			
	pDC->SelectObject( pOldPen );

}
void CMDXMachineChart::DrawVPSwitchPosition(CDC *pDC)
{
	if ( GetVPSwitchLocation() > 0 )
	{
		CPen pen;
		pen.CreatePen( PS_DOT, 1, RGB(0, 255, 255) );
			
		CPen *pOldPen = pDC->SelectObject( &pen );
			
			//畫小圓圈
		int x1=0, x2=0, y1=0, y2=0;
		x1 = DataToXAxis(GetVPSwitchLocation()+0.24);
		x2 = DataToXAxis(GetVPSwitchLocation()-0.24);
		y1 =  DataToYAxis( m_dYmax/1 /*0.9*/ );//讓她變大 變成1就恢復正常了
		y2 =  DataToYAxis( m_dYmin );
		//pDC->Ellipse(x1, y1, x2, y2);
		pDC->MoveTo(x1, y1);
		pDC->LineTo(x1, y2);
		pDC->SelectObject( pOldPen );
	}
	else
	{
		CPen pen;
		pen.CreatePen( PS_DOT, 1, RGB(0, 255, 255) );
			
		CPen *pOldPen = pDC->SelectObject( &pen );
			
			//畫小圓圈
		int x1=0, x2=0, y1=0, y2=0;
		x1 = DataToXAxis(m_dXmax/0.99);
		x2 = DataToXAxis(m_dXmax/0.99);
		y1 =  DataToYAxis( m_dYmax/0.9 );//讓她變大
		y2 =  DataToYAxis( m_dYmin );
		//pDC->Ellipse(x1, y1, x2, y2);
		pDC->MoveTo(x1, y1);
		pDC->LineTo(x1, y2);
		pDC->SelectObject( pOldPen );
	}
}
void CMDXMachineChart::SetProfileType(int iType)
{
    m_iProfileType = iType;

    Invalidate( FALSE );
}
void CMDXMachineChart::DrawProifleData(CDC* pDC, std::vector<double> vXData, std::vector<double> vYData, int nItem, COLORREF color )
{

   CPoint point[4];

    if( vXData.size() != vYData.size() )
    {
        return;
    }

    int x, y;
    for(int i = 0; i < GetNodeCount(nItem); i++)
    {
		x = DataToXAxis( vXData[i] );
        y = DataToYAxis( vYData[i] );

		if ( i == 0)
		{
			//if( i < GetNodeCount()-1 )
			//{
			//	DrawMaxPressure( pDC);
			//}	
			
		}
				
		if ( i > 0 )
		{
		   if( vYData[i] != vYData[i-1] ||
			   i == 1 )
		   {
				x = DataToXAxis( vXData[i] );
				y = DataToYAxis( vYData[i] );

				if( i < GetNodeCount(nItem)-1 )
				{
					CBrush brush, *pOldBrush;

					//將profile 實體化
					brush.CreateSolidBrush(color );

				   pOldBrush = pDC->SelectObject( &brush );

					//    0    1    //
					//    3    2    //
				
					//else
					//{

						point[0].x = point[3].x = (long) (x+1.5);            
						point[1].x = point[2].x = (long)(x-1.5);//'DataToXAxis( m_vXData[i+1] );
				 
						point[0].y = y;//DataToYAxis( m_vYData[i] );
						point[1].y = y;//DataToYAxis( m_vYData[i] );
						point[2].y = DataToYAxis( vYData[i-1] );
						point[3].y = DataToYAxis( vYData[i-1] );
			
						pDC->Polygon(point, 4);

				   
					
						pDC->MoveTo( point[0].x, point[0].y );
						pDC->LineTo( point[1].x, point[1].y );
					//}
					CPen pen;
					//
					pen.CreatePen( PS_SOLID, 1, RGB(255, 255, 255) );
					
					CPen *pOldPen = pDC->SelectObject( &pen );
			

					pDC->SelectObject( pOldPen );
				  }
			  }
	   }
		
		
		//x = DataToXAxis( m_vXData[i] );
  //      y = DataToYAxis( m_vYData[i] );

        if( i < GetNodeCount(nItem)-1 )
        {
            CBrush brush, *pOldBrush;

			//將profile 實體化
			brush.CreateSolidBrush( color );

           pOldBrush = pDC->SelectObject( &brush );

            //    0    1    //
            //    3    2    //
		   	if( i == 0 )
			{
				point[0].x = point[3].x = DataToXAxis(vXData[i]-0.3);            
				point[1].x = point[2].x = DataToXAxis(vXData[i]+0.3);    
				 
				point[0].y = y;//DataToYAxis( m_vYData[i] );
				point[1].y = y;//DataToYAxis( m_vYData[i] );
				point[2].y = DataToYAxis( 0 );
				point[3].y = DataToYAxis( 0 );
			
				pDC->Polygon(point, 4);
					
				pDC->MoveTo( point[2].x, point[2].y );
				pDC->LineTo( point[1].x, point[1].y );

			}



            point[0].x = point[3].x = x;            
            point[1].x = point[2].x = DataToXAxis( vXData[i+1] );

            point[0].y = y;
            point[1].y = y;//DataToYAxis( m_vYData[i] );
            point[2].y = y+2;
			point[3].y = y+2; //=DataToYAxis( 0.0 );
			
            pDC->Polygon(point, 4);

           // pDC->SelectObject( pOldBrush );

            //
            pDC->MoveTo( point[0].x, point[0].y );
            pDC->LineTo( point[1].x, point[1].y );



        }
    }
}
void CMDXMachineChart::DrawBasicProfile(CDC *pDC, std::vector<double> vXData, std::vector<double> vYData)
{
	/////原來的
    CPoint point[4];
	

    if( vXData.size() != vYData.size() )
    {
        return;
    }

    int x, y;
    for(int i = 0; i < GetNodeCount(); i++)
    {
        x = DataToXAxis( vXData[i] );
        y = DataToYAxis( vYData[i] );

        if( i < GetNodeCount()-1 )
        {
            CBrush brush, *pOldBrush;

			//將profile 實體化
			brush.CreateSolidBrush( GetColor( i ) );

            pOldBrush = pDC->SelectObject( &brush );

            //    0    1    //
            //    3    2    //
            point[0].x = point[3].x = x;            
            point[1].x = point[2].x = DataToXAxis( vXData[i+1] );

            point[0].y = y;
            point[1].y = DataToYAxis( vYData[i] );  //就是Y阿
            point[2].y = point[3].y = DataToYAxis( 0.0 );


            pDC->Polygon(point, 4);

            pDC->SelectObject( pOldBrush );

            //
            pDC->MoveTo( point[0].x, point[0].y );
            pDC->LineTo( point[1].x, point[1].y );

            //
           // CPen pen;
           // pen.CreatePen( PS_SOLID, 1, RGB(255, 0, 0) );

            //CPen *pOldPen = pDC->SelectObject( &pen );

			CBrush brush1, *pOldBrush1;

			brush1.CreateSolidBrush( RGB(255, 0, 0) );

            pOldBrush1 = pDC->SelectObject( &brush1 );

            // 畫小圓圈
            pDC->Ellipse(x-3, y-3, x+3, y+3);

            pDC->SelectObject( pOldBrush1 );
        }
    }
}
void CMDXMachineChart::DrawMaxPressure(CDC *pDC)
{
	CPoint point[4];
	///畫射壓

	CBrush brush, *pOldBrush;

	//將profile 實體化
	brush.CreateSolidBrush( RGB(0,0,255) );

	pOldBrush = pDC->SelectObject( &brush );

	//    0    1    //
	//    3    2    //
	point[0].x = point[3].x = DataToXAxis( m_dXmin );          
	point[1].x = point[2].x = DataToXAxis( m_dXmax/1 /*0.9*/ );  //預留的

	point[0].y = DataToYAxis( m_dYmax );
	point[1].y = DataToYAxis( m_dYmax );
	point[2].y = DataToYAxis( m_dYmax-1 );
	point[3].y = DataToYAxis( m_dYmax-1 );
			
	pDC->Polygon(point, 4);

	// pDC->SelectObject( pOldBrush );

	//
	//if( i == 1 )
	//{
	//	pDC->MoveTo( point[1].x, point[1].y );
	//	pDC->LineTo( point[0].x, point[0].y );
	//}
	pDC->MoveTo( point[0].x, point[0].y );
	pDC->LineTo( point[1].x, point[1].y );       
	///
	DrawVPSwitchPosition(pDC);
		////這是畫VP SWITCH
		//CPen pen;
		//pen.CreatePen( PS_DOT, 1, RGB(0, 255, 255) );
			
		//CPen *pOldPen = pDC->SelectObject( &pen );
			
		// //畫小圓圈
		//int x1=0, x2=0, y1=0, y2=0;
		//x1 = DataToXAxis(m_dXmax/0.99);
		//x2 = DataToXAxis(m_dXmax/0.99);
		//y1 =  DataToYAxis( m_dYmax/0.9 );
		//y2 =  DataToYAxis( m_dYmin );
		////pDC->Ellipse(x1, y1, x2, y2);
		//pDC->MoveTo(x1, y1);
		//pDC->LineTo(x1, y2);
		//pDC->SelectObject( pOldPen );
	
}
