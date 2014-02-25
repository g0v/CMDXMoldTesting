#pragma once


// CMDXProductPage dialog

class CMDXProductPage : public CDialog
{
	DECLARE_DYNAMIC(CMDXProductPage)

public:
	CMDXProductPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXProductPage();

// Dialog Data
	enum { IDD = IDD_PAGE_PRODUCT };


public:
	BOOL UpdatePageData(); 
	void UpdateAllData();

	void SetVolumeData(double dValue)			{ m_dVolumeData = dValue;};
	void SetColdRunnerVolumeData(double dValue) { m_dColdRunnerVolumeData = dValue;};
	void SetHotRunnerVolumeData(double dValue)	{ m_dHotRunnerVolumeData = dValue;};
	void SetPlasticVolumeData(double dValue)	{ m_dPlasticVolumeData = dValue;};
	void SetGateThicknessData(double dValue)	{ m_dGateThicknessData = dValue;};
	void SetPartThicknessData(double dValue)	{ m_dPartThicknessData = dValue;};
	void SetMaxPartThicknessData(double dValue) { m_dMaxPartThicknessData = dValue;};
	double GetVolumeData()				{ return m_dVolumeData;};
	double GetColdRunnerVolumeData()	{ return m_dColdRunnerVolumeData;};
	double GetHotRunnerVolumeData()		{ return m_dHotRunnerVolumeData;};
	double GetPlasticVolumeData()		{ return m_dPlasticVolumeData;};
	double GetGateThicknessData()		{ return m_dGateThicknessData;};
	double GetPartThicknessData()		{ return m_dPartThicknessData;};
	double GetMaxPartThicknessData()	{ return m_dMaxPartThicknessData;};

	void SetClampingForceData( double dValue ) {m_dClampingForce = dValue;};
	void SetScrewDiamData( double dValue ) {m_dScrewDiam = dValue;};
	void SetMaxStrokeData( double dValue  ) {m_dMaxStroke = dValue;};
	void SetInjectionVolumeData( double dValue ) {m_dInjectionVolume = dValue;};
	void SetMaxInjectionVolumeData( double dValue ) {m_dMaxInjectionVolume = dValue;};
	void SetMaxInjectionVelocityData( double dValue ) {m_dMaxInjectionVelocity = dValue;};
	void SetMaxInjectionPressureData( double dValue ) {m_dMaxInjectionPressure = dValue;};
	double GetClampingForceData() { return m_dClampingForce;};
	double GetScrewDiamData() {return m_dScrewDiam;};
	double GetMaxStrokeData() {return m_dMaxStroke;};
	double GetInjectionVolumeData() {return m_dInjectionVolume;};
	double GetMaxInjectionVolumeData() {return m_dMaxInjectionVolume;};
	double GetMaxInjectionVelocityData() {return m_dMaxInjectionVelocity;};
	double GetMaxInjectionPressureData() {return m_dMaxInjectionPressure;};

	void SetMaxMeltTemperature( double dValue )	{ m_dMaxMeltTemp =  dValue; };
	void SetMinMeltTemperature( double dValue )	{ m_dMinMeltTemp =  dValue; };
	void SetMaxMoldTemperature( double dValue ) { m_dMaxMoldTemp =  dValue; };
	void SetMinMoldTemperature( double dValue )	{ m_dMinMoldTemp =  dValue; };
	void SetMeltTemperature( double dValue )	{ m_dMeltTemp =  dValue; };
	void SetMoldTemperatureCore( double dValue )	{ m_dMoldTempCore =  dValue; };
	void SetMoldTemperatureCavity( double dValue )	{ m_dMoldTempCavity =  dValue; };
	void SetBarrelTemperatureFirst( double dValue )	{ m_dBarrelTempFirst =  dValue; };
	void SetBarrelTemperatureSecond( double dValue )	{ m_dBarrelTempSecond =  dValue; };
	void SetBarrelTemperatureThird( double dValue )	{ m_dBarrelTempThird =  dValue; };
	void SetBarrelTemperatureSlope( double dValue )	{ m_dBarrelTempSlope =  dValue; };
	double GetMaxMeltTemperature()	{ return m_dMaxMeltTemp; };
	double GetMinMeltTemperature()	{ return m_dMinMeltTemp; };
	double GetMaxMoldTemperature()	{ return m_dMaxMoldTemp; };
	double GetMinMoldTemperature()	{ return m_dMinMoldTemp; };
	double GetMeltTemperature()	{ return m_dMeltTemp; };
	double GetMoldTemperatureCore()	{ return m_dMoldTempCore; };
	double GetMoldTemperatureCavity()	{ return m_dMoldTempCavity; };
	double GetBarrelTemperatureFirst()	{ return m_dBarrelTempFirst; };
	double GetBarrelTemperatureSecond()	{ return m_dBarrelTempSecond; };
	double GetBarrelTemperatureThird()	{ return m_dBarrelTempThird; };
	double GetBarrelTemperatureSlope()	{ return m_dBarrelTempSlope; };

private:
	void InitEditData();
	BOOL UpDateEditData();

	BOOL IsValidateData(CDataExchange *pDX);
	BOOL IsVolumeValidate( CDataExchange *pDX );
    BOOL IsColdRunnerVolumeValidate( CDataExchange *pDX );
    BOOL IsHotRunnerVolumeValidate( CDataExchange *pDX );
	BOOL IsPlasticVolumeValidate( CDataExchange *pDX );
	BOOL IsGateThicknessValidate( CDataExchange *pDX );
	BOOL IsPartThicknessValidate( CDataExchange *pDX );
	BOOL IsMaxPartThicknessValidate( CDataExchange *pDX );
	BOOL IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue);
	void ShowWarningMessage(CDataExchange *pDX, UINT nEditID, CString strMsg);
	BOOL CheckInputValue( CDataExchange *pDX, UINT nEditID, double dVlaue ); //check >= 0
	BOOL CheckInputValueNotZero(CDataExchange *pDX, UINT nEditID, double dValue); //check != 0
	BOOL CheckPlasticVolumeValue(CDataExchange *pDX, UINT nEditID, double dValue);
	BOOL CheckPartThickness(CDataExchange *pDX, UINT nEditID, double part, double max);

	void InitComboMachineTon();
	//void InitComboMachineGrade();
	void SetMachineData();
	BOOL IsClampingForceValidate( CDataExchange *pDX );
	BOOL IsScrewDiamValidate( CDataExchange *pDX );
	BOOL IsMaxStrokeValidate( CDataExchange *pDX );
	BOOL IsInjectionVolumeValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionVolumeValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionVelocityValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionPressureValidate( CDataExchange *pDX );

	void InitComboMaterialData();
	void SetTemperatureData();
	BOOL CheckMeltMinMax( CDataExchange *pDX, UINT nEditID, double melt, double min, double max );
	BOOL CheckMoldMinMax( CDataExchange *pDX, UINT nEditID, double mold, double min, double max );
	BOOL IsMaxMeltTemperature( CDataExchange *pDX ); 
	BOOL IsMinMeltTemperature( CDataExchange *pDX );
	BOOL IsMeltTemperature( CDataExchange *pDX );
	BOOL IsMaxMoldTemperature( CDataExchange *pDX ); 
	BOOL IsMinMoldTemperature( CDataExchange *pDX );
	BOOL IsMoldTemperatureCore( CDataExchange *pDX );
	BOOL IsMoldTemperatureCavity( CDataExchange *pDX );

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//CEdit m_cEditPartVolume;
	//CSliderCtrl m_SectionSlider;

	//afx_msg void OnEnKillfocusEditPartVolume();
	CComboBox m_cMaterialType;

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCheckEditData;

	double m_dVolumeData;
	double m_dColdRunnerVolumeData;
	double m_dHotRunnerVolumeData;
	double m_dPlasticVolumeData;
	double m_dGateThicknessData;
	double m_dPartThicknessData;
	double m_dMaxPartThicknessData;

	int m_iMachineSel;
	//bool m_bCheckEditData;
	double m_dClampingForce;
	double m_dScrewDiam;
	double m_dMaxStroke;
	double m_dInjectionVolume;
	double m_dMaxInjectionVolume;
	double m_dMaxInjectionVelocity;
	double m_dMaxInjectionPressure;

	int m_iMaterialSel;
	//bool m_bCheckEditData;
	double m_dMaxMeltTemp;
	double m_dMinMeltTemp;
	double m_dMaxMoldTemp;
	double m_dMinMoldTemp;
	double m_dMeltTemp;
	double m_dMoldTempCore;
	double m_dMoldTempCavity;
	double m_dBarrelTempFirst;
	double m_dBarrelTempSecond;
	double m_dBarrelTempThird;
	double m_dBarrelTempSlope;

public:
	afx_msg void OnEnChangeEditPartVolume();
	afx_msg void OnEnChangeEditColdRunnerVolume();
	afx_msg void OnEnChangeEditPartThickness();
	afx_msg void OnEnChangeEditMaxPartThickness();
	afx_msg void OnEnChangeEditHrVolume();
	afx_msg void OnBnClickedButtonVolumeInfo();
	afx_msg void OnBnClickedButtonCrVolumeInfo();
	afx_msg void OnBnClickedButtonHrVolumeInfo();
	afx_msg void OnBnClickedButtonPlasticVolumeInfo();
	afx_msg void OnBnClickedButtonPartThicknessInfo();
	afx_msg void OnBnClickedButtonMaxPartThicknessInfo();
	afx_msg void OnBnClickedButtonGateThicknessInfo();

	afx_msg void OnCbnSelchangeComboMachineTon();
	afx_msg void OnCbnSelchangeComboMaterial();
	afx_msg void OnEnChangeEditMoldTemperature();
	afx_msg void OnEnChangeEditMeltTemperature();
	afx_msg void OnBnClickedButtonMeltTemperatureInfo();
	afx_msg void OnBnClickedButtonBarrelTemperatureFirstInfo();
	afx_msg void OnBnClickedButtonBarrelTemperatureSecondInfo();
	afx_msg void OnBnClickedButtonBarrelTemperatureThirdInfo();
	afx_msg void OnBnClickedButtonMoldTemperatureCoreInfo();
	afx_msg void OnBnClickedButtonMoldTemperatureCavityInfo();
	afx_msg void OnBnClickedButtonMeltTemperatureLimitInfo();
	afx_msg void OnBnClickedButtonMoldTemperatureLimitInfo();
	afx_msg void OnDeltaposSpinMeltTemperature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBarrelTemperatureFirst(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBarrelTemperatureSecond(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinBarrelTemperatureThird(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMoldTemperatureCore(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinMoldTemperatureCavity(NMHDR *pNMHDR, LRESULT *pResult);
};
