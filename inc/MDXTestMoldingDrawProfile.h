#pragma once
#include "MDXMachineChart.h"

class AFX_EXT_CLASS CMDXTestMoldingDrawProfile :
	public CMDXMachineChart
{
public:
	CMDXTestMoldingDrawProfile(void);
	~CMDXTestMoldingDrawProfile(void);
	

public:
	
	virtual BOOL CreateChart(CRect &rect, CWnd *pParent);
	virtual void SetProfileType(int iType);
	virtual void SetXAxisDrawingMode(const int iMode)   { m_iXDrawingMode = iMode; };
	virtual void SetXAxisCaption(CString str);
	virtual void SetYAxisCaption(CString str);
	virtual void SetReadOnly(BOOL bReadOnly)    { m_bReadOnly = bReadOnly; }; // 2009-03-13
	virtual void SetColorForBk(COLORREF crColor) { m_bkColor = crColor;};
	virtual void SetVPSwitchLocation( double dValue) { m_dVPSwitchLoca = dValue;}; 
	virtual void SetProfileColor(COLORREF crColor) { m_bProfileColor = crColor;};
	virtual void AddXYData(const double dx, const double dy, int nItem = 0);
	void RemoveAllData();
    void SetXMinMaxValue(const double dmin, const double dmax); 
    void SetYMinMaxValue(const double dmin, const double dmax); 
private:
	bool Initialize(); 
	virtual void DrawGridline(CDC *pDC); 
	 virtual void DrawValueText(CDC *pDC); // 2008-10-07
private:
	HINSTANCE m_hExists;
	bool m_bisValid;
};

