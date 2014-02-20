#pragma once

#include"MDXProductPage.h"
#include"MDXMachinePage.h"
#include"MDXMaterialPage.h"
#include"MDXProcessPage.h"
#include "MDXAllMoldTestingData.h"
// CMDXTestMoldingDlg dialog

#define PAGESIZE 4  //頁面個數

class CMDXTestMoldingDlg : public CDialog
{
	DECLARE_DYNAMIC(CMDXTestMoldingDlg)

public:
	CMDXTestMoldingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMDXTestMoldingDlg();
	void UpDateAllPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_MOLDTESTINDLG };

public:
	CMDXProductPage* GetProductPagePtr();
	CMDXMachinePage* GetMachinePagePtr();
	CMDXMaterialPage* GetMaterialPagePtr();
	CMDXProcessPage* GetProcessPagePtr();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//void OnOK();
    //virtual void OnCancel() {};
	DECLARE_MESSAGE_MAP()
	HICON m_hIcon;

private:
	void Init();  //初始化內容
	void CreateTab(); // 
	void FreeMemory();  //記憶體釋放

private:
	CDialog* m_pTestMoldingDlg[PAGESIZE];  //container
	CTabCtrl m_tab;
	CMDXProductPage m_ProductPage;  //產品頁面
	CMDXMachinePage m_MachinePage; //機台頁面
	CMDXMaterialPage m_MaterialPage; //材料頁面
	CMDXProcessPage m_ProcessPage; // 成型頁面

	CMDXMoldTestingData m_pMoldTestingData;//所有資料存放區
private:
	int m_iCurrentPage;  //當前頁面指針

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabmolding(NMHDR *pNMHDR, LRESULT *pResult);
	double m_dDiaScrew;
};
