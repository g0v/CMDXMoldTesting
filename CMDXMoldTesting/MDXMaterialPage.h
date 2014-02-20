#pragma once


// CMDXMaterialPage dialog

class CMDXMaterialPage : public CDialog
{
	DECLARE_DYNAMIC(CMDXMaterialPage)

public:
	CMDXMaterialPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXMaterialPage();

// Dialog Data
	enum { IDD = IDD_PAGE_MATERIAL };

public:
	void SetMaxMeltTemperature( double dValue )	{ m_dMaxMeltTemp =  dValue; };
	void SetMinMeltTemperature( double dValue )	{ m_dMinMeltTemp =  dValue; };
	void SetMaxMoldTemperature( double dValue ) { m_dMaxMoldTemp =  dValue; };
	void SetMinMoldTemperature( double dValue )	{ m_dMinMoldTemp =  dValue; };
	double SetMaxMeltTemperature()	{ return m_dMaxMeltTemp; };
	double SetMinMeltTemperature()	{ return m_dMinMeltTemp; };
	double SetMaxMoldTemperature()	{ return m_dMaxMoldTemp; };
	double SetMinMoldTemperature()	{ return m_dMinMoldTemp; };
	void UpdateAllData();

private:
	void InitComboBoxData();
	void SetTemperatureData();
	BOOL IsValidateData(CDataExchange *pDX);
	BOOL IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue);
	BOOL CheckInputValue( CDataExchange *pDX, UINT nEditID, double dVlaue );
	BOOL IsMaxMeltTemperature( CDataExchange *pDX ); 
	BOOL IsMinMeltTemperature( CDataExchange *pDX );
	BOOL IsMaxMoldTemperature( CDataExchange *pDX ); 
	BOOL IsMinMoldTemperature( CDataExchange *pDX );

protected:

	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	afx_msg void OnCbnSelchangeComboMaterialType();

	CComboBox m_cMaterialType;
	DECLARE_MESSAGE_MAP()
private:
	int m_iMaterialSel;
	bool m_bCheckEditData;
	double m_dMaxMeltTemp;
	double m_dMinMeltTemp;
	double m_dMaxMoldTemp;
	double m_dMinMoldTemp;
};
