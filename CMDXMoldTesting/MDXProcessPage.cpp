// MDXProcessPage.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXProcessPage.h"
#include "afxdialogex.h"
#include "DataCenter.h"

// CMDXProcessPage dialog

IMPLEMENT_DYNAMIC(CMDXProcessPage, CDialog)

CMDXProcessPage::CMDXProcessPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMDXProcessPage::IDD, pParent)
, m_iFillSel(0)
, m_iPackSel(0)
, m_iGateNumber(0)
, m_iMaterialSel(0)
, m_iSpeedRatio_1(0)
, m_iSpeedRatio_2(0)
, m_iSpeedRatio_3(0)
, m_iPackPressurePercent_1(0)
, m_iPackPressurePercent_2(0)
, m_iPackTimeRatio_1(0)
, m_iPackTimeRatio_2(0)
, m_pParent(pParent)
{

}

CMDXProcessPage::~CMDXProcessPage()
{
}

void CMDXProcessPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMDXProcessPage, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMDXProcessPage::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_FILLING_SECTION, &CMDXProcessPage::OnCbnSelchangeComboFillingSection)
	ON_CBN_SELCHANGE(IDC_COMBO_PACKING_SECTION, &CMDXProcessPage::OnCbnSelchangeComboPackingSection)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VP, &CMDXProcessPage::OnDeltaposSpinVP)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_INJECTION_PRESSURE, &CMDXProcessPage::OnDeltaposSpinInjectionPressure)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FILLINT_TIME, &CMDXProcessPage::OnDeltaposSpinFillTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MOLDOPEN_TIME, &CMDXProcessPage::OnDeltaposSpinMoldopenTime)
	ON_BN_CLICKED(IDC_BUTTON_VP_INFO, &CMDXProcessPage::OnBnClickedButtonVpInfo)
	ON_BN_CLICKED(IDC_BUTTON_INJECTION_PRESSURE_INFO, &CMDXProcessPage::OnBnClickedButtonInjectionPressureInfo)
	ON_BN_CLICKED(IDC_BUTTON_FILLINT_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonFillintTimeInfo)
	ON_BN_CLICKED(IDC_BUTTON_FILLING_SECTION_INFO, &CMDXProcessPage::OnBnClickedButtonFillingSectionInfo)
	ON_BN_CLICKED(IDC_BUTTON_PACKING_SECTION_INFO, &CMDXProcessPage::OnBnClickedButtonPackingSectionInfo)
	ON_BN_CLICKED(IDC_BUTTON_COOLING_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonCoolingTimeInfo)
	ON_BN_CLICKED(IDC_BUTTON_MOLDOPEN_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonMoldopenTimeInfo)
	ON_BN_CLICKED(IDC_BUTTON_CYCLE_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonCycleTimeInfo)
	ON_BN_CLICKED(IDC_BUTTON_RESIDENCE_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonResidenceTimeInfo)
	ON_BN_CLICKED(IDC_BUTTON_PACKING_TIME_INFO, &CMDXProcessPage::OnBnClickedButtonPackingTimeInfo)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PACKING_TIME, &CMDXProcessPage::OnDeltaposSpinPackingTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_COOLING_TIME, &CMDXProcessPage::OnDeltaposSpinCoolingTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FILLINGSPEED_1, &CMDXProcessPage::OnDeltaposSpinFillingspeed1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FILLINGSPEED_2, &CMDXProcessPage::OnDeltaposSpinFillingspeed2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_FILLINGSPEED_3, &CMDXProcessPage::OnDeltaposSpinFillingspeed3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PACKINGPRESSURE_1, &CMDXProcessPage::OnDeltaposSpinPackingpressure1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PACKINGPRESSURE_2, &CMDXProcessPage::OnDeltaposSpinPackingpressure2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PACKINGTIME_1, &CMDXProcessPage::OnDeltaposSpinPackingtime1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PACKINGTIME_2, &CMDXProcessPage::OnDeltaposSpinPackingtime2)
	ON_BN_CLICKED(IDC_BUTTON_PACKING_PRESSURE_PERCENT_INFO, &CMDXProcessPage::OnBnClickedButtonPackingPressurePercentInfo)
	ON_BN_CLICKED(IDC_BUTTON_PACKING_TIME_RATIO_INFO, &CMDXProcessPage::OnBnClickedButtonPackingTimeRatioInfo)
END_MESSAGE_MAP()


// CMDXProcessPage message handlers
BOOL CMDXProcessPage::OnInitDialog()
{
	InitVP();
	InitInjectionPressure();

	InitFillTime();
	InitPackTime();
	InitVolumeExpansion();

	InitComboProcessFill();
	InitComboProcessPack();

	InitFillSpeedRatio();
	InitPackPressurePercent();
	InitPackTimeRatio();

	SetProfileFill();
	SetProfilePack();

	InitCoolTime();
	InitMoldOpenTime();
	InitCycleTime();
	InitResidenceTime();

	return TRUE;
}

void CMDXProcessPage::InitCoolTime()
{
	double max_part = DataCenter::getInstance().GetMaxPartThickness();
	m_dCoolTime = max_part * (1+2*max_part) - m_dPackTime;
	m_dCoolTime_step = m_dCoolTime * 0.01;
	m_dCoolTime_max = m_dCoolTime * 1.5;
	m_dCoolTime_min = m_dCoolTime * 1.0;

	CString strTemp("");
	strTemp.Format("%.1f", m_dCoolTime);
	GetDlgItem(IDC_EDIT_COOLING_TIME)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitMoldOpenTime()
{
	m_dMoldOpenTime = 5.0;
	m_dMoldOpenTime_step = m_dMoldOpenTime * 0.01;
	m_dMoldOpenTime_max = m_dMoldOpenTime * 1.1;
	m_dMoldOpenTime_min = m_dMoldOpenTime * 0.9;

	CString strTemp("");
	strTemp.Format("%.1f", m_dMoldOpenTime);
	GetDlgItem(IDC_EDIT_MOLDOPEN_TIME)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitFillSpeedRatio()
{
	//預設速度比 2:4:1
	m_iSpeedRatio_1 = 2;
	m_iSpeedRatio_2 = 4;
	m_iSpeedRatio_3 = 1;

	CString strTemp("");
	strTemp.Format("%d", m_iSpeedRatio_1);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_1)->SetWindowText(strTemp);
	strTemp.Format("%d", m_iSpeedRatio_2);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_2)->SetWindowText(strTemp);
	strTemp.Format("%d", m_iSpeedRatio_3);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_3)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitPackPressurePercent()
{
	//預設為機器壓力的 70%:40%
	m_iPackPressurePercent_1 = 70;
	m_iPackPressurePercent_2 = 40;

	CString strTemp("");
	strTemp.Format("%d", m_iPackPressurePercent_1);
	GetDlgItem(IDC_EDIT_PACKINGPRESSURE_1)->SetWindowText(strTemp);
	strTemp.Format("%d", m_iPackPressurePercent_2);
	GetDlgItem(IDC_EDIT_PACKINGPRESSURE_2)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitPackTimeRatio()
{
	//預設為 1:1
	m_iPackTimeRatio_1 = 1;
	m_iPackTimeRatio_2 = 1;

	CString strTemp("");
	strTemp.Format("%d", m_iPackTimeRatio_1);
	GetDlgItem(IDC_EDIT_PACKINGTIME_1)->SetWindowText(strTemp);
	strTemp.Format("%d", m_iPackTimeRatio_2);
	GetDlgItem(IDC_EDIT_PACKINGTIME_2)->SetWindowText(strTemp);
}

void CMDXProcessPage::OnDeltaposSpinMoldopenTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-bigger(預設值的1%, 0.1) 
	//至多調整+-10%

	if (m_dMoldOpenTime_step < 0.1)
	{
		m_dMoldOpenTime_step = 0.1;
	}

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dMoldOpenTime < m_dMoldOpenTime_max)  
    {
        m_dMoldOpenTime += m_dMoldOpenTime_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dMoldOpenTime > m_dMoldOpenTime_min)  
    {
        m_dMoldOpenTime -= m_dMoldOpenTime_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dMoldOpenTime);
	GetDlgItem(IDC_EDIT_MOLDOPEN_TIME)->SetWindowText(strTemp); 

	InitCycleTime();
	InitResidenceTime();
}
	
void CMDXProcessPage::InitCycleTime()
{
	m_dCycleTime = m_dInjectionTime + m_dPackTime + m_dCoolTime + m_dMoldOpenTime;

	CString strTemp("");
	strTemp.Format("%.1f", m_dCycleTime);
	GetDlgItem(IDC_EDIT_CYCLE_TIME)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitResidenceTime()
{
	double hrV = DataCenter::getInstance().GetHotRunnerVolume();
	m_dResidenceTime = (hrV+m_dPartVolume+m_dColdRunnerVolume)
						/(m_dPartVolume+m_dColdRunnerVolume)
						/m_dVolumeExpansion*m_dCycleTime/60;
	
	CString strTemp("");
	strTemp.Format("%.1f", m_dResidenceTime);
	GetDlgItem(IDC_EDIT_RESIDENCE_TIME)->SetWindowText(strTemp);
}

void CMDXProcessPage::InitVP()
{
	//從資料中心拿資料
	m_dDiaScrew = DataCenter::getInstance().GetDiaScrew();

	//更新顯示(VP切換位置)
	m_dVP = m_dDiaScrew * 0.25;
	m_dVP_step = m_dVP * 0.01;
	m_dVP_max = m_dVP * 1.1;
	m_dVP_min = m_dVP * 0.9;

	CString strTemp("");
	strTemp.Format("%.1f", m_dVP);
	GetDlgItem(IDC_EDIT_VP)->SetWindowText(strTemp);

	//計算螺桿截面積 (cm^2)
	m_dAreaScrew = 3.1415926 * m_dDiaScrew * m_dDiaScrew / 4 / 100;
}

void CMDXProcessPage::OnDeltaposSpinVP(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-bigger(預設值的1%, 0.1) 
	//至多調整+-10%

	if (m_dVP_step < 0.1)
	{
		m_dVP_step = 0.1;
	}

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dVP < m_dVP_max)  
    {
        m_dVP += m_dVP_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dVP > m_dVP_min)  
    {
        m_dVP -= m_dVP_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dVP);
	GetDlgItem(IDC_EDIT_VP)->SetWindowText(strTemp); 
	SetProfileFill();
	SetProfilePack();
}

void CMDXProcessPage::InitInjectionPressure()
{
	//從資料中心拿資料
	m_dMachinePressure = DataCenter::getInstance().GetMaxInjectionPressure();

	//更新顯示(射出壓力)
	m_dInjectionPressure = m_dMachinePressure*0.8;	
	m_dInjectionPressure_step = m_dInjectionPressure * 0.01;
	m_dInjectionPressure_max = m_dInjectionPressure * 1.1;
	m_dInjectionPressure_min = m_dInjectionPressure * 0.9;

	CString strTemp("");
	strTemp.Format("%.1f", m_dInjectionPressure);
	GetDlgItem(IDC_EDIT_INJECTION_PRESSURE)->SetWindowText(strTemp); 
}

void CMDXProcessPage::OnDeltaposSpinInjectionPressure(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-預設值的1%
	//至多調整+-10%

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dInjectionPressure < m_dInjectionPressure_max)  
    {
        m_dInjectionPressure += m_dInjectionPressure_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dInjectionPressure > m_dInjectionPressure_min)  
    {
        m_dInjectionPressure -= m_dInjectionPressure_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dInjectionPressure);
	GetDlgItem(IDC_EDIT_INJECTION_PRESSURE)->SetWindowText(strTemp); 
	//DataCenter::getInstance().SetMaxInjectionPressure(m_dInjectionPressure);
	//SetProfilePack();
}

void CMDXProcessPage::InitVolumeExpansion()
{
	if (m_iMaterialSel != 2) //PC+Fiber or PC+ABS or ABS:非結晶型 
	{
		m_dVolumeExpansion = 1.1;
	}
	else //PA:結晶型
	{
		m_dVolumeExpansion = 1.3;
	}
}

void CMDXProcessPage::InitFillTime()
{
	//從資料中心拿資料
	m_iMaterialSel = DataCenter::getInstance().GetMaterialSel();
	m_dPartVolume = DataCenter::getInstance().GetPartVolume();
	m_dColdRunnerVolume = DataCenter::getInstance().GetColdRunnerVolume();
	m_iGateNumber = DataCenter::getInstance().GetGateNumber();

	//更新顯示(充填時間)
	m_dInjectionTime = InjectionTimeLookUpTable();
	m_dInjectionTime_step = m_dInjectionTime * 0.01;
	m_dInjectionTime_max = m_dInjectionTime * 1.1;
	m_dInjectionTime_min = m_dInjectionTime * 0.9;

	CString strTemp("");
	strTemp.Format("%.1f", m_dInjectionTime);
	GetDlgItem(IDC_EDIT_FILLINT_TIME)->SetWindowText(strTemp); 
}

void CMDXProcessPage::OnDeltaposSpinFillTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-bigger(1%, 0.1)
	//至多調整+-10%

	if (m_dInjectionTime_step < 0.1)
	{
		m_dInjectionTime_step = 0.1;
	}

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dInjectionTime < m_dInjectionTime_max)  
    {
        m_dInjectionTime += m_dInjectionTime_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dInjectionTime > m_dInjectionTime_min)  
    {
        m_dInjectionTime -= m_dInjectionTime_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dInjectionTime);
	GetDlgItem(IDC_EDIT_FILLINT_TIME)->SetWindowText(strTemp); 
	
	SetProfileFill();
	InitCycleTime();
	InitResidenceTime();
}

void CMDXProcessPage::InitPackTime()
{
	//從資料中心拿資料
	double gate_thickness = DataCenter::getInstance().GetGateThickness();
	m_dMachinePressure = DataCenter::getInstance().GetMaxInjectionPressure();
	m_dPackTime = gate_thickness * (1+2*gate_thickness);
	m_dPackTime_step = m_dPackTime * 0.01;
	m_dPackTime_max = m_dPackTime * 1.5;
	m_dPackTime_min = m_dPackTime * 1.0;
		
	//更新顯示(保壓時間)
	CString strTemp("");
	strTemp.Format("%.1f", m_dPackTime);
	GetDlgItem(IDC_EDIT_PACKING_TIME)->SetWindowText(strTemp); 
}

double CMDXProcessPage::InjectionTimeLookUpTable()
{
	std::vector<double> LowVis  (10, 0);    // 10 double with value 0
	std::vector<double> MidVis  (LowVis);	// a copy of LowVis
	std::vector<double> HighVis (LowVis);   

	LowVis[0] = (0.2+0.4) / 2;
	LowVis[1] = (0.4+0.5) / 2;
	LowVis[2] = (0.5+0.6) / 2;
	LowVis[3] = (0.6+0.8) / 2;
	LowVis[4] = (0.8+1.2) / 2;
	LowVis[5] = (1.2+1.8) / 2;
	LowVis[6] = (1.8+2.6) / 2;
	LowVis[7] = (2.6+3.5) / 2;
	LowVis[8] = (3.5+4.6) / 2;
	LowVis[9] = (4.6+6.5) / 2;

	MidVis[0] = (0.25+0.5) / 2;
	MidVis[1] = (0.5+0.6) / 2;
	MidVis[2] = (0.6+0.75) / 2;
	MidVis[3] = (0.75+1.0) / 2;
	MidVis[4] = (1.0+1.5) / 2;
	MidVis[5] = (1.5+2.2) / 2;
	MidVis[6] = (2.2+3.2) / 2;
	MidVis[7] = (3.2+4.4) / 2;
	MidVis[8] = (4.4+6.0) / 2;
	MidVis[9] = (6.0+8.0) / 2;

	HighVis[0] = (0.3+0.6) / 2;
	HighVis[1] = (0.6+0.75) / 2;
	HighVis[2] = (0.75+0.9) / 2;
	HighVis[3] = (0.9+1.2) / 2;
	HighVis[4] = (1.2+1.8) / 2;
	HighVis[5] = (1.8+2.7) / 2;
	HighVis[6] = (2.7+4.0) / 2;
	HighVis[7] = (4.0+5.4) / 2;
	HighVis[8] = (5.4+7.2) / 2;
	HighVis[9] = (7.2+9.5) / 2;

	// part volume + cold runner volume = plasticizing volume 塑化體積
	// 若為多點進澆，則單一澆口分配到的塑化體積才用於查表 (塑化體積/澆口數量)
	double plastic_volume = (m_dPartVolume + m_dColdRunnerVolume) / m_iGateNumber;
	int idxV = 0;
	if (plastic_volume < 8)
	{
		idxV = 0;
	}
	else if (plastic_volume < 15)
	{
		idxV = 1;
	}
	else if (plastic_volume < 30)
	{
		idxV = 2;
	}
	else if (plastic_volume < 50)
	{
		idxV = 3;
	}
	else if (plastic_volume < 80)
	{
		idxV = 4;
	}
	else if (plastic_volume < 120)
	{
		idxV = 5;
	}
	else if (plastic_volume < 180)
	{
		idxV = 6;
	}
	else if (plastic_volume < 250)
	{
		idxV = 7;
	}
	else if (plastic_volume < 350)
	{
		idxV = 8;
	}
	else //plasticizing volume >= 350
	{
		idxV = 9;
	}

	// material type
	if (m_iMaterialSel == 0) //PC+Fiber:high viscosity
	{
		return HighVis[idxV];
	}
	else if (m_iMaterialSel == 1) //PC+ABS:midium viscosity
	{
		return MidVis[idxV];
	}
	else //PA:low viscosity
	{
		return LowVis[idxV];
	}
}

void CMDXProcessPage::InitComboProcessFill()
{
	CString strFillType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_FILLING_SECTION))->ResetContent();
	strFillType = "1";
	((CComboBox*)GetDlgItem(IDC_COMBO_FILLING_SECTION))->AddString(strFillType); 
	strFillType = "3";
	((CComboBox*)GetDlgItem(IDC_COMBO_FILLING_SECTION))->AddString(strFillType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_FILLING_SECTION))->SetCurSel(0);
	m_iFillSel = 0; //單段充填
	/*m_iMachineSel = 0;
	SetMachineData();*/
}

void CMDXProcessPage::InitComboProcessPack()
{
	CString strPackType("");
	((CComboBox*)GetDlgItem(IDC_COMBO_PACKING_SECTION))->ResetContent();
	strPackType = "1";
	((CComboBox*)GetDlgItem(IDC_COMBO_PACKING_SECTION))->AddString(strPackType); 
	strPackType = "2";
	((CComboBox*)GetDlgItem(IDC_COMBO_PACKING_SECTION))->AddString(strPackType); 

	((CComboBox*)GetDlgItem(IDC_COMBO_PACKING_SECTION))->SetCurSel(0);
	m_iPackSel = 0; //單段保壓
	/*m_iMachineSel = 0;
	SetMachineData();*/
}

void CMDXProcessPage::CalculateFillSpeed()
{
	//從資料中心拿資料
	m_dColdRunnerVolume = DataCenter::getInstance().GetColdRunnerVolume();
	m_dMaxScrewStroke = DataCenter::getInstance().GetMaxScrewStroke();

	if (m_iFillSel == 0) //單段充填
	{
		m_dFillSpeed_single = 10*(m_dPartVolume+m_dColdRunnerVolume)*m_dVolumeExpansion
								/m_dInjectionTime/m_dAreaScrew;
		m_dScrewStroke_single = m_dFillSpeed_single*m_dInjectionTime+m_dVP;
	}
	else //三段充填
	{
		//第一.二.三段螺桿行程距離
		double dScrew_1 = 10 * m_dColdRunnerVolume*m_dVolumeExpansion/m_dAreaScrew;
		double dScrew_2 = 10 * 0.95*m_dPartVolume*m_dVolumeExpansion/m_dAreaScrew;
		double dScrew_3 = 10 * 0.05*m_dPartVolume*m_dVolumeExpansion/m_dAreaScrew;

		//第一.二.三段速度
		m_dFillSpeed_multi_1 = m_iSpeedRatio_1/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));
		m_dFillSpeed_multi_2 = m_iSpeedRatio_2/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));
		m_dFillSpeed_multi_3 = m_iSpeedRatio_3/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));

		//第一.二.三段螺桿位置
		m_dScrewStroke_1 = m_dVP + dScrew_1 + dScrew_2 + dScrew_3;
		m_dScrewStroke_2 = m_dVP + dScrew_2 + dScrew_3;
		m_dScrewStroke_3 = m_dVP + dScrew_3;
	}
}

void CMDXProcessPage::SetProfileFill()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_FILLING)->GetWindowRect(&rect);
	GetDlgItem(IDC_STATIC_FILLING)->ScreenToClient(&rect) ;
	
	m_profileF.CreateChart(rect,GetDlgItem(IDC_STATIC_FILLING));
	m_profileF.SetProfileType(1);	//0:純線段 1:填滿
	m_profileF.SetXAxisDrawingMode(1);	//0:左小右大 1:左大右小
	m_profileF.SetXAxisCaption(_T("螺桿位置 (mm)"));
	m_profileF.SetYAxisCaption(_T("射出速度 (mm/s)"));
	m_profileF.SetReadOnly(true);
	m_profileF.SetColorForBk(RGB( 255,255,255 ) );  //背景顏色
	m_profileF.SetVPSwitchLocation(m_dVP); //VP位置
	m_profileF.SetProfileColor( RGB(0,255,0));  //多段線的顏色

	m_profileF.RemoveAllData();
	CalculateFillSpeed();

	//TRACE("%lf", m_dVP);

	//加入資料
	if (m_iFillSel == 0) //單段充填
	{
		m_profileF.SetXMinMaxValue(m_dVP, m_dScrewStroke_single);  //X軸上下限
		m_profileF.SetYMinMaxValue(0,m_dFillSpeed_single*1.2);  //Y軸上下限

		m_profileF.AddXYData(m_dScrewStroke_single,m_dFillSpeed_single);
		m_profileF.AddXYData(m_dVP,m_dFillSpeed_single);
	}
	else //三段充填
	{
		m_profileF.SetXMinMaxValue(m_dVP, m_dScrewStroke_1);  //X軸上下限
		//Y軸上下限
		if (m_iSpeedRatio_1 >= m_iSpeedRatio_2 && m_iSpeedRatio_1 >= m_iSpeedRatio_3)
		{
			m_profileF.SetYMinMaxValue(0,m_dFillSpeed_multi_1*1.2);
		}
		else if (m_iSpeedRatio_2 >= m_iSpeedRatio_1 && m_iSpeedRatio_2 >= m_iSpeedRatio_3)
		{
			m_profileF.SetYMinMaxValue(0,m_dFillSpeed_multi_2*1.2);
		}
		else
		{
			m_profileF.SetYMinMaxValue(0,m_dFillSpeed_multi_3*1.2);
		}

		m_profileF.AddXYData(m_dScrewStroke_1,m_dFillSpeed_multi_1);
		m_profileF.AddXYData(m_dScrewStroke_2,m_dFillSpeed_multi_1); //SetProfileType(1)
		m_profileF.AddXYData(m_dScrewStroke_2,m_dFillSpeed_multi_2);
		m_profileF.AddXYData(m_dScrewStroke_3,m_dFillSpeed_multi_2); //SetProfileType(1)
		m_profileF.AddXYData(m_dScrewStroke_3,m_dFillSpeed_multi_3);
		m_profileF.AddXYData(m_dVP,m_dFillSpeed_multi_3);
	}

	m_profileF.Invalidate(TRUE);
}

void CMDXProcessPage::SetProfilePack()
{
	CRect rect;
	GetDlgItem(IDC_STATIC_PACKING)->GetWindowRect(&rect);
	GetDlgItem(IDC_STATIC_PACKING)->ScreenToClient(&rect) ;
	
	m_profileP.CreateChart(rect,GetDlgItem(IDC_STATIC_PACKING) );
	m_profileP.SetProfileType(1);	//0:純線段 1:填滿
	m_profileP.SetXAxisDrawingMode(0);	//0:右畫到左 1:左畫到右
	m_profileP.SetXAxisCaption(_T("時間 (sec)"));
	m_profileP.SetYAxisCaption(_T("保壓壓力 (MPa)"));
	m_profileP.SetReadOnly(true);
	m_profileP.SetColorForBk(RGB( 255,255,255 ) );  //背景顏色
	m_profileP.SetVPSwitchLocation(m_dVP); //VP位置
	m_profileP.SetProfileColor( RGB(0,0,255));  //多段線的顏色
	
	m_profileP.RemoveAllData();

	//TRACE("%d\n", m_iPackPressurePercent_1);

	m_profileP.SetXMinMaxValue(0,m_dPackTime);
	m_profileP.SetYMinMaxValue(0,m_dMachinePressure);

	//加入資料
	if (m_iPackSel == 0) //單段保壓 
	{
		//TRACE("%lf\n", m_iPackPressurePercent_1);

		m_profileP.AddXYData(m_dPackTime, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
		m_profileP.AddXYData(0, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
	}
	else //二段保壓 
	{
		double ratio_1 = (double)m_iPackTimeRatio_1 / (m_iPackTimeRatio_1+m_iPackTimeRatio_2);
		double ratio_2 = (double)m_iPackTimeRatio_2 / (m_iPackTimeRatio_1+m_iPackTimeRatio_2);

		m_profileP.AddXYData(m_dPackTime, (m_iPackPressurePercent_2*0.01)*m_dMachinePressure);
		m_profileP.AddXYData(ratio_1*m_dPackTime, (m_iPackPressurePercent_2*0.01)*m_dMachinePressure);
		m_profileP.AddXYData(ratio_1*m_dPackTime, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
		m_profileP.AddXYData(0, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
	}

	m_profileP.Invalidate(TRUE);
}

// test button
void CMDXProcessPage::OnBnClickedButton1()
{
	m_profileP.RemoveAllData();
	m_profileP.AddXYData(150,40);
	m_profileP.AddXYData(30,20);
	m_profileP.AddXYData(15,90);
	m_profileP.AddXYData(0,0);
	m_profileP.SetXMinMaxValue(0,250);
	m_profileP.SetYMinMaxValue(0,123);
	m_profileP.Invalidate(TRUE);
}

void CMDXProcessPage::OnCbnSelchangeComboFillingSection()
{
	if (m_iFillSel == 0)
	{
		m_iFillSel = 1;

		GetDlgItem(IDC_STATIC_FILLINGSPEED)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_3)->EnableWindow(TRUE);
	}
	else
	{
		m_iFillSel = 0;

		GetDlgItem(IDC_STATIC_FILLINGSPEED)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_FILLINGSPEED_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_FILLINGSPEED_3)->EnableWindow(FALSE);
	}

	m_profileF.RemoveAllData();
	SetProfileFill();
}

void CMDXProcessPage::OnCbnSelchangeComboPackingSection()
{
	if (m_iPackSel == 0)
	{
		m_iPackSel = 1;

		GetDlgItem(IDC_EDIT_PACKINGPRESSURE_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_PACKINGPRESSURE_2)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_PACKINGTIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PACKINGTIME_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PACKINGTIME_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_PACKINGTIME_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPIN_PACKINGTIME_2)->EnableWindow(TRUE);
	}
	else
	{
		m_iPackSel = 0;

		GetDlgItem(IDC_EDIT_PACKINGPRESSURE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_PACKINGPRESSURE_2)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_PACKINGTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PACKINGTIME_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PACKINGTIME_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_PACKINGTIME_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPIN_PACKINGTIME_2)->EnableWindow(FALSE);
	}

	m_profileP.RemoveAllData();
	SetProfilePack();
}


void CMDXProcessPage::OnBnClickedButtonVpInfo()
{
	MessageBox(_T("射出機從[速度控制]切換為[壓力控制]之螺桿位置，單位 mm\n"
				"(預設為25%螺桿直徑)"), 
				_T("VP 切換位置 (VP switch-over)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonInjectionPressureInfo()
{
	MessageBox(_T("射出作動的設定壓力上限，單位 MPa\n"
				"(預設為80%機台上限)"), 
				_T("射出壓力 (injection pressure)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonFillintTimeInfo()
{
	MessageBox(_T("預估充填時間，單位 sec\n"
				"(依[塑化體積]與[材料種類]估算而得)"), 
				_T("充填時間 (filling time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonFillingSectionInfo()
{
	MessageBox(_T("可選擇[單段充填]或[三段充填]，\n"
				"[三段充填]預設速度比為 2:4:1，\n"
				"分別充填[冷流道體積]、[95% 產品體積]、[5% 產品體積]"), 
				_T("充填段數 (filling section)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingSectionInfo()
{
	MessageBox(_T("可選擇[單段保壓]或[二段保壓]，\n"
				"[二段保壓]預設保壓時間比為 1:1，\n"
				"預設保壓壓力分別為[70% 機台最大射壓]、[40% 機台最大射壓]"), 
				_T("保壓段數 (packing section)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonCoolingTimeInfo()
{
	MessageBox(_T("從[保壓結束]到成型料溫已冷卻至[頂出溫度]的時間，單位 sec\n"
				"(依[產品最大厚度]估算而得)"), 
				_T("冷卻時間 (cooling time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonMoldopenTimeInfo()
{
	MessageBox(_T("開模、塑件頂出與關模所需的開模時間，單位 sec\n"
				"(預設為 5.0 秒)"), 
				_T("開模時間 (mold-open time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonCycleTimeInfo()
{
	MessageBox(_T("一次射出成型所需時間，單位 sec\n"
				"([充填時間]+[保壓時間]+[冷卻時間]+[開模時間])"), 
				_T("成型周期 (cycle time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonResidenceTimeInfo()
{
	MessageBox(_T("塑料從熱澆道入口到澆口擠出前，在料管內滯留的時間，單位 min"), 
				_T("料管滯留時間 (residence time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingTimeInfo()
{
	MessageBox(_T("預估保壓時間，單位 sec\n"
				"(依[產品平均厚度]估算[澆口固化時間]而得)"), 
				_T("保壓時間 (packing time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnDeltaposSpinPackingTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-bigger(1%, 0.1)
	//至多調整+50%

	if (m_dPackTime_step < 0.1)
	{
		m_dPackTime_step = 0.1;
	}

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dPackTime < m_dPackTime_max)  
    {
        m_dPackTime += m_dPackTime_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dPackTime > m_dPackTime_min)  
    {
        m_dPackTime -= m_dPackTime_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dPackTime);
	GetDlgItem(IDC_EDIT_PACKING_TIME)->SetWindowText(strTemp); 
	
	InitCoolTime();
	SetProfilePack();
	//InitCycleTime(); //cool+pack=equal
	//InitResidenceTime();
}

void CMDXProcessPage::OnDeltaposSpinCoolingTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以+-bigger(1%, 0.1)
	//至多調整+50%

	if (m_dCoolTime_step < 0.1)
	{
		m_dCoolTime_step = 0.1;
	}

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_dCoolTime < m_dCoolTime_max)  
    {
        m_dCoolTime += m_dCoolTime_step;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_dCoolTime > m_dCoolTime_min)  
    {
        m_dCoolTime -= m_dCoolTime_step;
    }

    CString strTemp("");
	strTemp.Format("%.1f", m_dCoolTime);
	GetDlgItem(IDC_EDIT_COOLING_TIME)->SetWindowText(strTemp); 
	
	InitCycleTime();
	InitResidenceTime();
}

void CMDXProcessPage::OnDeltaposSpinFillingspeed1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-1
	//調整範圍 1~10

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_1 < 10)  
    {
        m_iSpeedRatio_1 += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iSpeedRatio_1 > 1)  
    {
        m_iSpeedRatio_1 -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iSpeedRatio_1);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_1)->SetWindowText(strTemp); 
	
	SetProfileFill();
}

void CMDXProcessPage::OnDeltaposSpinFillingspeed2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-1
	//調整範圍 1~10

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_2 < 10)  
    {
        m_iSpeedRatio_2 += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iSpeedRatio_1 > 1)  
    {
        m_iSpeedRatio_2 -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iSpeedRatio_2);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_2)->SetWindowText(strTemp); 
	
	SetProfileFill();
}

void CMDXProcessPage::OnDeltaposSpinFillingspeed3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-1
	//調整範圍 1~10

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_3 < 10)  
    {
        m_iSpeedRatio_3 += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iSpeedRatio_3 > 1)  
    {
        m_iSpeedRatio_3 -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iSpeedRatio_3);
	GetDlgItem(IDC_EDIT_FILLINGSPEED_3)->SetWindowText(strTemp); 
	
	SetProfileFill();
}

void CMDXProcessPage::OnDeltaposSpinPackingpressure1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-5
	//調整範圍 30~100

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iPackPressurePercent_1 < 100)  
    {
        m_iPackPressurePercent_1 += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iPackPressurePercent_1 > 30)  
    {
        m_iPackPressurePercent_1 -= 5;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iPackPressurePercent_1);
	GetDlgItem(IDC_EDIT_PACKINGPRESSURE_1)->SetWindowText(strTemp); 

	//確認[第二段保壓壓力]沒有超過[第一段-10]
	if ((m_iPackPressurePercent_1 - 10) < m_iPackPressurePercent_2)
	{
		m_iPackPressurePercent_2 = m_iPackPressurePercent_1 - 10;

		strTemp.Format("%d", m_iPackPressurePercent_2);
		GetDlgItem(IDC_EDIT_PACKINGPRESSURE_2)->SetWindowText(strTemp);
	}
	
	SetProfilePack();
}

void CMDXProcessPage::OnDeltaposSpinPackingpressure2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-5
	//調整範圍 10~(第一段保壓壓力-10)

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iPackPressurePercent_2 < (m_iPackPressurePercent_1-10))  
    {
        m_iPackPressurePercent_2 += 5;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iPackPressurePercent_2 > 10)  
    {
        m_iPackPressurePercent_2 -= 5;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iPackPressurePercent_2);
	GetDlgItem(IDC_EDIT_PACKINGPRESSURE_2)->SetWindowText(strTemp); 
	
	SetProfilePack();
}

void CMDXProcessPage::OnDeltaposSpinPackingtime1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-1
	//調整範圍 1~10

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iPackTimeRatio_1 < 10)  
    {
        m_iPackTimeRatio_1 += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iPackTimeRatio_1 > 1)  
    {
        m_iPackTimeRatio_1 -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iPackTimeRatio_1);
	GetDlgItem(IDC_EDIT_PACKINGTIME_1)->SetWindowText(strTemp); 
	
	SetProfilePack();
}

void CMDXProcessPage::OnDeltaposSpinPackingtime2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//按一次箭頭可以 +-1
	//調整範圍 1~10

	//向上箭頭
	if(pNMUpDown->iDelta == -1 && m_iPackTimeRatio_2 < 10)  
    {
        m_iPackTimeRatio_2 += 1;
    }
	//向下箭頭
    else if(pNMUpDown->iDelta == 1 && m_iPackTimeRatio_2 > 1)  
    {
        m_iPackTimeRatio_2 -= 1;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iPackTimeRatio_2);
	GetDlgItem(IDC_EDIT_PACKINGTIME_2)->SetWindowText(strTemp); 
	
	SetProfilePack();
}

void CMDXProcessPage::OnBnClickedButtonPackingPressurePercentInfo()
{
	MessageBox(_T("[保壓壓力]占[機台最大射壓]之百分比，單位 %"), 
				_T("保壓壓力比 (packing pressure percentage)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingTimeRatioInfo()
{
	MessageBox(_T("[二段保壓]之間的時間分配比例"), 
				_T("保壓時間比 (packing time ratio)"), 
      MB_OK | MB_ICONINFORMATION);
}
