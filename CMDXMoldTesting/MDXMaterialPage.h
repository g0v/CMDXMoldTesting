#pragma once


// CMDXMaterialPage dialog

class CMDXMaterialPage : public CDialog
{
	DECLARE_DYNAMIC(CMDXMaterialPage)

public:
	CMDXMaterialPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXMaterialPage();

// Dialog Data
	enum { IDD = IDD_PAGE_PRODUCT };

public:
	void SetMaxMeltTemperature( double dValue )	{ m_dMaxMeltTemp =  dValue; };
	void SetMinMeltTemperature( double dValue )	{ m_dMinMeltTemp =  dValue; };
	void SetMaxMoldTemperature( double dValue ) { m_dMaxMoldTemp =  dValue; };
	void SetMinMoldTemperature( double dValue )	{ m_dMinMoldTemp =  dValue; };
	void SetMeltTemperature( double dValue )	{ m_dMeltTemp =  dValue; };
	void SetMoldTemperature( double dValue )	{ m_dMoldTemp =  dValue; };
	double GetMaxMeltTemperature()	{ return m_dMaxMeltTemp; };
	double GetMinMeltTemperature()	{ return m_dMinMeltTemp; };
	double GetMaxMoldTemperature()	{ return m_dMaxMoldTemp; };
	double GetMinMoldTemperature()	{ return m_dMinMoldTemp; };
	double GetMeltTemperature()	{ return m_dMeltTemp; };
	double GetMoldTemperature()	{ return m_dMoldTemp; };
	void UpdateAllData();

private:
	void InitComboBoxData();
	void SetTemperatureData();
	BOOL IsValidateData(CDataExchange *pDX);
	BOOL IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue);
	BOOL CheckInputValue( CDataExchange *pDX, UINT nEditID, double dVlaue );
	BOOL CheckMeltMinMax( CDataExchange *pDX, UINT nEditID, double melt, double min, double max );
	BOOL CheckMoldMinMax( CDataExchange *pDX, UINT nEditID, double mold, double min, double max );
	BOOL IsMaxMeltTemperature( CDataExchange *pDX ); 
	BOOL IsMinMeltTemperature( CDataExchange *pDX );
	BOOL IsMeltTemperature( CDataExchange *pDX );
	BOOL IsMaxMoldTemperature( CDataExchange *pDX ); 
	BOOL IsMinMoldTemperature( CDataExchange *pDX );
	BOOL IsMoldTemperature( CDataExchange *pDX );

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
	double m_dMeltTemp;
	double m_dMoldTemp;
public:
	afx_msg void OnEnChangeEditMeltTemperature();
};
