#pragma once

#include"MDXProductPage.h"
#include"MDXMachinePage.h"
#include"MDXMaterialPage.h"
#include"MDXProcessPage.h"
#include "MDXAllMoldTestingData.h"
// CMDXTestMoldingDlg dialog

#define PAGESIZE 4  //�����Ӽ�

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
	void Init();  //��l�Ƥ��e
	void CreateTab(); // 
	void FreeMemory();  //�O��������

private:
	CDialog* m_pTestMoldingDlg[PAGESIZE];  //container
	CTabCtrl m_tab;
	CMDXProductPage m_ProductPage;  //���~����
	CMDXMachinePage m_MachinePage; //���x����
	CMDXMaterialPage m_MaterialPage; //���ƭ���
	CMDXProcessPage m_ProcessPage; // ��������

	CMDXMoldTestingData m_pMoldTestingData;//�Ҧ���Ʀs���
private:
	int m_iCurrentPage;  //��e�������w

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTabmolding(NMHDR *pNMHDR, LRESULT *pResult);
	double m_dDiaScrew;
};
