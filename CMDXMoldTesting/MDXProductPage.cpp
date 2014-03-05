// MDXProdectPage.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXProductPage.h"
#include "afxdialogex.h"
#include "MDXStringParser.h"
#include "MDXProductPageData.h"
#include "DataCenter.h"
#include <vector>

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
, m_iGateNumber(0)
, m_iMachineSel(0)
, m_iMachineSelDefault(0)
, m_dClampingForce(0.)
, m_dScrewDiam(0.)
, m_dScrewDiamDefault(0.)
, m_iScrewDiaSel(0)
, m_dScrewDiamMax(0.)
, m_dScrewDiamMin(0.)
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
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MELT_TEMPERATURE, &CMDXProductPage::OnDeltaposSpinMeltTemperature)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BARREL_TEMPERATURE_FIRST, &CMDXProductPage::OnDeltaposSpinBarrelTemperatureFirst)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BARREL_TEMPERATURE_SECOND, &CMDXProductPage::OnDeltaposSpinBarrelTemperatureSecond)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BARREL_TEMPERATURE_THIRD, &CMDXProductPage::OnDeltaposSpinBarrelTemperatureThird)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOLD_TEMPERATURE_CORE, &CMDXProductPage::OnDeltaposSpinMoldTemperatureCore)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOLD_TEMPERATURE_CAVITY, &CMDXProductPage::OnDeltaposSpinMoldTemperatureCavity)
	ON_EN_CHANGE(IDC_EDIT_PLASTIC_VOLUME, &CMDXProductPage::OnEnChangeEditPlasticVolume)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_GATE_NUMBER, &CMDXProductPage::OnDeltaposSpinGateNumber)
	ON_BN_CLICKED(IDC_BUTTON_GATE_NUMBER_INFO, &CMDXProductPage::OnBnClickedButtonGateNumberInfo)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_TON_INFO, &CMDXProductPage::OnBnClickedButtonMachineTonInfo)
	ON_BN_CLICKED(IDC_BUTTON_SCREW_DIAM_INFO, &CMDXProductPage::OnBnClickedButtonScrewDiamInfo)
	ON_BN_CLICKED(IDC_BUTTON_SCREW_DIAM_DEFAULT_INFO, &CMDXProductPage::OnBnClickedButtonScrewDiamDefaultInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_SCREW_STROKE_INFO, &CMDXProductPage::OnBnClickedButtonMaxScrewStrokeInfo)
	ON_BN_CLICKED(IDC_BUTTON_INJECTION_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonInjectionVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_VOLUME_OUTPUT_INFO, &CMDXProductPage::OnBnClickedButtonMaxVolumeOutputInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_INJECTION_VELOCITY_INFO, &CMDXProductPage::OnBnClickedButtonMaxInjectionVelocityInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_INJECTION_PRESSURE_INFO, &CMDXProductPage::OnBnClickedButtonMaxInjectionPressureInfo)
	ON_BN_CLICKED(IDC_BUTTON_CLAMPING_FORCE_INFO, &CMDXProductPage::OnBnClickedButtonClampingForceInfo)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCREW_DIAM, &CMDXProductPage::OnDeltaposSpinScrewDiam)
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
	GetDlgItem(IDC_EDIT_GATE_NUMBER)->SetWindowText("1");
	SetGateNumberData(1);

	////push cold runner volume to data center
	//DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
}

void CMDXProductPage::InitComboMachineTon()
{
	//參考MDX專案內的[FCS]機台製造商
	CString strMachineType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->ResetContent();
	strMachineType = "30";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "60";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "110";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "150";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "200";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "250";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "300";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "350";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "450";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 
	strMachineType = "550";
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->AddString(strMachineType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->SetCurSel(AutoMachineSel());
	m_iMachineSel = AutoMachineSel();
	SetMachineData();
}

void CMDXProductPage::OnCbnSelchangeComboMachineTon()
{
	int iCurrentSel = ((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->GetCurSel();
	
	if( m_iMachineSel == iCurrentSel)
	{
		return ;
	}

	//TRACE("now:%d default:%d\n", m_iMachineSel, m_iMachineSelDefault);

	//不可選擇比預設更小的機台
	if (iCurrentSel < m_iMachineSelDefault)
	{
		MessageBox(_T("塑化體積超出機台限制，請選擇較大噸數"), 
					_T("警告 warning"), 
					MB_OK | MB_ICONWARNING);

		//跳回預設機台
		m_iMachineSel = m_iMachineSelDefault;
		((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->SetCurSel(m_iMachineSel);
		SetMachineData();

		return ;
	}

	m_iMachineSel = iCurrentSel;
	SetMachineData();
}

int CMDXProductPage::AutoMachineSel()
{
	std::vector<double> machineDia  (10, 0);    // 10 double with value 0
	machineDia[0] = 20;	//mm
	machineDia[1] = 24;
	machineDia[2] = 32;
	machineDia[3] = 38;
	machineDia[4] = 44;
	machineDia[5] = 44;
	machineDia[6] = 55;
	machineDia[7] = 55;
	machineDia[8] = 66;
	machineDia[9] = 72;

	double tmp = 0;
	for (int i=0; i<9; i++)
	{
		//2.0~2.5D為適當螺桿行程
		//2D*pi*D*D/4 = 2*塑化體積 (適當的螺桿行程*截面積=2倍塑化體積)
		tmp = (machineDia[i]/10) * 3.1415926 * (machineDia[i]/10) * (machineDia[i]/10) / 4;
		if (tmp >= m_dPlasticVolumeData)
		{
			m_iMachineSelDefault = i;
			return i;
		}
	}

	m_iMachineSelDefault = 9;
	return 9;
}

void CMDXProductPage::SetMachineData()
{
	//最大射出量  =  螺桿截面積 * 最大射速
	//求最大射速(mm/s) --> 10(cm to mm) * 最大射出量(cm^3/s) / 螺桿截面積(cm^2)
	double mv = 0; 
	switch(m_iMachineSel)
	{
	case 0://30 ton(AF-30-20)
		{
			mv = 10 * 220.0 / (0.25*3.1415926*(20.0/10)*(20.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("30");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("20");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("20");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("90");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("26"); //shot weight
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("220"); //injection rate
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("258");

			m_dScrewDiamMax = 22;
			m_dScrewDiamMin = 18;
		}
		break;
	case 1://60 ton(AF-60-24)
		{
			mv = 10 * 271.0 / (0.25*3.1415926*(24.0/10)*(24.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("60");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("24");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("24");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("110");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("45"); //shot weight
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("271"); //injection rate
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("220");

			m_dScrewDiamMax = 26;
			m_dScrewDiamMin = 22;
		}
		break;
	case 2://110 ton(AF-110-32)
		{
			mv = 10 * 483.0 / (0.25*3.1415926*(32.0/10)*(32.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("110");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("32");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("32");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("150");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("110"); //shot weight
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("483"); //injection rate
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("217");

			m_dScrewDiamMax = 34;
			m_dScrewDiamMin = 28;
		}
		break;
	case 3://150 ton(AF-150-38)
		{
			mv = 10 * 567.0 / (0.25*3.1415926*(38.0/10)*(38.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("150");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("38");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("38");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("180");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("186");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("567");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("232");

			m_dScrewDiamMax = 42;
			m_dScrewDiamMin = 34;
		}
		break;
	case 4://200 ton(AF-200-44)
		{
			mv = 10 * 759.0 / (0.25*3.1415926*(44.0/10)*(44.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("44");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("44");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("277"); //shot weight
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("759"); //injection rate
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("226");

			m_dScrewDiamMax = 48;
			m_dScrewDiamMin = 40;
		}
		break;
	case 5://250 ton(AF-250-44)
		{
			mv = 10 * 759.0 / (0.25*3.1415926*(44.0/10)*(44.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("250");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("44");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("44");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("277"); //shot weight
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("759"); //injection rate
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("226");

			m_dScrewDiamMax = 48;
			m_dScrewDiamMin = 40;
		}
		break;
	case 6://300 ton(AF-300-55)
		{
			mv = 10 * 949.0 / (0.25*3.1415926*(55.0/10)*(55.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("300");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("55");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("55");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("250");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("540");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("949");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("232");

			m_dScrewDiamMax = 60;
			m_dScrewDiamMin = 50;
		}
		break;
	case 7://350 ton(AF-350-55)
		{
			mv = 10 * 594.0 / (0.25*3.1415926*(55.0/10)*(55.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("350");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("55");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("55");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("250");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("540");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("594");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("231");

			m_dScrewDiamMax = 60;
			m_dScrewDiamMin = 50;
		}
		break;
	case 8://450 ton(AF-450-66)
		{
			mv = 10 * 1366.0 / (0.25*3.1415926*(66.0/10)*(66.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("450");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("66");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("66");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("300");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("934");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1366");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("193");

			m_dScrewDiamMax = 72;
			m_dScrewDiamMin = 60;
		}
		break;
	case 9://550 ton(AF-550-72)
		{
			mv = 10 * 1426.0 / (0.25*3.1415926*(72.0/10)*(72.0/10)); 
			CString strTemp("");
			strTemp.Format("%.0f", mv);

			GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->SetWindowText("550");
			GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText("72");
			GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->SetWindowText("72");
			GetDlgItem(IDC_EDIT_MAX_SCREW_STROKE)->SetWindowText("330");
			GetDlgItem(IDC_EDIT_INJECTION_VOLUME)->SetWindowText("1222");
			GetDlgItem(IDC_EDIT_MAX_VOLUME_OUTPUT)->SetWindowText("1426");
			GetDlgItem(IDC_EDIT_MAX_INJECTION_VELOCITY)->SetWindowText(strTemp);
			GetDlgItem(IDC_EDIT_MAX_INJECTIONPRESSURE)->SetWindowText("188");

			m_dScrewDiamMax = 76;
			m_dScrewDiamMin = 66;
		}
		break;
	}
	
	m_iScrewDiaSel = 0; //螺桿直徑=預設螺桿直徑
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
	if( !IsGateNumberValidate( pDX ) )			{ return FALSE; };

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
	CString strItem2("");
	GetDlgItem(IDC_EDIT_GATE_NUMBER)->GetWindowText(strItem2);
    
	if( !IsRealParse( pDX, IDC_EDIT_PLASTIC_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckPlasticVolumeValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem), atof(strItem2)))
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
	CString strItem2("");
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strItem2);
    
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

	if( !CheckGateThickness( pDX, IDC_EDIT_GATE_THICKNESS, atof(strItem), atof(strItem2)))
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

BOOL CMDXProductPage::IsGateNumberValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_GATE_NUMBER)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_GATE_NUMBER, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_GATE_NUMBER, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_GATE_NUMBER, atof(strItem)))
	{
		return FALSE;
	}

	SetGateNumberData(atof(strItem));
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
		strErrorMesg = "請輸入數字";
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
		strErrorMesg = "此設定值不能小於0";
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
		strErrorMesg = "此設定值不能等於0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}
BOOL CMDXProductPage::CheckPlasticVolumeValue(CDataExchange *pDX, UINT nEditID, double dValue, int gate)
{
	CMDXStringParser parser;
	if( (dValue/gate) > 550 )
	{
		CString strErrorMesg("");
		strErrorMesg = "建議[塑化體積/進澆數量]需小於550";
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
		strErrorMesg = "產品[平均肉厚]不可大於[最大肉厚]";
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
	GetDlgItem(IDC_EDIT_GATE_NUMBER)->GetWindowText(strTemp);
	SetGateNumberData(atof(strTemp));

	DataCenter::getInstance().SetPartVolume(GetVolumeData());
	DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
	DataCenter::getInstance().SetHotRunnerVolume(GetHotRunnerVolumeData());
	DataCenter::getInstance().SetGateThickness(GetGateThicknessData());
	DataCenter::getInstance().SetMaxPartThickness(GetMaxPartThicknessData());
	DataCenter::getInstance().SetGateNumber(GetGateNumberData());

	//-------------------------------------
	GetDlgItem(IDC_EDIT_CLAMPING_FORCE)->GetWindowText(strTemp);
	SetClampingForceData(atof(strTemp));
	GetDlgItem(IDC_EDIT_SCREW_DIAM)->GetWindowText(strTemp);
	SetScrewDiamData(atof(strTemp));
	GetDlgItem(IDC_EDIT_SCREW_DIAM_DEFAULT)->GetWindowText(strTemp);
	SetScrewDiamDefaultData(atof(strTemp));
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
	// 更新塑化體積
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
	// 更新塑化體積
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
	// 更新澆口短邊肉厚
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
	MessageBox(_T("成型品的產品體積，單位 cc\n"
				"(多模穴系統則為全部產品體積總和)"), 
				_T("產品體積 (product volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonCrVolumeInfo()
{
	MessageBox(_T("冷流道體積，單位 cc"), 
				_T("冷流道體積 (cold runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonHrVolumeInfo()
{
	MessageBox(_T("熱流道體積，單位 cc"), 
				_T("熱流道體積 (hot runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPlasticVolumeInfo()
{
	MessageBox(_T("每模次射出體積，單位 cc\n"
				"(預設為產品體積與冷流道體積總和)，建議 < 550 cc"), 
				_T("塑化體積 (plasticizing volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPartThicknessInfo()
{
	MessageBox(_T("產品平均肉厚，單位 mm\n"
				"(用以估計澆口短邊肉厚)"), 
				_T("產品平均肉厚 (product average thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxPartThicknessInfo()
{
	MessageBox(_T("產品最大肉厚，單位 mm\n"
				"(用以估計冷卻時間)"), 
				_T("產品最大肉厚 (product maximum thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonGateThicknessInfo()
{
	MessageBox(_T("澆口最薄處之肉厚，單位 mm\n"
				"(用以估計保壓時間)"), 
				_T("澆口短邊肉厚 (gate thickness)"), 
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
	strMaterialType = "PC+10%GF"; //Styron Celex 310HF
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "PC+ABS"; //Sabic Cycoloy C7230P
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "PA";
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 
	strMaterialType = "ABS"; //LG AF-312
	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->AddString(strMaterialType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_MATERIAL))->SetCurSel(0);
	m_iMaterialSel = 0;
	SetTemperatureData();
}

void CMDXProductPage::SetTemperatureData()
{
	switch(m_iMaterialSel)
	{
	case 0://PC+10%GF --Styron(Celex 310HF)
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("300");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("260");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("280"); 
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("120");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("80");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->SetWindowText("100"); 
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("100"); 
			
			m_dBarrelTempSlope = 5;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("280"); // IDC_EDIT_MELT_TEMPERATURE
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("275"); // first - slope
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("270"); // second - slope
		}
		break;
	case 1://PC+ABS --Sabic(Cycoloy C7230P)
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("280");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("240");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("260");
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("80");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("60");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->SetWindowText("70");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("70");

			m_dBarrelTempSlope = 5;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("260"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("255"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("250"); 
		}
		break;
	case 2://PA
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("260");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("230");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("245");
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("90");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("50");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->SetWindowText("70");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("70");

			m_dBarrelTempSlope = 10;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("245"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("235"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("225"); 
		}
		break;
	case 3://ABS --LG(AF-312)
		{
			GetDlgItem(IDC_EDIT_MAX_MELT_TEMPERATURE)->SetWindowText("230");
			GetDlgItem(IDC_EDIT_MIN_MELT_TEMPERATURE)->SetWindowText("200");
			GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText("215");
			GetDlgItem(IDC_EDIT_MAX_MOLD_TEMPERATURE)->SetWindowText("60");
			GetDlgItem(IDC_EDIT_MIN_MOLD_TEMPERATURE)->SetWindowText("40");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->SetWindowText("50");
			GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText("50");

			m_dBarrelTempSlope = 5;
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText("215"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText("210"); 
			GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText("205"); 
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
		strErrorMesg = "[料溫]需在建議上下限之間";
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
		strErrorMesg = "[模溫]需在建議上下限之間";
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
	MessageBox(_T("射嘴設定溫度，單位 ℃"), 
				_T("射嘴料溫 (melt temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureFirstInfo()
{
	MessageBox(_T("第一段料管設定溫度，單位 ℃\n"
				"(高黏度材料每段溫差 5℃、低黏度溫差 10℃)"), 
				_T("第一段料管溫度 (first barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureSecondInfo()
{
	MessageBox(_T("第二段料管設定溫度，單位 ℃"), 
				_T("第二段料管溫度 (second barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonBarrelTemperatureThirdInfo()
{
	MessageBox(_T("第三段料管設定溫度，單位 ℃"), 
				_T("第三段料管溫度 (third barrel temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureCoreInfo()
{
	MessageBox(_T("公模設定溫度，單位 ℃"), 
				_T("公模模溫 (core temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureCavityInfo()
{
	MessageBox(_T("母模設定溫度，單位 ℃"), 
				_T("母模模溫 (cavity temperature)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMeltTemperatureLimitInfo()
{
	MessageBox(_T("料商建議塑料加工溫度範圍，單位 ℃"), 
				_T("建議料溫 (suggested melt temperature range)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMoldTemperatureLimitInfo()
{
	MessageBox(_T("料商建議模具溫度範圍，單位 ℃"), 
				_T("建議模溫 (suggested mold temperature range)"), 
      MB_OK | MB_ICONINFORMATION);
}



void CMDXProductPage::OnDeltaposSpinMeltTemperature(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dMeltTemp < m_dMaxMeltTemp)  
    {
        m_dMeltTemp += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dMeltTemp > m_dMinMeltTemp)  
    {
        m_dMeltTemp -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dMeltTemp);
	GetDlgItem(IDC_EDIT_MELT_TEMPERATURE)->SetWindowText(strTemp); 
}


void CMDXProductPage::OnDeltaposSpinBarrelTemperatureFirst(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dBarrelTempFirst < m_dMaxMeltTemp)  
    {
        m_dBarrelTempFirst += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dBarrelTempFirst > m_dMinMeltTemp)  
    {
        m_dBarrelTempFirst -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dBarrelTempFirst);
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_FIRST)->SetWindowText(strTemp); 
}


void CMDXProductPage::OnDeltaposSpinBarrelTemperatureSecond(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dBarrelTempSecond < m_dMaxMeltTemp)  
    {
        m_dBarrelTempSecond += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dBarrelTempSecond > m_dMinMeltTemp)  
    {
        m_dBarrelTempSecond -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dBarrelTempSecond);
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_SECOND)->SetWindowText(strTemp); 
}


void CMDXProductPage::OnDeltaposSpinBarrelTemperatureThird(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dBarrelTempThird < m_dMaxMeltTemp)  
    {
        m_dBarrelTempThird += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dBarrelTempThird > m_dMinMeltTemp)  
    {
        m_dBarrelTempThird -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dBarrelTempThird);
	GetDlgItem(IDC_EDIT_BARREL_TEMPERATURE_THIRD)->SetWindowText(strTemp); 
}


void CMDXProductPage::OnDeltaposSpinMoldTemperatureCore(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dMoldTempCore < m_dMaxMoldTemp)  
    {
        m_dMoldTempCore += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dMoldTempCore > m_dMinMoldTemp)  
    {
        m_dMoldTempCore -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dMoldTempCore);
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CORE)->SetWindowText(strTemp); 
}


void CMDXProductPage::OnDeltaposSpinMoldTemperatureCavity(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-5
	//至多調整至料商建議上下限

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dMoldTempCavity < m_dMaxMoldTemp)  
    {
        m_dMoldTempCavity += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dMoldTempCavity > m_dMinMoldTemp)  
    {
        m_dMoldTempCavity -= 5;
    }

    CString strTemp("");
	strTemp.Format("%.0f", m_dMoldTempCavity);
	GetDlgItem(IDC_EDIT_MOLD_TEMPERATURE_CAVITY)->SetWindowText(strTemp); 
}

void CMDXProductPage::OnEnChangeEditPlasticVolume()
{
	//若塑化體積改變，改變自動推薦之機台選擇
	((CComboBox*)GetDlgItem(IDC_COMBO_MACHINE_TON))->SetCurSel(AutoMachineSel());
	m_iMachineSel = AutoMachineSel();
	SetMachineData();
}

void CMDXProductPage::OnDeltaposSpinGateNumber(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-1
	//不可 < 1

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iGateNumber < 20)  
    {
        m_iGateNumber += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iGateNumber > 1)  
    {
        m_iGateNumber -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iGateNumber);
	GetDlgItem(IDC_EDIT_GATE_NUMBER)->SetWindowText(strTemp); 
}

void CMDXProductPage::OnBnClickedButtonGateNumberInfo()
{
	MessageBox(_T("進澆數量"), 
				_T("進澆數量 (number of melt entrances)"), 
      MB_OK | MB_ICONINFORMATION);
}

BOOL CMDXProductPage::CheckGateThickness(CDataExchange *pDX, UINT nEditID, double gate, double part_max)
{
	CMDXStringParser parser;
	
	if (gate > part_max)
	{
		CString strErrorMesg("");
		strErrorMesg = "[澆口短邊肉厚]不可大於[產品最大肉厚]";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

void CMDXProductPage::OnBnClickedButtonMachineTonInfo()
{
	MessageBox(_T("選擇射出機噸數，單位 Ton\n"
				"(預設值依據塑化體積為噸數下限)"), 
				_T("機台噸數 (machine tonnage)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonScrewDiamInfo()
{
	MessageBox(_T("選擇螺桿直徑，單位 mm"), 
				_T("螺桿直徑 (screw diameter)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonScrewDiamDefaultInfo()
{
	MessageBox(_T("預設螺桿直徑，單位 mm"), 
				_T("預設螺桿直徑 (default screw diameter)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxScrewStrokeInfo()
{
	MessageBox(_T("最大螺桿行程，單位 mm"), 
				_T("預設螺桿之最大螺桿行程 (max screw stroke)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonInjectionVolumeInfo()
{
	MessageBox(_T("預設螺桿直徑之射出量，單位 g"), 
				_T("射出量 (injection volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxVolumeOutputInfo()
{
	MessageBox(_T("預設螺桿直徑之最大射出量，單位 cc/s"), 
				_T("最大射出量 (max injection volume output)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxInjectionVelocityInfo()
{
	MessageBox(_T("預設螺桿直徑之最大射速，單位 mm/s"), 
				_T("最大射速 (max injection velocity)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxInjectionPressureInfo()
{
	MessageBox(_T("預設螺桿直徑之最大射壓，單位 MPa"), 
				_T("最大射壓 (max injection pressure)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonClampingForceInfo()
{
	MessageBox(_T("機台鎖模力，單位 Ton"), 
				_T("機台鎖模力 (machine clamping force)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnDeltaposSpinScrewDiam(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按箭頭可以在3種螺桿直徑間轉換
	//m_iScrewDiaSel = -1(較小螺桿), 0(預設螺桿), 1(較大螺桿)

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iScrewDiaSel != 1)  
    {
        if (m_iScrewDiaSel == 0)
		{
			m_dScrewDiam = m_dScrewDiamMax;
		}
		else
		{
			m_dScrewDiam = m_dScrewDiamDefault;
		}

		m_iScrewDiaSel += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iScrewDiaSel != -1)  
    {
        if (m_iScrewDiaSel == 0)
		{
			m_dScrewDiam = m_dScrewDiamMin;
		}
		else
		{
			m_dScrewDiam = m_dScrewDiamDefault;
		}

		m_iScrewDiaSel -= 1;
    }


	CString strTemp("");
	strTemp.Format("%.0f", m_dScrewDiam);
	GetDlgItem(IDC_EDIT_SCREW_DIAM)->SetWindowText(strTemp); 
}
