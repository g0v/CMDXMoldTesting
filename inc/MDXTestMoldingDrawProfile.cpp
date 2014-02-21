#include "StdAfx.h"
#include "MDXTestMoldingDrawProfile.h"


CMDXTestMoldingDrawProfile::CMDXTestMoldingDrawProfile(void)
:m_hExists(NULL)
{
	Initialize();
}


CMDXTestMoldingDrawProfile::~CMDXTestMoldingDrawProfile(void)
{
	if (m_hExists != NULL) AfxSetResourceHandle(m_hExists); //handle還回去
}
void CMDXTestMoldingDrawProfile::DrawGridline(CDC *pDC)
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

    for(int i = 2; i <=6 ; i++)
    {
        pDC->MoveTo(m_Rect.left, m_Rect.top+(i-1)*m_Rect.Height()/6);     // X 軸的虛線
        pDC->LineTo(m_Rect.right, m_Rect.top+(i-1)*m_Rect.Height()/6);    // X 軸的虛線
        
        pDC->MoveTo(m_Rect.left+(i-1)*m_Rect.Width()/6, m_Rect.top);      // Y 軸的虛線
        pDC->LineTo(m_Rect.left+(i-1)*m_Rect.Width()/6, m_Rect.bottom);   // Y 軸的虛線
    }

    pDC->SelectObject(pOldPen);
    pDC->SetROP2( iOldDrawMode ); // 2009-04-30 (case 12040)
}
BOOL CMDXTestMoldingDrawProfile::CreateChart(CRect &rect, CWnd *pParent)
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
void CMDXTestMoldingDrawProfile::SetXAxisCaption(CString str)
{
    m_strXCaption = str;

    Invalidate( FALSE );
}

void CMDXTestMoldingDrawProfile::SetYAxisCaption(CString str)
{
    m_strYCaption = str;

    Invalidate( FALSE );
}
void CMDXTestMoldingDrawProfile::AddXYData(const double dx, const double dy, int nItem)
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
bool CMDXTestMoldingDrawProfile::Initialize()
{
	HINSTANCE hRes = NULL;
	m_hExists = AfxGetResourceHandle();

	AfxSetResourceHandle(m_hExists );
	m_bisValid = TRUE;

	return m_bisValid;
}
void CMDXTestMoldingDrawProfile::SetProfileType(int iType)
{
    m_iProfileType = iType;

    Invalidate( FALSE );
}
void CMDXTestMoldingDrawProfile::DrawValueText(CDC *pDC)
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
			strTemp.Format( _T("%6.1f"), dValue);
		}
			
		//strTemp.Format( "%6.2f", dValue); //2010-02-10
		if ( i %2 == 0 )
		{
			pDC->TextOut( m_Rect.left+(m_Rect.Width())*i/10 - 4, m_Rect.bottom+5, strTemp);
		}
		
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
	        

		strTemp.Format( _T("%6.1f"), dValue);	
	     if ( i %2 == 0 )
		 {
			 pDC->TextOut( m_Rect.left - 25, m_Rect.bottom-m_Rect.Height()*i/10-8, strTemp );
		 }
		
	}
	
    //
    pDC->SetBkMode( iOldBkMode );
    pDC->SetTextAlign( iOldTextAlign );
    pDC->SelectObject( pOldFont );
}
void CMDXTestMoldingDrawProfile::RemoveAllData()
{
    m_vXData.clear();
    m_vYData.clear();

	m_vXData.clear();
	m_vYData.clear();
}
void CMDXTestMoldingDrawProfile::SetXMinMaxValue(const double dmin, const double dmax)
{
    m_dXmin = dmin;
    m_dXmax = dmax;
}
void CMDXTestMoldingDrawProfile::SetYMinMaxValue(const double dmin, const double dmax)
{
    m_dYmin = dmin;
    m_dYmax = dmax;
}