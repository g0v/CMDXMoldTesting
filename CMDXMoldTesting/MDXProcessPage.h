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
	void DrawFillCurve();
	void DrawPackCurve();
	afx_msg void OnPaint();
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

	double m_dMachinePressure;
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

	double m_dInjectionTime;
	double m_dInjectionTime_step;
	double m_dInjectionTime_max;
	double m_dInjectionTime_min;

	double m_dPackTime;

	double m_dFillSpeed_single;
	double m_dFillSpeed_multi_1;
	double m_dFillSpeed_multi_2;
	double m_dFillSpeed_multi_3;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeComboFillingSection();
	afx_msg void OnCbnSelchangeComboPackingSection();
	void InitVP();
	void InitInjectionPressure();
	void InitFillTime();
	void InitVolumeExpansion();
	void SetProfileFill();
	void SetProfilePack();
	afx_msg void OnDeltaposSpinVP(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinInjectionPressure(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinFillTime(NMHDR *pNMHDR, LRESULT *pResult);
};
