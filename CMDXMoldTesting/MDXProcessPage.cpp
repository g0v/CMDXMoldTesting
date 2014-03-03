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
	//�w�]�t�פ� 2:4:1
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
	//�w�]���������O�� 70%:40%
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
	//�w�]�� 1:1
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

	//���@���b�Y�i�H+-bigger(�w�]�Ȫ�1%, 0.1) 
	//�ܦh�վ�+-10%

	if (m_dMoldOpenTime_step < 0.1)
	{
		m_dMoldOpenTime_step = 0.1;
	}

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dMoldOpenTime < m_dMoldOpenTime_max)  
    {
        m_dMoldOpenTime += m_dMoldOpenTime_step;
    }
	//�V�U�b�Y
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
	//�q��Ƥ��߮����
	m_dDiaScrew = DataCenter::getInstance().GetDiaScrew();

	//��s���(VP������m)
	m_dVP = m_dDiaScrew * 0.25;
	m_dVP_step = m_dVP * 0.01;
	m_dVP_max = m_dVP * 1.1;
	m_dVP_min = m_dVP * 0.9;

	CString strTemp("");
	strTemp.Format("%.1f", m_dVP);
	GetDlgItem(IDC_EDIT_VP)->SetWindowText(strTemp);

	//�p������I���n (cm^2)
	m_dAreaScrew = 3.1415926 * m_dDiaScrew * m_dDiaScrew / 4 / 100;
}

void CMDXProcessPage::OnDeltaposSpinVP(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//���@���b�Y�i�H+-bigger(�w�]�Ȫ�1%, 0.1) 
	//�ܦh�վ�+-10%

	if (m_dVP_step < 0.1)
	{
		m_dVP_step = 0.1;
	}

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dVP < m_dVP_max)  
    {
        m_dVP += m_dVP_step;
    }
	//�V�U�b�Y
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
	//�q��Ƥ��߮����
	m_dMachinePressure = DataCenter::getInstance().GetMaxInjectionPressure();

	//��s���(�g�X���O)
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

	//���@���b�Y�i�H+-�w�]�Ȫ�1%
	//�ܦh�վ�+-10%

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dInjectionPressure < m_dInjectionPressure_max)  
    {
        m_dInjectionPressure += m_dInjectionPressure_step;
    }
	//�V�U�b�Y
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
	if (m_iMaterialSel != 2) //PC+Fiber or PC+ABS or ABS:�D������ 
	{
		m_dVolumeExpansion = 1.1;
	}
	else //PA:������
	{
		m_dVolumeExpansion = 1.3;
	}
}

void CMDXProcessPage::InitFillTime()
{
	//�q��Ƥ��߮����
	m_iMaterialSel = DataCenter::getInstance().GetMaterialSel();
	m_dPartVolume = DataCenter::getInstance().GetPartVolume();
	m_dColdRunnerVolume = DataCenter::getInstance().GetColdRunnerVolume();
	m_iGateNumber = DataCenter::getInstance().GetGateNumber();

	//��s���(�R��ɶ�)
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

	//���@���b�Y�i�H+-bigger(1%, 0.1)
	//�ܦh�վ�+-10%

	if (m_dInjectionTime_step < 0.1)
	{
		m_dInjectionTime_step = 0.1;
	}

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dInjectionTime < m_dInjectionTime_max)  
    {
        m_dInjectionTime += m_dInjectionTime_step;
    }
	//�V�U�b�Y
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
	//�q��Ƥ��߮����
	double gate_thickness = DataCenter::getInstance().GetGateThickness();
	m_dMachinePressure = DataCenter::getInstance().GetMaxInjectionPressure();
	m_dPackTime = gate_thickness * (1+2*gate_thickness);
	m_dPackTime_step = m_dPackTime * 0.01;
	m_dPackTime_max = m_dPackTime * 1.5;
	m_dPackTime_min = m_dPackTime * 1.0;
		
	//��s���(�O���ɶ�)
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

	// part volume + cold runner volume = plasticizing volume �����n
	// �Y���h�I�i��A�h��@��f���t�쪺�����n�~�Ω�d�� (�����n/��f�ƶq)
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
	m_iFillSel = 0; //��q�R��
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
	m_iPackSel = 0; //��q�O��
	/*m_iMachineSel = 0;
	SetMachineData();*/
}

void CMDXProcessPage::CalculateFillSpeed()
{
	//�q��Ƥ��߮����
	m_dColdRunnerVolume = DataCenter::getInstance().GetColdRunnerVolume();
	m_dMaxScrewStroke = DataCenter::getInstance().GetMaxScrewStroke();

	if (m_iFillSel == 0) //��q�R��
	{
		m_dFillSpeed_single = 10*(m_dPartVolume+m_dColdRunnerVolume)*m_dVolumeExpansion
								/m_dInjectionTime/m_dAreaScrew;
		m_dScrewStroke_single = m_dFillSpeed_single*m_dInjectionTime+m_dVP;
	}
	else //�T�q�R��
	{
		//�Ĥ@.�G.�T�q�����{�Z��
		double dScrew_1 = 10 * m_dColdRunnerVolume*m_dVolumeExpansion/m_dAreaScrew;
		double dScrew_2 = 10 * 0.95*m_dPartVolume*m_dVolumeExpansion/m_dAreaScrew;
		double dScrew_3 = 10 * 0.05*m_dPartVolume*m_dVolumeExpansion/m_dAreaScrew;

		//�Ĥ@.�G.�T�q�t��
		m_dFillSpeed_multi_1 = m_iSpeedRatio_1/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));
		m_dFillSpeed_multi_2 = m_iSpeedRatio_2/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));
		m_dFillSpeed_multi_3 = m_iSpeedRatio_3/m_dInjectionTime
								*((dScrew_1/m_iSpeedRatio_1)+(dScrew_2/m_iSpeedRatio_2)+(dScrew_3/m_iSpeedRatio_3));

		//�Ĥ@.�G.�T�q�����m
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
	m_profileF.SetProfileType(1);	//0:�½u�q 1:��
	m_profileF.SetXAxisDrawingMode(1);	//0:���p�k�j 1:���j�k�p
	m_profileF.SetXAxisCaption(_T("�����m (mm)"));
	m_profileF.SetYAxisCaption(_T("�g�X�t�� (mm/s)"));
	m_profileF.SetReadOnly(true);
	m_profileF.SetColorForBk(RGB( 255,255,255 ) );  //�I���C��
	m_profileF.SetVPSwitchLocation(m_dVP); //VP��m
	m_profileF.SetProfileColor( RGB(0,255,0));  //�h�q�u���C��

	m_profileF.RemoveAllData();
	CalculateFillSpeed();

	//TRACE("%lf", m_dVP);

	//�[�J���
	if (m_iFillSel == 0) //��q�R��
	{
		m_profileF.SetXMinMaxValue(m_dVP, m_dScrewStroke_single);  //X�b�W�U��
		m_profileF.SetYMinMaxValue(0,m_dFillSpeed_single*1.2);  //Y�b�W�U��

		m_profileF.AddXYData(m_dScrewStroke_single,m_dFillSpeed_single);
		m_profileF.AddXYData(m_dVP,m_dFillSpeed_single);
	}
	else //�T�q�R��
	{
		m_profileF.SetXMinMaxValue(m_dVP, m_dScrewStroke_1);  //X�b�W�U��
		//Y�b�W�U��
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
	m_profileP.SetProfileType(1);	//0:�½u�q 1:��
	m_profileP.SetXAxisDrawingMode(0);	//0:�k�e�쥪 1:���e��k
	m_profileP.SetXAxisCaption(_T("�ɶ� (sec)"));
	m_profileP.SetYAxisCaption(_T("�O�����O (MPa)"));
	m_profileP.SetReadOnly(true);
	m_profileP.SetColorForBk(RGB( 255,255,255 ) );  //�I���C��
	m_profileP.SetVPSwitchLocation(m_dVP); //VP��m
	m_profileP.SetProfileColor( RGB(0,0,255));  //�h�q�u���C��
	
	m_profileP.RemoveAllData();

	//TRACE("%d\n", m_iPackPressurePercent_1);

	m_profileP.SetXMinMaxValue(0,m_dPackTime);
	m_profileP.SetYMinMaxValue(0,m_dMachinePressure);

	//�[�J���
	if (m_iPackSel == 0) //��q�O�� 
	{
		//TRACE("%lf\n", m_iPackPressurePercent_1);

		m_profileP.AddXYData(m_dPackTime, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
		m_profileP.AddXYData(0, (m_iPackPressurePercent_1*0.01)*m_dMachinePressure);
	}
	else //�G�q�O�� 
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
	MessageBox(_T("�g�X���q[�t�ױ���]������[���O����]�������m�A��� mm\n"
				"(�w�]��25%���쪽�|)"), 
				_T("VP ������m (VP switch-over)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonInjectionPressureInfo()
{
	MessageBox(_T("�g�X�@�ʪ��]�w���O�W���A��� MPa\n"
				"(�w�]��80%���x�W��)"), 
				_T("�g�X���O (injection pressure)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonFillintTimeInfo()
{
	MessageBox(_T("�w���R��ɶ��A��� sec\n"
				"(��[�����n]�P[���ƺ���]����ӱo)"), 
				_T("�R��ɶ� (filling time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonFillingSectionInfo()
{
	MessageBox(_T("�i���[��q�R��]��[�T�q�R��]�A\n"
				"[�T�q�R��]�w�]�t�פ� 2:4:1�A\n"
				"���O�R��[�N�y�D��n]�B[95% ���~��n]�B[5% ���~��n]"), 
				_T("�R��q�� (filling section)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingSectionInfo()
{
	MessageBox(_T("�i���[��q�O��]��[�G�q�O��]�A\n"
				"[�G�q�O��]�w�]�O���ɶ��� 1:1�A\n"
				"�w�]�O�����O���O��[70% ���x�̤j�g��]�B[40% ���x�̤j�g��]"), 
				_T("�O���q�� (packing section)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonCoolingTimeInfo()
{
	MessageBox(_T("�q[�O������]�즨���ƷŤw�N�o��[���X�ū�]���ɶ��A��� sec\n"
				"(��[���~�̤j�p��]����ӱo)"), 
				_T("�N�o�ɶ� (cooling time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonMoldopenTimeInfo()
{
	MessageBox(_T("�}�ҡB��󳻥X�P���ҩһݪ��}�Үɶ��A��� sec\n"
				"(�w�]�� 5.0 ��)"), 
				_T("�}�Үɶ� (mold-open time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonCycleTimeInfo()
{
	MessageBox(_T("�@���g�X�����һݮɶ��A��� sec\n"
				"([�R��ɶ�]+[�O���ɶ�]+[�N�o�ɶ�]+[�}�Үɶ�])"), 
				_T("�����P�� (cycle time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonResidenceTimeInfo()
{
	MessageBox(_T("��Ʊq����D�J�f���f���X�e�A�b�ƺޤ����d���ɶ��A��� min"), 
				_T("�ƺ޺��d�ɶ� (residence time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingTimeInfo()
{
	MessageBox(_T("�w���O���ɶ��A��� sec\n"
				"(��[���~�����p��]����[��f�T�Ʈɶ�]�ӱo)"), 
				_T("�O���ɶ� (packing time)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnDeltaposSpinPackingTime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//���@���b�Y�i�H+-bigger(1%, 0.1)
	//�ܦh�վ�+50%

	if (m_dPackTime_step < 0.1)
	{
		m_dPackTime_step = 0.1;
	}

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dPackTime < m_dPackTime_max)  
    {
        m_dPackTime += m_dPackTime_step;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H+-bigger(1%, 0.1)
	//�ܦh�վ�+50%

	if (m_dCoolTime_step < 0.1)
	{
		m_dCoolTime_step = 0.1;
	}

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_dCoolTime < m_dCoolTime_max)  
    {
        m_dCoolTime += m_dCoolTime_step;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-1
	//�վ�d�� 1~10

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_1 < 10)  
    {
        m_iSpeedRatio_1 += 1;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-1
	//�վ�d�� 1~10

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_2 < 10)  
    {
        m_iSpeedRatio_2 += 1;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-1
	//�վ�d�� 1~10

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iSpeedRatio_3 < 10)  
    {
        m_iSpeedRatio_3 += 1;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-5
	//�վ�d�� 30~100

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iPackPressurePercent_1 < 100)  
    {
        m_iPackPressurePercent_1 += 5;
    }
	//�V�U�b�Y
    else if(pNMUpDown->iDelta == 1 && m_iPackPressurePercent_1 > 30)  
    {
        m_iPackPressurePercent_1 -= 5;
    }

    CString strTemp("");
	strTemp.Format("%d", m_iPackPressurePercent_1);
	GetDlgItem(IDC_EDIT_PACKINGPRESSURE_1)->SetWindowText(strTemp); 

	//�T�{[�ĤG�q�O�����O]�S���W�L[�Ĥ@�q-10]
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

	//���@���b�Y�i�H +-5
	//�վ�d�� 10~(�Ĥ@�q�O�����O-10)

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iPackPressurePercent_2 < (m_iPackPressurePercent_1-10))  
    {
        m_iPackPressurePercent_2 += 5;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-1
	//�վ�d�� 1~10

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iPackTimeRatio_1 < 10)  
    {
        m_iPackTimeRatio_1 += 1;
    }
	//�V�U�b�Y
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

	//���@���b�Y�i�H +-1
	//�վ�d�� 1~10

	//�V�W�b�Y
	if(pNMUpDown->iDelta == -1 && m_iPackTimeRatio_2 < 10)  
    {
        m_iPackTimeRatio_2 += 1;
    }
	//�V�U�b�Y
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
	MessageBox(_T("[�O�����O]�e[���x�̤j�g��]���ʤ���A��� %"), 
				_T("�O�����O�� (packing pressure percentage)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProcessPage::OnBnClickedButtonPackingTimeRatioInfo()
{
	MessageBox(_T("[�G�q�O��]�������ɶ����t���"), 
				_T("�O���ɶ��� (packing time ratio)"), 
      MB_OK | MB_ICONINFORMATION);
}
