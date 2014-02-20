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
	BOOL CheckInputValue( CDataExchange *pDX, UINT nEditID, double dVlaue );
	BOOL CheckPartThickness(CDataExchange *pDX, UINT nEditID, double part, double max);

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//CEdit m_cEditPartVolume;
	//CSliderCtrl m_SectionSlider;

	//afx_msg void OnEnKillfocusEditPartVolume();

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
public:
	afx_msg void OnEnChangeEditPartVolume();
	afx_msg void OnEnChangeEditColdRunnerVolume();
	afx_msg void OnEnChangeEditPartThickness();
};
