#pragma once

#include<vector>

// CMDXMachineChart

class CMDXMachineChart : public CWnd
{
	DECLARE_DYNAMIC(CMDXMachineChart)

public:
	CMDXMachineChart();
	virtual ~CMDXMachineChart();


public:
	virtual BOOL CreateChart(CRect &rect, CWnd *pParent);


    // 0: Stepwise, 1: Polyline
    void SetProfileType(int iType);

	// 0: min -> max, 1: max -> min
    void SetXAxisDrawingMode(const int iMode)   { m_iXDrawingMode = iMode; }; // 2007-12-20
    const int GetXAxisDrawingMode()             { return m_iXDrawingMode; }; // 2007-12-20
	 void AddXYData(const double dx, const double dy, int nItem = 0);
    BOOL RemoveXYData(const int iIndex);
    void RemoveAllData();
	void SetParentWndPtr(CDialog *pWnd) { m_pParentWnd = pWnd; }; // 2008-10-07
	void SetColorForBk(COLORREF crColor) { m_bkColor = crColor;};
	void SetProfileColor(COLORREF crColor) { m_bProfileColor = crColor;};
	void SetVPSwitchLocation( double dValue) { m_dVPSwitchLoca = dValue;}; 
	double  GetVPSwitchLocation( ) { return m_dVPSwitchLoca;}; 
    void SetXAxisCaption(CString str);
    void SetYAxisCaption(CString str);
    void SetXMinValue(const double dmin); // 2007-11-21
    void SetXMaxValue(const double dmax); // 2007-11-21
    void SetYMinValue(const double dmin); // 2007-11-21
    void SetYMaxValue(const double dmax); // 2007-11-21
    void SetXMinMaxValue(const double dmin, const double dmax); // 2007-11-21
    void SetYMinMaxValue(const double dmin, const double dmax); // 2007-11-21
	//第二組資料
    void SetX2MinValue(const double dmin); // 2007-11-21
    void SetX2MaxValue(const double dmax); // 2007-11-21
    void SetY2MinValue(const double dmin); // 2007-11-21
    void SetY2MaxValue(const double dmax); // 2007-11-21
    void SetX2MinMaxValue(const double dmin, const double dmax); // 2007-11-21
    void SetY2MinMaxValue(const double dmin, const double dmax); // 2007-11-21
	void SetProfile2Color(COLORREF crColor) { m_bProfile2Color = crColor;};

    void SetReadOnly(BOOL bReadOnly)    { m_bReadOnly = bReadOnly; }; // 2009-03-13
    BOOL IsReadOnly()                   { return m_bReadOnly; }; // 2009-03-13

protected:
	virtual	void DrawChart(CDC *pDC); 
	virtual	 void DrawProfile(CDC *pDC); // 2008-10-07
    void DrawBackground(CDC *pDC); // 2008-10-07
	virtual void DrawChartBKColor(CDC *pDC);//2011-07-25
    void DrawXYCaption(CDC *pDC); // 2008-10-07
    virtual void DrawValueText(CDC *pDC); // 2008-10-07
	virtual void DrawGridline(CDC *pDC); // 2008-10-07
	void DrawFocusNode(CDC *pDC); // 2008-10-07
	virtual void DrawPolylineProfile(CDC *pDC); // 2008-10-07
    virtual void DrawStepwiseProfile(CDC *pDC); // 2008-10-07
    void DrawDragStepwiseProfile(CDC *pDC); // 2008-10-08
    void DrawDragPolylineProfile(CDC *pDC); // 2008-10-08
	void DrawMaxPressure(CDC *pDC); // 2008-10-08
	void DrawVPSwitchPosition(CDC *pDC);
	void DrawBasicProfile(CDC *pDC, std::vector<double> vXData, std::vector<double> vYData);
	virtual void DrawProifleData(CDC* pDC, std::vector<double> vXData, std::vector<double> vYData, int nItem,COLORREF color  );
	///<Color>
	COLORREF GetColorForBk( ) { return m_bkColor;};
	COLORREF GetColor(const int iIndex);

	///<Data Transfer>
    const int    DataToXAxis(const double dx);
    const int    DataToYAxis(const double dy);
    const double XAxisToData(const int x);
    const double YAxisToData(const int y);

	///<mouse event>
	BOOL IsLButtonDown()    { return m_bLButtonDown; }; // 2008-10-07
	BOOL HasMatchPoint(); // 2008-10-08
	 int GetCurrentPoint() { return m_iCurrentPoint; }; // 2008-10-08

	 ///<internal >
	 void Initialize();
	const int GetNodeCount(int nItem = 0);
    double GetPointXPos() { return m_dPointXPos; }; // 2008-10-07
    double GetPointYPos() { return m_dPointYPos; }; // 2008-10-07
	BOOL PtInChart(CPoint *pPt); // 2008-10-07
	BOOL SearchMatchPoint(CPoint *pPt); // 2008-10-07
	 BOOL IsMatchPos(const int iPos1, const int iPos2); // 2008-10-07
	 BOOL IsCrossPoint(const double dx, const double dy); // 2008-10-08


protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

protected:

	CRect   m_WndRect;
	CRect   m_Rect;
	CBitmap*    m_pOldChartBitmap; // 2008-10-07
	CBitmap     m_ChartBitmap; // 2008-10-07

	///<CDC>
	CDC         m_dcChartBitmap; // 2008-10-07

	///<Color>
	COLORREF m_bkColor;
	COLORREF m_bProfileColor;
	COLORREF m_bProfile2Color;
	///<Font>
	CFont m_XFont;
	CFont m_YFont;
	CFont m_ValueFont;
	///
    std::vector<double>    m_vXData;
    std::vector<double>    m_vYData;

	std::vector<double> m_vX2Data;
	std::vector<double> m_vY2Data;

	CString m_strXCaption;
    CString m_strYCaption;

    double  m_dXmin;
    double  m_dXmax;
    double  m_dYmin;
    double  m_dYmax;
    double  m_dXFactor;
    double  m_dYFactor;
    double  m_dPointXPos; // 2008-10-07
    double  m_dPointYPos; // 2008-10-07
	double m_dVPSwitchLoca;

	//second profile data
    double  m_dXmin2;
    double  m_dXmax2;
    double  m_dYmin2;
    double  m_dYmax2;

	int m_iXDrawingMode;
	int m_iProfileType;
	int     m_iCurrentPoint; // 2008-10-07
	int     m_iFinalPoint; // 2008-10-08

	BOOL    m_bLButtonDown; // 2008-10-07
	BOOL    m_bPointMatch; // 2008-10-07
	BOOL    m_bReadOnly; // 2009-03-13

	CDialog* m_pParentWnd;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


