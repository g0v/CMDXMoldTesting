// MDXTestMoldingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXTestMoldingDlg.h"
#include "afxdialogex.h"
#include "DataCenter.h"

enum {MDXProductPage=0, MDXMachinePage, MDXMaterialPage, MDXProcessPage};
// CMDXTestMoldingDlg dialog

IMPLEMENT_DYNAMIC(CMDXTestMoldingDlg, CDialog)

CMDXTestMoldingDlg::CMDXTestMoldingDlg(CWnd* pParent /*=NULL*/ )
	: CDialog(CMDXTestMoldingDlg::IDD, pParent)
	,m_iCurrentPage(0)
	,m_dDiaScrew(0.f)
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

}
void CMDXTestMoldingDlg::CreateTab()
{
	//tab�����إ�
	m_tab.InsertItem( 0, _T("���~") );
	m_tab.InsertItem( 1, _T("���x") );
	m_tab.InsertItem( 2, _T("����") );
	m_tab.InsertItem( 3, _T("����") );

	m_ProductPage.Create( IDD_PAGE_PRODUCT, &m_tab );
	m_MachinePage.Create( IDD_PAGE_MACHINE, &m_tab);
	m_MaterialPage.Create( IDD_PAGE_MATERIAL, &m_tab);
	m_ProcessPage.Create( IDD_PAGE_PROCESS, &m_tab);

	//��TAB�~�[���|�B����
	CRect rect;
	m_tab.GetClientRect(rect);
	rect.top += 22;
	rect.bottom -= 5;
	rect.left += 1;
	rect.right -= 5;

	//���ʭ���
	m_ProductPage.MoveWindow(&rect);
	m_MachinePage.MoveWindow(&rect);
	m_MaterialPage.MoveWindow(&rect);
	m_ProcessPage.MoveWindow(&rect);

	//�N�ӭ����[�J��container
	m_pTestMoldingDlg[0] = &m_ProductPage;
	m_pTestMoldingDlg[1] = &m_MachinePage;
	m_pTestMoldingDlg[2] = &m_MaterialPage;
	m_pTestMoldingDlg[3] = &m_ProcessPage;

	//��ܭ���  �Ĥ@���}�l��ܲ��~����
	m_pTestMoldingDlg[0]->ShowWindow( SW_SHOW );
	m_pTestMoldingDlg[1]->ShowWindow( SW_HIDE );
	m_pTestMoldingDlg[2]->ShowWindow( SW_HIDE );
	m_pTestMoldingDlg[3]->ShowWindow( SW_HIDE );
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
	case 0: //���~
		{
			//���}�����ɧ�s��T
			m_ProductPage.UpdateAllData();
			m_ProcessPage.InitFillTime();
			m_ProcessPage.SetProfileFill();
			m_ProcessPage.SetProfilePack();

			if( !m_ProductPage.UpdateData())
			{
				m_tab.SetCurSel(m_iCurrentPage);
				return;
			}
		}
		break;
	case 1: //���x
		{
			//���}�����ɧ�s��T
			m_MachinePage.UpdateAllData();
			m_ProcessPage.InitVP();
			m_ProcessPage.InitInjectionPressure();
			m_ProcessPage.SetProfileFill();
			m_ProcessPage.SetProfilePack();

			if( !m_MachinePage.UpdateData())
			{
				m_tab.SetCurSel(m_iCurrentPage);
				return;
			}
		}
		break;
	case 2: //����
		{
			//���}�����ɧ�s��T
			m_MaterialPage.UpdateAllData();
			m_ProcessPage.InitFillTime();
			m_ProcessPage.SetProfileFill();
			m_ProcessPage.SetProfilePack();

			if( !m_MaterialPage.UpdateData())
			{
				m_tab.SetCurSel(m_iCurrentPage);
				return;
			}
		}
		break;
	case 3: //����
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

	//�u��"����"���i�H��[����]
	if(m_iCurrentPage == 3)
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

CMDXMachinePage* CMDXTestMoldingDlg::GetMachinePagePtr()
{
	return &m_MachinePage;
}

CMDXMaterialPage* CMDXTestMoldingDlg::GetMaterialPagePtr()
{
	return &m_MaterialPage;
}

CMDXProcessPage* CMDXTestMoldingDlg::GetProcessPagePtr()
{
	return &m_ProcessPage;
}

//void CMDXTestMoldingDlg::OnOK()
//{
//	UpDateAllPage();

//}