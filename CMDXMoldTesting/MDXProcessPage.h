#pragma once

#include"..\inc\MDXTestMoldingDrawProfile.h"
// CMDXProcessPage dialog

class CMDXProcessPage : public CDialog
{
	DECLARE_DYNAMIC(CMDXProcessPage)

public:
	CMDXProcessPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXProcessPage();

// Dialog Data
	enum { IDD = IDD_PAGE_PROCESS };

protected:
	
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void InitComboProcessFill();
	void InitComboProcessPack();
	void CalculateFillSpeed();

	double InjectionTimeLookUpTable();

private:
	int m_iFillSel;
	int m_iPackSel;
	int m_iMaterialSel;
	double m_dVolumeExpansion;
	int m_iGateNumber;

	CWnd* m_pParent;
	CMDXTestMoldingDrawProfile m_profileF;
	CMDXTestMoldingDrawProfile m_profileP;
	double m_dDiaScrew;
	double m_dAreaScrew;
	double m_dMaxScrewStroke;

	double m_dScrewStroke_single;
	double m_dScrewStroke_1;
	double m_dScrewStroke_2;
	double m_dScrewStroke_3;

	int m_iSpeedRatio_1;
	int m_iSpeedRatio_2;
	int m_iSpeedRatio_3;

	double m_dMachinePressure;

	int m_iPackPressurePercent_1;
	int m_iPackPressurePercent_2;
	int m_iPackTimeRatio_1;
	int m_iPackTimeRatio_2;

	double m_dPartVolume;
	double m_dColdRunnerVolume;

	double m_dVP;
	double m_dVP_step;
	double m_dVP_max;
	double m_dVP_min;

	double m_dInjectionPressure;
	double m_dInjectionPressure_step;
	double m_dInjectionPressure_max;
	double m_dInjectionPressure_min;

	double m_dInjectionTime; //filling time
	double m_dInjectionTime_step;
	double m_dInjectionTime_max;
	double m_dInjectionTime_min;

	double m_dPackTime;
	double m_dPackTime_step;
	double m_dPackTime_max;
	double m_dPackTime_min;

	double m_dFillSpeed_single;
	double m_dFillSpeed_multi_1;
	double m_dFillSpeed_multi_2;
	double m_dFillSpeed_multi_3;

	double m_dMoldOpenTime;
	double m_dMoldOpenTime_step;
	double m_dMoldOpenTime_max;
	double m_dMoldOpenTime_min;

	double m_dCoolTime;
	double m_dCoolTime_step;
	double m_dCoolTime_max;
	double m_dCoolTime_min;

	double m_dCycleTime;
	double m_dResidenceTime;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeComboFillingSection();
	afx_msg void OnCbnSelchangeComboPackingSection();
	void InitVP();
	void InitInjectionPressure();
	void InitFillTime();
	void InitPackTime();
	void InitVolumeExpansion();
	void SetProfileFill();
	void SetProfilePack();
	void InitCoolTime();
	void InitMoldOpenTime();
	void InitCycleTime();
	void InitResidenceTime();
	void InitFillSpeedRatio();
	void InitPackPressurePercent();
	void InitPackTimeRatio();
	afx_msg void OnDeltaposSpinVP(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinInjectionPressure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinFillTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMoldopenTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonVpInfo();
	afx_msg void OnBnClickedButtonInjectionPressureInfo();
	afx_msg void OnBnClickedButtonFillintTimeInfo();
	afx_msg void OnBnClickedButtonFillingSectionInfo();
	afx_msg void OnBnClickedButtonPackingSectionInfo();
	afx_msg void OnBnClickedButtonCoolingTimeInfo();
	afx_msg void OnBnClickedButtonMoldopenTimeInfo();
	afx_msg void OnBnClickedButtonCycleTimeInfo();
	afx_msg void OnBnClickedButtonResidenceTimeInfo();
	afx_msg void OnBnClickedButtonPackingTimeInfo();
	afx_msg void OnDeltaposSpinPackingTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinCoolingTime(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinFillingspeed1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinFillingspeed2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinFillingspeed3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPackingpressure1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPackingpressure2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPackingtime1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPackingtime2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPackingPressurePercentInfo();
	afx_msg void OnBnClickedButtonPackingTimeRatioInfo();
};
