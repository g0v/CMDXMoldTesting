// MDXMachinePage.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXMachinePage.h"
#include "afxdialogex.h"
#include "MDXStringParser.h"
#include "DataCenter.h"

// CMDXMachinePage dialog

IMPLEMENT_DYNAMIC(CMDXMachinePage, CDialog)

CMDXMachinePage::CMDXMachinePage(CWnd* pParent /*=NULL*/)
	: CDialog(CMDXMachinePage::IDD, pParent)
, m_iMachineSel(0)
, m_bCheckEditData(false)
, m_dClampingForce(0.)
, m_dScrewDiam(0.)
, m_dMaxStroke(0.)
, m_dInjectionVolume(0.)
, m_dMaxInjectionVolume(0.)
, m_dMaxInjectionVelocity(0.)
, m_dMaxInjectionPressure(0.)
, m_pParent(pParent)
{

}

CMDXMachinePage::~CMDXMachinePage()
{
}

void CMDXMachinePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if( m_bCheckEditData )
	{
		IsValidateData( pDX );	
	}
}


BEGIN_MESSAGE_MAP(CMDXMachinePage, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_PRODUCTER, &CMDXMachinePage::OnCbnSelchangeComboMachineProducer)
	ON_CBN_SELCHANGE(IDC_COMBO_GRADE, &CMDXMachinePage::OnCbnSelchangeComboMachineGrade)
END_MESSAGE_MAP()


// CMDXMachinePage message handlers
BOOL CMDXMachinePage::OnInitDialog()
{
	InitComboMachineProducer();
	InitComboMachineGrade();
	m_bCheckEditData = false;
	return TRUE;
}

void CMDXMachinePage::InitComboMachineProducer()
{
	CString strMachineType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_PRODUCTER))->ResetContent();
	strMachineType = "FSC";
	((CComboBox*)GetDlgItem(IDC_COMBO_PRODUCTER))->AddString(strMachineType); 
	strMachineType = "CLF Machinery";
	((CComboBox*)GetDlgItem(IDC_COMBO_PRODUCTER))->AddString(strMachineType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_PRODUCTER))->SetCurSel(0);
	m_iMachineSel = 0;
	SetMachineData();
}

void CMDXMachinePage::InitComboMachineGrade()
{
	switch(m_iMachineSel)
	{
	case 0://FSC
		{
			CString strMachineType("");
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->ResetContent();
			strMachineType = "AF-250-40";
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->AddString(strMachineType); 
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(0);
		}
		break;
	case 1://CLF
		{
			CString strMachineType("");
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->ResetContent();
			strMachineType = "CLF-285TX-55";
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->AddString(strMachineType); 
			((CComboBox*)GetDlgItem(IDC_COMBO_GRADE))->SetCurSel(0);
		}
		break;
	}
}

void CMDXMachinePage::OnCbnSelchangeComboMachineProducer()
{
	int iCurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO_PRODUCTER))->GetCurSel();
	if( m_iMachineSel ==  iCurrentSel)
	{
		return ;
	}
	m_iMachineSel = iCurrentSel;
	InitComboMachineGrade();
	SetMachineData();
}

void CMDXMachinePage::OnCbnSelchangeComboMachineGrade()
{

}

void CMDXMachinePage::SetMachineData()
{
	switch(m_iMachineSel)
	{
	case 0://FSC
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("250");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("40");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("229");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("627");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("500");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("273");
		}
		break;
	case 1://CLF
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("280");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("55");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("329");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("643");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("211");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("88.8");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("203");
		}
		break;
	}

	UpdateAllData();
}

void CMDXMachinePage::UpdateAllData()
{
	CString strValue("");
	GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->GetWindowText(strValue);
	SetClampingForceData(atof(strValue));
	GetDlgItem(IDC_EDIT_SCREW_DIAM)->GetWindowText(strValue);
	SetScrewDiamData(atof(strValue));
	GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->GetWindowText(strValue);
	SetMaxStrokeData(atof(strValue));
	GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->GetWindowText(strValue);
	SetInjectionVolumeData(atof(strValue));
	GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->GetWindowText(strValue);
	SetMaxInjectionVolumeData(atof(strValue));
	GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->GetWindowText(strValue);
	SetMaxInjectionVelocityData(atof(strValue));
	GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->GetWindowText(strValue);
	SetMaxInjectionPressureData(atof(strValue));

	//TRACE("%lf", GetMaxInjectionPressureData());

	//push screw diameter to data center
	DataCenter::getInstance().SetDiaScrew(GetScrewDiamData());
	//push max injection pressure to data center
	DataCenter::getInstance().SetMaxInjectionPressure(GetMaxInjectionPressureData());
	//push max screw stroke to data center
	DataCenter::getInstance().SetMaxScrewStroke(GetMaxStrokeData());
}

BOOL CMDXMachinePage::IsValidateData(CDataExchange *pDX)
{

	if( pDX == NULL )
    {
        return false;
    }
	     
    if( !IsClampingForceValidate( pDX ) )			{ return FALSE; };
	if( !IsScrewDiamValidate( pDX ) )				{ return FALSE; };
	if( !IsMaxStrokeValidate( pDX ) )				{ return FALSE; };
	if( !IsInjectionVolumeValidate( pDX ) )			{ return FALSE; };
	if( !IsMaxInjectionVolumeValidate( pDX ) )		{ return FALSE; };
	if( !IsMaxInjectionVelocityValidate( pDX ) )	{ return FALSE; };
	if( !IsMaxInjectionPressureValidate( pDX ) )	{ return FALSE; };
        //
   return TRUE;
   
}

BOOL CMDXMachinePage::IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue)
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

BOOL CMDXMachinePage::CheckInputValue( CDataExchange *pDX, UINT nEditID, double dValue)
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

BOOL CMDXMachinePage::IsClampingForceValidate( CDataExchange *pDX ) 			
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_CLAMPING_FORCE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_CLAMPING_FORCE, atof(strItem)))
	{
		return FALSE;
	}
	SetClampingForceData(atof(strItem));
	return TRUE;

}
BOOL CMDXMachinePage::IsScrewDiamValidate( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_SCREW_DIAM)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_SCREW_DIAM, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_SCREW_DIAM, atof(strItem)))
	{
		return FALSE;
	}
	SetScrewDiamData(atof(strItem));
	return TRUE;
 
}
BOOL CMDXMachinePage::IsMaxStrokeValidate( CDataExchange *pDX )
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_SCREW_STROKE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_SCREW_STROKE, atof(strItem)))
	{
		return FALSE;
	}
	this->SetMaxStrokeData(atof(strItem));
	return TRUE;

}
BOOL CMDXMachinePage::IsInjectionVolumeValidate( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_INJECTION_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_INJECTION_VOLUME, atof(strItem)))
	{
		return FALSE;
	}
	SetInjectionVolumeData(atof(strItem));
	return TRUE;

}
BOOL CMDXMachinePage::IsMaxInjectionVolumeValidate( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_VOLUME_OUTPUT, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_VOLUME_OUTPUT, atof(strItem)))
	{
		return FALSE;
	}
	this->SetMaxInjectionVolumeData(atof(strItem));
	return TRUE;

}
BOOL CMDXMachinePage::IsMaxInjectionVelocityValidate( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_INJECTION_VELOCITY, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_INJECTION_VELOCITY, atof(strItem)))
	{
		return FALSE;
	}
	SetMaxInjectionVelocityData(atof(strItem));
	return TRUE;

}
BOOL CMDXMachinePage::IsMaxInjectionPressureValidate( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_INJECTIONPRESSURE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_INJECTIONPRESSURE, atof(strItem)))
	{
		return FALSE;
	}
	SetMaxInjectionPressureData(atof(strItem));
	return TRUE;
}