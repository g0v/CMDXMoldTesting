// MDXProdectPage.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXProductPage.h"
#include "afxdialogex.h"
#include "MDXStringParser.h"
#include "MDXProductPageData.h"
#include "DataCenter.h"


// CMDXProductPage dialog

IMPLEMENT_DYNAMIC(CMDXProductPage, CDialog)

CMDXProductPage::CMDXProductPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMDXProductPage::IDD, pParent)
, m_bCheckEditData(false)
, m_dVolumeData(0.)
, m_dColdRunnerVolumeData(0.)
, m_dHotRunnerVolumeData(0.)
, m_dPlasticVolumeData(0.)
, m_dGateThicknessData(0.)
, m_dPartThicknessData(0.)
, m_dMaxPartThicknessData(0.)
, m_iMachineSel(0)
, m_dClampingForce(0.)
, m_dScrewDiam(0.)
, m_dMaxStroke(0.)
, m_dInjectionVolume(0.)
, m_dMaxInjectionVolume(0.)
, m_dMaxInjectionVelocity(0.)
, m_dMaxInjectionPressure(0.)
, m_iMaterialSel(0)
, m_dMaxMeltTemp(0.)
, m_dMinMeltTemp(0.)
, m_dMaxMoldTemp(0.)
, m_dMinMoldTemp(0.)
, m_dMeltTemp(0.)
, m_dMoldTempCore(0.)
, m_dMoldTempCavity(0.)
, m_dBarrelTempSlope(0.)
, m_dBarrelTempFirst(0.)
, m_dBarrelTempSecond(0.)
, m_dBarrelTempThird(0.)
{

}

CMDXProductPage::~CMDXProductPage()
{
}

void CMDXProductPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	if( m_bCheckEditData )
	{
		IsValidateData( pDX );	
	}
}


BEGIN_MESSAGE_MAP(CMDXProductPage, CDialog)
	
	ON_EN_CHANGE(IDC_EDIT_VOLUME, &CMDXProductPage::OnEnChangeEditPartVolume)
	ON_EN_CHANGE(IDC_EDIT_CR_VOLUME, &CMDXProductPage::OnEnChangeEditColdRunnerVolume)
	ON_EN_CHANGE(IDC_EDIT_PART_THICKNESS, &CMDXProductPage::OnEnChangeEditPartThickness)
	ON_EN_CHANGE(IDC_EDIT_MAX_PART_THICKNESS, &CMDXProductPage::OnEnChangeEditMaxPartThickness)
	ON_EN_CHANGE(IDC_EDIT_HR_VOLUME, &CMDXProductPage::OnEnChangeEditHrVolume)
	ON_BN_CLICKED(IDC_BUTTON_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_CR_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonCrVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_HR_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonHrVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_PLASTIC_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonPlasticVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_PART_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonPartThicknessInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_PART_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonMaxPartThicknessInfo)
	ON_BN_CLICKED(IDC_BUTTON_GATE_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonGateThicknessInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_MACHINE_TON, &CMDXProductPage::OnCbnSelchangeComboMachineTon)
	//ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL2, &CMDXProductPage::OnCbnSelchangeComboMaterial)
	ON_EN_CHANGE(IDC_EDIT_MOLD_TEMPERATURE, &CMDXProductPage::OnEnChangeEditMoldTemperature)
	ON_EN_CHANGE(IDC_EDIT_MELT_TEMPERATURE, &CMDXProductPage::OnEnChangeEditMeltTemperature)
	ON_BN_CLICKED(IDC_BUTTON_MELT_TEMPERATURE_INFO, &CMDXProductPage::OnBnClickedButtonMeltTemperatureInfo)
	ON_BN_CLICKED(IDC_BUTTON_BARREL_TEMPERATURE_FIRST_INFO, &CMDXProductPage::OnBnClickedButtonBarrelTemperatureFirstInfo)
	ON_BN_CLICKED(IDC_BUTTON_BARREL_TEMPERATURE_SECOND_INFO, &CMDXProductPage::OnBnClickedButtonBarrelTemperatureSecondInfo)
	ON_BN_CLICKED(IDC_BUTTON_BARREL_TEMPERATURE_THIRD_INFO, &CMDXProductPage::OnBnClickedButtonBarrelTemperatureThirdInfo)
	ON_BN_CLICKED(IDC_BUTTON_MOLD_TEMPERATURE_CORE_INFO, &CMDXProductPage::OnBnClickedButtonMoldTemperatureCoreInfo)
	ON_BN_CLICKED(IDC_BUTTON_MOLD_TEMPERATURE_CAVITY_INFO, &CMDXProductPage::OnBnClickedButtonMoldTemperatureCavityInfo)
	ON_BN_CLICKED(IDC_BUTTON_MELT_TEMPERATURE_LIMIT_INFO, &CMDXProductPage::OnBnClickedButtonMeltTemperatureLimitInfo)
	ON_BN_CLICKED(IDC_BUTTON_MOLD_TEMPERATURE_LIMIT_INFO, &CMDXProductPage::OnBnClickedButtonMoldTemperatureLimitInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL, &CMDXProductPage::OnCbnSelchangeComboMaterial)
END_MESSAGE_MAP()

BOOL CMDXProductPage::OnInitDialog()
{
	InitEditData();
	InitComboMachineTon();
	InitComboMaterialData();

	m_bCheckEditData = true;
	return TRUE;
}
// CMDXProductPage message handlers

void CMDXProductPage::InitEditData()
{
	//CString strVolumeText("");
	//strVolumeText= "300";
	//GetDlgItem( IDC_EDIT_VOLUME )->SetWindowText(strVolumeText);	
	//((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOLUME))->SetRange(0, 10000 );
	//(CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOLUME))->SetBuddy(GetDlgItem(IDC_EDIT_VOLUME),0);

	// cold & hot runner volume default = 0
	GetDlgItem(IDC_EDIT_CR_VOLUME)->SetWindowText("0.00");
	SetColdRunnerVolumeData(0.0);
	GetDlgItem(IDC_EDIT_HR_VOLUME)->SetWindowText("0.00");
	SetHotRunnerVolumeData(0.0);

	////push cold runner volume to data center
	//DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
}

void CMDXProductPage::InitComboMachineTon()
{
	CString strMachineType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->ResetContent();
	strMachineType = "25";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "51";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "61";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "133";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "153";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "163";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "204";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "326";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "408";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "469";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "510";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->SetCurSel(0);
	m_iMachineSel = 0;
	SetMachineData();
}

void CMDXProductPage::OnCbnSelchangeComboMachineTon()
{
	int iCurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->GetCurSel();
	if( m_iMachineSel ==  iCurrentSel)
	{
		return ;
	}
	m_iMachineSel = iCurrentSel;
	SetMachineData();
}

void CMDXProductPage::SetMachineData()
{
	switch(m_iMachineSel)
	{
	case 0://25 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("25");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("22");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("89");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("31");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("62");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("200");
		}
		break;
	case 1://51 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("51");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("25");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("120");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("54");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("98");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	case 2://61 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("61");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("25");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("100");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("45");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("124");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("224");
		}
		break;
	case 3://133 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("133");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("25");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("110");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("49");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("80");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	case 4://153 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("153");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("50");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("359");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("214");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("200");
		}
		break;
	case 5://163 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("163");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("35");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("144");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("127");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("128");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	case 6://204 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("204");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("35");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("144");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("127");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("128");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	case 7://326 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("326");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("70");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("280");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("984");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("306");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("200");
		}
		break;
	case 8://408 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("163");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("60");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("280");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("723");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("290");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	case 9://469 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("469");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("70");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("280");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("984");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("306");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("200");
		}
		break;
	case 10://510 ton
		{
			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("510");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("70");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("320");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("1125");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1111");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText("290");
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("250");
		}
		break;
	}

	UpdateAllData();
}

BOOL CMDXProductPage::UpdatePageData()
{
	BOOL bState = FALSE;
	if( !UpdateData())
	{
		return FALSE;
	}

	bState = UpDateEditData();

	return bState;

}

BOOL CMDXProductPage::IsValidateData(CDataExchange *pDX)
{
	//return true;	
	if( pDX == NULL )
    {
        return false;
    }
	     
    if( !IsVolumeValidate( pDX ) )				{ return FALSE; };
    if( !IsColdRunnerVolumeValidate( pDX ) )	{ return FALSE; };
    if( !IsHotRunnerVolumeValidate( pDX ) )     { return FALSE; };
	if( !IsPlasticVolumeValidate( pDX ) )		{ return FALSE; };
	if( !IsGateThicknessValidate( pDX ) )		{ return FALSE; };
	if( !IsPartThicknessValidate( pDX ) )		{ return FALSE; };
	if( !IsMaxPartThicknessValidate( pDX ) )    { return FALSE; };

	if( !IsClampingForceValidate( pDX ) )			{ return FALSE; };
	if( !IsScrewDiamValidate( pDX ) )				{ return FALSE; };
	if( !IsMaxStrokeValidate( pDX ) )				{ return FALSE; };
	if( !IsInjectionVolumeValidate( pDX ) )			{ return FALSE; };
	if( !IsMaxInjectionVolumeValidate( pDX ) )		{ return FALSE; };
	if( !IsMaxInjectionVelocityValidate( pDX ) )	{ return FALSE; };
	if( !IsMaxInjectionPressureValidate( pDX ) )	{ return FALSE; };

	if( !IsMaxMeltTemperature( pDX ) )			{ return FALSE; };
	if( !IsMinMeltTemperature( pDX ) )				{ return FALSE; };
	if( !IsMeltTemperature( pDX ) )				{ return FALSE; };
	if( !IsMaxMoldTemperature( pDX ) )				{ return FALSE; };
	if( !IsMinMoldTemperature( pDX ) )			{ return FALSE; };
	if( !IsMoldTemperatureCore( pDX ) )			{ return FALSE; };
	if( !IsMoldTemperatureCavity( pDX ) )			{ return FALSE; };
        //
   return TRUE;
   
}

BOOL CMDXProductPage::IsVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetVolumeData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsColdRunnerVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_CR_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_CR_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_CR_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetColdRunnerVolumeData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsHotRunnerVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_HR_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_HR_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_HR_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetHotRunnerVolumeData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsPlasticVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_PLASTIC_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_PLASTIC_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckPlasticVolumeValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetPlasticVolumeData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsGateThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_GATE_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_GATE_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_GATE_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_GATE_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	SetGateThicknessData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsPartThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_PART_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_PART_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	CString strItem2("");
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strItem2);

	if( !CheckPartThickness( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem), atof(strItem2)))
	{
		return FALSE;
	}

	SetPartThicknessData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsMaxPartThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_PART_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	SetMaxPartThicknessData(atof(strItem));
	return TRUE;
}
BOOL CMDXProductPage::IsClampingForceValidate( CDataExchange *pDX ) 			
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
BOOL CMDXProductPage::IsScrewDiamValidate( CDataExchange *pDX ) 
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
BOOL CMDXProductPage::IsMaxStrokeValidate( CDataExchange *pDX )
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
BOOL CMDXProductPage::IsInjectionVolumeValidate( CDataExchange *pDX ) 
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
BOOL CMDXProductPage::IsMaxInjectionVolumeValidate( CDataExchange *pDX ) 
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
BOOL CMDXProductPage::IsMaxInjectionVelocityValidate( CDataExchange *pDX ) 
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
BOOL CMDXProductPage::IsMaxInjectionPressureValidate( CDataExchange *pDX ) 
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
BOOL CMDXProductPage::IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue)
{
    CMDXStringParser parser;

    if( !parser.IsRealParse( strValue ) )
    {
        CString strErrorMesg("");
		strErrorMesg = "�п�J�Ʀr";
		parser.ShowWarningMessage( pDX, nEditID,  strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );

        return FALSE;
    }

    return TRUE;
}

BOOL CMDXProductPage::CheckInputValue( CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue < 0 )
	{
		CString strErrorMesg("");
		strErrorMesg = "���]�w�Ȥ���p��0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}
BOOL CMDXProductPage::CheckInputValueNotZero(CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue == 0 )
	{
		CString strErrorMesg("");
		strErrorMesg = "���]�w�Ȥ��൥��0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}
BOOL CMDXProductPage::CheckPlasticVolumeValue(CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue > 550 )
	{
		CString strErrorMesg("");
		strErrorMesg = "��ĳ�����n�ݤp��550";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}
BOOL CMDXProductPage::CheckPartThickness(CDataExchange *pDX, UINT nEditID, double part, double max)
{
	CMDXStringParser parser;
	
	if (part > max)
	{
		CString strErrorMesg("");
		strErrorMesg = "���~[�����׫p]���i�j��[�̤j�׫p]";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::UpDateEditData()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_VOLUME )->GetWindowText(strEditData);
	//m_cEditPartVolume.GetWindowTextW(strEditData);
	//::AfxMessageBox(strEditData);

	return TRUE;
}

void CMDXProductPage::UpdateAllData()
{		
	CString strTemp("");
	GetDlgItem(IDC_EDIT_VOLUME)->GetWindowText(strTemp);
	SetVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_CR_VOLUME)->GetWindowText(strTemp);
	SetColdRunnerVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_HR_VOLUME)->GetWindowText(strTemp);
	SetHotRunnerVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_GATE_THICKNESS)->GetWindowText(strTemp);
	SetGateThicknessData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strTemp);
	SetMaxPartThicknessData(atof(strTemp));

	DataCenter::getInstance().SetPartVolume(GetVolumeData());
	DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
	DataCenter::getInstance().SetHotRunnerVolume(GetHotRunnerVolumeData());
	DataCenter::getInstance().SetGateThickness(GetGateThicknessData());
	DataCenter::getInstance().SetMaxPartThickness(GetMaxPartThicknessData());

	//-------------------------------------
	GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->GetWindowText(strTemp);
	SetClampingForceData(atof(strTemp));
	GetDlgItem(IDC_EDIT_SCREW_DIAM)->GetWindowText(strTemp);
	SetScrewDiamData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->GetWindowText(strTemp);
	SetMaxStrokeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->GetWindowText(strTemp);
	SetInjectionVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->GetWindowText(strTemp);
	SetMaxInjectionVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->GetWindowText(strTemp);
	SetMaxInjectionVelocityData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->GetWindowText(strTemp);
	SetMaxInjectionPressureData(atof(strTemp));

	//TRACE("%lf", GetMaxInjectionPressureData());

	//push screw diameter to data center
	DataCenter::getInstance().SetDiaScrew(GetScrewDiamData());
	//push max injection pressure to data center
	DataCenter::getInstance().SetMaxInjectionPressure(GetMaxInjectionPressureData());
	//push max screw stroke to data center
	DataCenter::getInstance().SetMaxScrewStroke(GetMaxStrokeData());

	//-------------------------------------
	GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->GetWindowText(strTemp);
	SetMaxMeltTemperature(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->GetWindowText(strTemp);
	SetMinMeltTemperature(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->GetWindowText(strTemp);
	SetMaxMoldTemperature(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->GetWindowText(strTemp);
	SetMinMoldTemperature(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->GetWindowText(strTemp);
	SetMoldTemperatureCore(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->GetWindowText(strTemp);
	SetMoldTemperatureCore(atof(strTemp) );
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->GetWindowText(strTemp);
	SetMoldTemperatureCavity(atof(strTemp) );
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->GetWindowText(strTemp);
	SetBarrelTemperatureFirst(atof(strTemp) );
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->GetWindowText(strTemp);
	SetBarrelTemperatureSecond(atof(strTemp) );
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->GetWindowText(strTemp);
	SetBarrelTemperatureThird(atof(strTemp) );

	//push material selection to data center
	DataCenter::getInstance().SetMaterialSel(m_iMaterialSel);
}

void CMDXProductPage::OnEnChangeEditPartVolume()
{
	// ��s�����n
	CString strEditData("");
	GetDlgItem( IDC_EDIT_VOLUME )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	SetVolumeData(d);
	double modifiedPV = d + GetColdRunnerVolumeData();
	SetPlasticVolumeData(modifiedPV);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedPV);
	GetDlgItem( IDC_EDIT_PLASTIC_VOLUME )->SetWindowText(strTemp);

	//push part volume to data center
	DataCenter::getInstance().SetPartVolume(GetVolumeData());
}

void CMDXProductPage::OnEnChangeEditColdRunnerVolume()
{
	// ��s�����n
	CString strEditData("");
	GetDlgItem( IDC_EDIT_CR_VOLUME )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	SetColdRunnerVolumeData(d);
	double modifiedPV = GetVolumeData() + d;
	SetPlasticVolumeData(modifiedPV);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedPV);
	GetDlgItem( IDC_EDIT_PLASTIC_VOLUME )->SetWindowText(strTemp);

	//push cold runner volume to data center
	DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
}

void CMDXProductPage::OnEnChangeEditPartThickness()
{
	// ��s��f�u��׫p
	CString strEditData("");
	GetDlgItem( IDC_EDIT_PART_THICKNESS )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	double modifiedGate = d *2 /3;
	SetGateThicknessData(modifiedGate);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedGate);
	GetDlgItem( IDC_EDIT_GATE_THICKNESS )->SetWindowText(strTemp);

	//push gate thickness to data center
	DataCenter::getInstance().SetGateThickness(GetGateThicknessData());
}

void CMDXProductPage::OnEnChangeEditMaxPartThickness()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_MAX_PART_THICKNESS )->GetWindowText(strEditData);
	double t = _tstof(strEditData);
	SetMaxPartThicknessData(t);

	DataCenter::getInstance().SetMaxPartThickness(GetMaxPartThicknessData());
}

void CMDXProductPage::OnEnChangeEditHrVolume()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_HR_VOLUME )->GetWindowText(strEditData);
	double HR = _tstof(strEditData);
	SetHotRunnerVolumeData(HR);

	DataCenter::getInstance().SetHotRunnerVolume(GetHotRunnerVolumeData());
}


void CMDXProductPage::OnBnClickedButtonVolumeInfo()
{
	MessageBox(_T("�����~�����~��n�A��� cc (�h�ҥިt�Ϋh���������~��n�`�M)"), _T("���~��n (product volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonCrVolumeInfo()
{
	MessageBox(_T("�N�y�D��n�A��� cc"), _T("�N�y�D��n (cold runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonHrVolumeInfo()
{
	MessageBox(_T("���y�D��n�A��� cc"), _T("���y�D��n (hot runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPlasticVolumeInfo()
{
	MessageBox(_T("�C�Ҧ��g�X��n�A��� cc (�w�]�����~��n�P�N�y�D��n�`�M)�A��ĳ < 550 cc"), _T("�����n (plasticizing volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPartThicknessInfo()
{
	MessageBox(_T("���~�����׫p�A��� mm (�ΥH���p��f�u��׫p)"), _T("���~�����׫p (product average thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxPartThicknessInfo()
{
	MessageBox(_T("���~�̤j�׫p�A��� mm (�ΥH���p�N�o�ɶ�)"), _T("���~�̤j�׫p (product maximum thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonGateThicknessInfo()
{
	MessageBox(_T("��f�����B���׫p�A��� mm (�ΥH���p�O���ɶ�)"), _T("��f�u��׫p (gate thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnCbnSelchangeComboMaterial()
{
	int iCurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->GetCurSel();
	if( m_iMaterialSel ==  iCurrentSel)
	{
		return ;
	}
	m_iMaterialSel = iCurrentSel;
	SetTemperatureData();
}

void CMDXProductPage::InitComboMaterialData()
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

void CMDXProductPage::SetTemperatureData()
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
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("75"); // (90+60)/2
			
			m_dBarrelTempSlope = 5;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("265"); // IDC_EDIT_MELT_TEMPERATURE
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("260"); // first - slope
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("255"); // second - slope
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
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("70");

			m_dBarrelTempSlope = 10;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("235"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("225"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("215"); 
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
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("70");

			m_dBarrelTempSlope = 10;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("245"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("235"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("225"); 
		}
		break;
	}

	UpdateAllData();
}

BOOL CMDXProductPage::CheckMeltMinMax( CDataExchange *pDX, UINT nEditID, double melt, double min, double max )
{
	CMDXStringParser parser;
	if( melt < min || melt > max )
	{
		CString strErrorMesg("");
		strErrorMesg = "[�Ʒ�]�ݦb��ĳ�W�U������";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::CheckMoldMinMax( CDataExchange *pDX, UINT nEditID, double mold, double min, double max )
{
	CMDXStringParser parser;
	if( mold < min || mold > max )
	{
		CString strErrorMesg("");
		strErrorMesg = "[�ҷ�]�ݦb��ĳ�W�U������";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::IsMaxMeltTemperature( CDataExchange *pDX ) 
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

BOOL CMDXProductPage::IsMinMeltTemperature( CDataExchange *pDX ) 
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

BOOL CMDXProductPage::IsMeltTemperature( CDataExchange *pDX ) 
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

BOOL CMDXProductPage::IsMaxMoldTemperature( CDataExchange *pDX ) 
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

BOOL CMDXProductPage::IsMinMoldTemperature( CDataExchange *pDX ) 
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

BOOL CMDXProductPage::IsMoldTemperatureCore( CDataExchange *pDX ) 
{ 
	CString strItem("");
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MOLD_TEMPERATURE_CORE, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MOLD_TEMPERATURE_CORE, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckMoldMinMax( pDX, IDC_EDIT_MOLD_TEMPERATURE_CORE, atof(strItem), 
		GetMinMoldTemperature(), GetMaxMoldTemperature()))
	{
		return FALSE;
	}

	SetMoldTemperatureCore(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsMoldTemperatureCavity( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MOLD_TEMPERATURE_CAVITY, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MOLD_TEMPERATURE_CAVITY, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckMoldMinMax( pDX, IDC_EDIT_MOLD_TEMPERATURE_CAVITY, atof(strItem), 
		GetMinMoldTemperature(), GetMaxMoldTemperature()))
	{
		return FALSE;
	}

	SetMoldTemperatureCavity(atof(strItem));
	return TRUE;
}

void CMDXProductPage::OnEnChangeEditMoldTemperature()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_MOLD_TEMPERATURE )->GetWindowText(strEditData);
	double t = _tstof(strEditData);
	SetMoldTemperatureCore(t);
}

void CMDXProductPage::OnEnChangeEditMeltTemperature()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_MELT_TEMPERATURE )->GetWindowText(strEditData);
	double t = _tstof(strEditData);
	SetMeltTemperature(t);
}


void CMDXProductPage::OnBnClickedButtonMeltTemperatureInfo()
{
	MessageBox(_T("�g�L�]�w�ūסA��� �J"), _T("�g�L�Ʒ� (melt temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureFirstInfo()
{
	MessageBox(_T("�Ĥ@�q�ƺ޳]�w�ūסA��� �J (���H�ק��ƨC�q�Ůt 5�J�B�C�H�׷Ůt 10�J)"), _T("�Ĥ@�q�ƺ޷ū� (first barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureSecondInfo()
{
	MessageBox(_T("�ĤG�q�ƺ޳]�w�ūסA��� �J"), _T("�ĤG�q�ƺ޷ū� (second barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureThirdInfo()
{
	MessageBox(_T("�ĤT�q�ƺ޳]�w�ūסA��� �J"), _T("�ĤT�q�ƺ޷ū� (third barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureCoreInfo()
{
	MessageBox(_T("���ҳ]�w�ūסA��� �J"), _T("���Ҽҷ� (core temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureCavityInfo()
{
	MessageBox(_T("���ҳ]�w�ūסA��� �J"), _T("���Ҽҷ� (cavity temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMeltTemperatureLimitInfo()
{
	MessageBox(_T("�ưӫ�ĳ��ƥ[�u�ū׽d��A��� �J"), _T("��ĳ�Ʒ� (suggested melt temperature range)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureLimitInfo()
{
	MessageBox(_T("�ưӫ�ĳ�Ҩ�ū׽d��A��� �J"), _T("��ĳ�ҷ� (suggested mold temperature range)"), 
      MB_OK | MB_ICONINFORMATION);
}

