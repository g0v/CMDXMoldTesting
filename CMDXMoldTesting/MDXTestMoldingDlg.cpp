// MDXTestMoldingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXTestMoldingDlg.h"
#include "afxdialogex.h"
#include "DataCenter.h"


enum {MDXProductPage=0, MDXProcessPage};
// CMDXTestMoldingDlg dialog

IMPLEMENT_DYNAMIC(CMDXTestMoldingDlg, CDialog)

CMDXTestMoldingDlg::CMDXTestMoldingDlg(CWnd* pParent /*=NULL*/ )
	: CDialog(CMDXTestMoldingDlg::IDD, pParent)
	,m_iCurrentPage(0)
	//,m_dDiaScrew(0.f)
{
	 m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMDXTestMoldingDlg::~CMDXTestMoldingDlg()
{
}

void CMDXTestMoldingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABMOLDING, m_tab);
}


BEGIN_MESSAGE_MAP(CMDXTestMoldingDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABMOLDING, &CMDXTestMoldingDlg::OnTcnSelchangeTabmolding)
END_MESSAGE_MAP()


// CMDXTestMoldingDlg message handlers
void CMDXTestMoldingDlg::Init()
{
	//MessageBox(_T("本程式意在幫助現場試模人員在相關經驗不足的情況下，\n"
	//				"填入基本產品資料便可得出[第一次試模]建議成型條件，\n"
	//				"不保證為最佳解。"), _T("電腦試模表輔助程式 (ver.02)"), 
 //     MB_OK | MB_ICONINFORMATION);
}
void CMDXTestMoldingDlg::CreateTab()
{
	//tab頁面建立
	m_tab.InsertItem( 0, _T("參數設定") );
	//m_tab.InsertItem( 1, _T("機台") );
	//m_tab.InsertItem( 2, _T("材料") );
	m_tab.InsertItem( 1, _T("成型條件") );

	m_ProductPage.Create( IDD_PAGE_PRODUCT, &m_tab );
	//m_MachinePage.Create( IDD_PAGE_MACHINE, &m_tab);
	//m_MaterialPage.Create( IDD_PAGE_MATERIAL, &m_tab);
	m_ProcessPage.Create( IDD_PAGE_PROCESS, &m_tab);

	//讓TAB外觀不會遮住頁面
	CRect rect;
	m_tab.GetClientRect(rect);
	rect.top += 22;
	rect.bottom -= 5;
	rect.left += 1;
	rect.right -= 5;

	//移動頁面
	m_ProductPage.MoveWindow(&rect);
	//m_MachinePage.MoveWindow(&rect);
	//m_MaterialPage.MoveWindow(&rect);
	m_ProcessPage.MoveWindow(&rect);

	//將個頁面加入至container
	m_pTestMoldingDlg[0] = &m_ProductPage;
	//m_pTestMoldingDlg[1] = &m_MachinePage;
	//m_pTestMoldingDlg[2] = &m_MaterialPage;
	m_pTestMoldingDlg[1] = &m_ProcessPage;

	//顯示頁面  第一次開始顯示產品頁面
	m_pTestMoldingDlg[0]->ShowWindow( SW_SHOW );
	//m_pTestMoldingDlg[1]->ShowWindow( SW_HIDE );
	//m_pTestMoldingDlg[2]->ShowWindow( SW_HIDE );
	m_pTestMoldingDlg[1]->ShowWindow( SW_HIDE );
}
void CMDXTestMoldingDlg::FreeMemory()
{

}

BOOL CMDXTestMoldingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	Init();

	CreateTab();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMDXTestMoldingDlg::OnTcnSelchangeTabmolding(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	switch(m_iCurrentPage)
	{
	case 0: //產品
		{
			//離開此頁時更新資訊
			m_ProductPage.UpdateAllData();
			m_ProcessPage.InitFillTime();
			m_ProcessPage.InitVP();
			m_ProcessPage.InitInjectionPressure();
			m_ProcessPage.SetProfileFill();
			m_ProcessPage.SetProfilePack();
			m_ProcessPage.InitCoolTime();
			m_ProcessPage.InitCycleTime();
			m_ProcessPage.InitResidenceTime();

			if( !m_ProductPage.UpdateData())
			{
				m_tab.SetCurSel(m_iCurrentPage);
				return;
			}
		}
		break;
	//case 1: //機台
	//	{
	//		//離開此頁時更新資訊
	//		m_MachinePage.UpdateAllData();
	//		m_ProcessPage.InitVP();
	//		m_ProcessPage.InitInjectionPressure();
	//		m_ProcessPage.SetProfileFill();
	//		m_ProcessPage.SetProfilePack();

	//		if( !m_MachinePage.UpdateData())
	//		{
	//			m_tab.SetCurSel(m_iCurrentPage);
	//			return;
	//		}
	//	}
	//	break;
	//case 2: //材料
	//	{
	//		//離開此頁時更新資訊
	//		m_MaterialPage.UpdateAllData();
	//		m_ProcessPage.InitFillTime();
	//		m_ProcessPage.SetProfileFill();
	//		m_ProcessPage.SetProfilePack();
	//		m_ProcessPage.InitCycleTime();
	//		m_ProcessPage.InitResidenceTime();

	//		if( !m_MaterialPage.UpdateData())
	//		{
	//			m_tab.SetCurSel(m_iCurrentPage);
	//			return;
	//		}
	//	}
	//	break;
	case 1: //成型
		{
			if( !m_ProcessPage.UpdateData())
			{
				m_tab.SetCurSel(m_iCurrentPage);
				return;
			}
		}
		break;
	}
	//if(m_iCurrentPage == 0 )
	//{
	//	if( !m_ProductPage.UpdateData())
	//	{
	//		m_tab.SetCurSel(0);
	//		return;
	//	}

	//	//m_ProductPage
	//}

	m_pTestMoldingDlg[m_iCurrentPage]->ShowWindow(SW_HIDE);
	m_iCurrentPage = m_tab.GetCurSel();
	m_pTestMoldingDlg[m_iCurrentPage]->ShowWindow(SW_SHOW);

	//只有"成型"頁可以按[提交]
	if(m_iCurrentPage == 1)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
	}
}

void CMDXTestMoldingDlg::UpDateAllPage()
{
	////MDXProductPage=0, MDXMachinePage, MDXMaterialPage, MDXProcessPage

	//int iCurrentPage = m_tab.GetCurSel();
	//switch(iCurrentPage)
	//{
	//case MDXProductPage:
	//	{
	//		if( !m_ProductPage.UpdateData())
	//		{
	//			m_tab.SetCurSel(iCurrentPage);
	//			return;
	//		}
	//	}
	//	break;
	//case MDXMachinePage:
	//	{

	//	}
	//	break;
	//case MDXMaterialPage:
	//	{

	//	}
	//	break;
	//case MDXProcessPage:
	//	{

	//	}
	//	break;
	//}
}
CMDXProductPage* CMDXTestMoldingDlg::GetProductPagePtr()
{
	return &m_ProductPage;
}

//CMDXMachinePage* CMDXTestMoldingDlg::GetMachinePagePtr()
//{
//	return &m_MachinePage;
//}
//
//CMDXMaterialPage* CMDXTestMoldingDlg::GetMaterialPagePtr()
//{
//	return &m_MaterialPage;
//}

CMDXProcessPage* CMDXTestMoldingDlg::GetProcessPagePtr()
{
	return &m_ProcessPage;
}

//void CMDXTestMoldingDlg::OnOK()
//{
//	UpDateAllPage();

//}