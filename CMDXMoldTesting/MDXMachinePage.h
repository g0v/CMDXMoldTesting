#pragma once


// CMDXMachinePage dialog

class CMDXMachinePage : public CDialog
{
	DECLARE_DYNAMIC(CMDXMachinePage)

public:
	CMDXMachinePage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXMachinePage();

// Dialog Data
	enum { IDD = IDD_PAGE_MACHINE };

public:
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
	void UpdateAllData();

private:
	void InitComboMachineProducer();
	void InitComboMachineGrade();
	void SetMachineData();
	BOOL IsValidateData(CDataExchange *pDX);
	BOOL IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue);
	//void ShowWarningMessage(CDataExchange *pDX, UINT nEditID, CString strMsg);
	BOOL CheckInputValue( CDataExchange *pDX, UINT nEditID, double dVlaue );
	BOOL IsClampingForceValidate( CDataExchange *pDX );
	BOOL IsScrewDiamValidate( CDataExchange *pDX );
	BOOL IsMaxStrokeValidate( CDataExchange *pDX );
	BOOL IsInjectionVolumeValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionVolumeValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionVelocityValidate( CDataExchange *pDX );
	BOOL IsMaxInjectionPressureValidate( CDataExchange *pDX );

protected:

	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnCbnSelchangeComboMachineProducer();
	afx_msg void OnCbnSelchangeComboMachineGrade();
	DECLARE_MESSAGE_MAP()

private:
	int m_iMachineSel;
	bool m_bCheckEditData;
	double m_dClampingForce;
	double m_dScrewDiam;
	double m_dMaxStroke;
	double m_dInjectionVolume;
	double m_dMaxInjectionVolume;
	double m_dMaxInjectionVelocity;
	double m_dMaxInjectionPressure;
	CWnd* m_pParent;
};
