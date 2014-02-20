#include "StdAfx.h"
#include "MDXStringParser.h"
#include "CMDXMoldTesting.h"
//

CMDXStringParser::CMDXStringParser(void)
{
}

CMDXStringParser::~CMDXStringParser(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CMDXStringParser::IsRealParse(const char* lpszText)
{
    double dTemp = 0.;
    if( !SimpleFloatParse( lpszText, dTemp ) )
    {
        return false;
    }

    return true;
}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool CMDXStringParser::SimpleFloatParse(const char* lpszText, double &dValue)
{
    // 這段 code 來自 DLGFLOAT.cpp
//    ASSERT(lpszText != NULL);
    if( lpszText == NULL )
    {
        return false;
    }

    while (*lpszText == ' ' || *lpszText == '\t')
        lpszText++;

    TCHAR chFirst = lpszText[0];
    dValue = _tcstod(lpszText, (LPTSTR*)&lpszText);
    if (dValue == 0.0 && chFirst != '0')
        return false;   // could not convert
    while (*lpszText == ' ' || *lpszText == '\t')
        lpszText++;

    if (*lpszText != '\0')
        return false;   // not terminated properly

    return true;
}

CString CMDXStringParser::GetTableString(UINT iStringID)
{
    CString str("");
    str.LoadString( iStringID );

    return str;
};

void CMDXStringParser::ShowWarningMessage(CDataExchange *pDX, UINT nEditID, CString strMsg)
{
    if( pDX == NULL )
    {
        return;
    }
	CMDXStringParser parser;

    HWND hWnd = pDX->PrepareEditCtrl( nEditID );
    
	::AfxMessageBox(strMsg);

    if( pDX != NULL )
    {
        //
        pDX->Fail();
    }
}
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
