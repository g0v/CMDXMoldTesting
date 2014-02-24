// MDXMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXMaterialPage.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "MDXStringParser.h"
#include "DataCenter.h"

// CMDXMaterialPage dialog

IMPLEMENT_DYNAMIC(CMDXMaterialPage, CDialog)

CMDXMaterialPage::CMDXMaterialPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMDXMaterialPage::IDD, pParent)
, m_iMaterialSel(0)
, m_bCheckEditData(false)
, m_dMaxMeltTemp(0)
, m_dMinMeltTemp(0)
, m_dMaxMoldTemp(0)
, m_dMinMoldTemp(0)
{

}

CMDXMaterialPage::~CMDXMaterialPage()
{
}

void CMDXMaterialPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO_MATERIAL, m_cMaterialType);
	if( m_bCheckEditData )
	{
		IsValidateData( pDX );	
	}
}


BEGIN_MESSAGE_MAP(CMDXMaterialPage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL, &CMDXMaterialPage::OnCbnSelchangeComboMaterialType)
	ON_EN_CHANGE(IDC_EDIT_MELT_TEMPERATURE, &CMDXMaterialPage::OnEnChangeEditMeltTemperature)
END_MESSAGE_MAP()


// CMDXMaterialPage message handlers
BOOL CMDXMaterialPage::OnInitDialog()
{
	InitComboBoxData();
	m_bCheckEditData = true;
	return TRUE;
}

void CMDXMaterialPage::OnCbnSelchangeComboMaterialType()
{
	int iCurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->GetCurSel();
	if( m_iMaterialSel ==  iCurrentSel)
	{
		return ;
	}
	m_iMaterialSel = iCurrentSel;
	SetTemperatureData();
}

void CMDXMaterialPage::InitComboBoxData()
{
	CString strMaterialType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->ResetContent();
	strMaterialType = "PC";
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "PC+ABS";
	/*((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "PC+Fiber";*/
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "PA";
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->SetCurSel(0);
	m_iMaterialSel = 0;
	SetTemperatureData();
}

void CMDXMaterialPage::SetTemperatureData()
{
	switch(m_iMaterialSel)
	{
	case 0://PC
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("300");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("230");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("265"); // (300+230)/2
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("90");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("60");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE)->SetWindowText("75"); // (90+60)/2
		}
		break;
	case 1://PC+ABS
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("270");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("235");
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("90");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("50");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE)->SetWindowText("70");
		}
		break;
	case 2://PA
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("260");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("230");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("245");
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("90");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("50");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE)->SetWindowText("70");
		}
		break;
	}

	UpdateAllData();
}

void CMDXMaterialPage::UpdateAllData()
{
	CString strValue("");
	GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->GetWindowText(strValue);
	SetMaxMeltTemperature(atof(strValue) );
	GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->GetWindowText(strValue);
	SetMinMeltTemperature(atof(strValue) );
	GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->GetWindowText(strValue);
	SetMaxMoldTemperature(atof(strValue) );
	GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->GetWindowText(strValue);
	SetMinMoldTemperature(atof(strValue) );
	GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->GetWindowText(strValue);
	SetMoldTemperature(atof(strValue) );
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE)->GetWindowText(strValue);
	SetMoldTemperature(atof(strValue) );

	//push material selection to data center
	DataCenter::getInstance().SetMaterialSel(m_iMaterialSel);
}

BOOL CMDXMaterialPage::IsValidateData(CDataExchange *pDX)
{

	if( pDX == NULL )
    {
        return false;
    }
	     
    if( !IsMaxMeltTemperature( pDX ) )			{ return FALSE; };
	if( !IsMinMeltTemperature( pDX ) )				{ return FALSE; };
	if( !IsMeltTemperature( pDX ) )				{ return FALSE; };
	if( !IsMaxMoldTemperature( pDX ) )				{ return FALSE; };
	if( !IsMinMoldTemperature( pDX ) )			{ return FALSE; };
	if( !IsMoldTemperature( pDX ) )			{ return FALSE; };


        //
   return TRUE;
   
}

BOOL CMDXMaterialPage::IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue)
{
    CMDXStringParser parser;

    if( !parser.IsRealParse( strValue ) )
    {
        CString strErrorMesg("");
		strErrorMesg = "請輸入數字";
		parser.ShowWarningMessage( pDX, nEditID,  strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );

        return FALSE;
    }

    return TRUE;
}

BOOL CMDXMaterialPage::CheckInputValue( CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue < 0 )
	{
		CString strErrorMesg("");
		strErrorMesg = "此設定值不能小於0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXMaterialPage::CheckMeltMinMax( CDataExchange *pDX, UINT nEditID, double melt, double min, double max )
{
	CMDXStringParser parser;
	if( melt < min || melt > max )
	{
		CString strErrorMesg("");
		strErrorMesg = "[料溫]需在建議上下限之間";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXMaterialPage::CheckMoldMinMax( CDataExchange *pDX, UINT nEditID, double mold, double min, double max )
{
	CMDXStringParser parser;
	if( mold < min || mold > max )
	{
		CString strErrorMesg("");
		strErrorMesg = "[模溫]需在建議上下限之間";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXMaterialPage::IsMaxMeltTemperature( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_MELT_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_MELT_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	SetMaxMeltTemperature(atof(strItem));
	return TRUE;
}

BOOL CMDXMaterialPage::IsMinMeltTemperature( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MIN_MELT_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MIN_MELT_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	SetMinMeltTemperature(atof(strItem));
	return TRUE;
}

BOOL CMDXMaterialPage::IsMeltTemperature( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MELT_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MELT_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckMeltMinMax( pDX, IDC_EDIT_MELT_TEMPERATURE, atof(strItem), 
		GetMinMeltTemperature(), GetMaxMeltTemperature()))
	{
		return FALSE;
	}

	SetMeltTemperature(atof(strItem));
	return TRUE;
}

BOOL CMDXMaterialPage::IsMaxMoldTemperature( CDataExchange *pDX ) 
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_MOLD_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_MOLD_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	SetMaxMoldTemperature(atof(strItem));
	return TRUE;
}

BOOL CMDXMaterialPage::IsMinMoldTemperature( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MIN_MOLD_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MIN_MOLD_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	SetMinMoldTemperature(atof(strItem));
	return TRUE;
}

BOOL CMDXMaterialPage::IsMoldTemperature( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MOLD_TEMPERATURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MOLD_TEMPERATURE, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckMoldMinMax( pDX, IDC_EDIT_MOLD_TEMPERATURE, atof(strItem), 
		GetMinMoldTemperature(), GetMaxMoldTemperature()))
	{
		return FALSE;
	}

	SetMoldTemperature(atof(strItem));
	return TRUE;
}

void CMDXMaterialPage::OnEnChangeEditMeltTemperature()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_MELT_TEMPERATURE )->GetWindowText(strEditData);
	double t = _tstof(strEditData);
	SetMeltTemperature(t);
}
