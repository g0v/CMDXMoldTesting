// MDXProdectPage.cpp : implementation file
//

#include "stdafx.h"
#include "CMDXMoldTesting.h"
#include "MDXProductPage.h"
#include "afxdialogex.h"
#include "MDXStringParser.h"
#include "MDXProductPageData.h"
#include "DataCenter.h"


// CMDXProductPage dialog

IMPLEMENT_DYNAMIC(CMDXProductPage, CDialog)

CMDXProductPage::CMDXProductPage(CWnd* pParent /*=NULL*/)
	: CDialog(CMDXProductPage::IDD, pParent)
, m_bCheckEditData(false)
, m_dVolumeData(0.)
, m_dColdRunnerVolumeData(0.)
, m_dHotRunnerVolumeData(0.)
, m_dPlasticVolumeData(0.)
, m_dGateThicknessData(0.)
, m_dPartThicknessData(0.)
, m_dMaxPartThicknessData(0.)
{

}

CMDXProductPage::~CMDXProductPage()
{
}

void CMDXProductPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	if( m_bCheckEditData )
	{
		IsValidateData( pDX );	
	}
}


BEGIN_MESSAGE_MAP(CMDXProductPage, CDialog)
	
	ON_EN_CHANGE(IDC_EDIT_VOLUME, &CMDXProductPage::OnEnChangeEditPartVolume)
	ON_EN_CHANGE(IDC_EDIT_CR_VOLUME, &CMDXProductPage::OnEnChangeEditColdRunnerVolume)
	ON_EN_CHANGE(IDC_EDIT_PART_THICKNESS, &CMDXProductPage::OnEnChangeEditPartThickness)
	ON_EN_CHANGE(IDC_EDIT_MAX_PART_THICKNESS, &CMDXProductPage::OnEnChangeEditMaxPartThickness)
	ON_EN_CHANGE(IDC_EDIT_HR_VOLUME, &CMDXProductPage::OnEnChangeEditHrVolume)
	ON_BN_CLICKED(IDC_BUTTON_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_CR_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonCrVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_HR_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonHrVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_PLASTIC_VOLUME_INFO, &CMDXProductPage::OnBnClickedButtonPlasticVolumeInfo)
	ON_BN_CLICKED(IDC_BUTTON_PART_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonPartThicknessInfo)
	ON_BN_CLICKED(IDC_BUTTON_MAX_PART_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonMaxPartThicknessInfo)
	ON_BN_CLICKED(IDC_BUTTON_GATE_THICKNESS_INFO, &CMDXProductPage::OnBnClickedButtonGateThicknessInfo)
END_MESSAGE_MAP()

//void CMDXProductPage::OnEnKillfocusEditPartVolume()
//{
//
//}

BOOL CMDXProductPage::OnInitDialog()
{
	InitEditData();
	m_bCheckEditData = true;
	return TRUE;
}
// CMDXProductPage message handlers

void CMDXProductPage::InitEditData()
{
	//CString strVolumeText("");
	//strVolumeText= "300";
	//GetDlgItem( IDC_EDIT_VOLUME )->SetWindowText(strVolumeText);	
	//((CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOLUME))->SetRange(0, 10000 );
	//(CSliderCtrl*)GetDlgItem(IDC_SLIDER_VOLUME))->SetBuddy(GetDlgItem(IDC_EDIT_VOLUME),0);

	// cold & hot runner volume default = 0
	GetDlgItem(IDC_EDIT_CR_VOLUME)->SetWindowText("0.00");
	SetColdRunnerVolumeData(0.0);
	GetDlgItem(IDC_EDIT_HR_VOLUME)->SetWindowText("0.00");
	SetHotRunnerVolumeData(0.0);

	////push cold runner volume to data center
	//DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
}

BOOL CMDXProductPage::UpdatePageData()
{
	BOOL bState = FALSE;
	if( !UpdateData())
	{
		return FALSE;
	}

	bState = UpDateEditData();

	return bState;

}

BOOL CMDXProductPage::IsValidateData(CDataExchange *pDX)
{
	//return true;	
	if( pDX == NULL )
    {
        return false;
    }
	     
    if( !IsVolumeValidate( pDX ) )				{ return FALSE; };
    if( !IsColdRunnerVolumeValidate( pDX ) )	{ return FALSE; };
    if( !IsHotRunnerVolumeValidate( pDX ) )     { return FALSE; };
	if( !IsPlasticVolumeValidate( pDX ) )		{ return FALSE; };
	if( !IsGateThicknessValidate( pDX ) )		{ return FALSE; };
	if( !IsPartThicknessValidate( pDX ) )		{ return FALSE; };
	if( !IsMaxPartThicknessValidate( pDX ) )    { return FALSE; };
        //
   return TRUE;
   
}

BOOL CMDXProductPage::IsVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetVolumeData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsColdRunnerVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_CR_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_CR_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_CR_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_CR_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetColdRunnerVolumeData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsHotRunnerVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_HR_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_HR_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_HR_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetHotRunnerVolumeData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsPlasticVolumeValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_PLASTIC_VOLUME)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_PLASTIC_VOLUME, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckPlasticVolumeValue( pDX, IDC_EDIT_PLASTIC_VOLUME, atof(strItem)))
	{
		return FALSE;
	}

	SetPlasticVolumeData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsGateThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_GATE_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_GATE_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_GATE_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_GATE_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	SetGateThicknessData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsPartThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_PART_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_PART_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	if( !CheckInputValueNotZero( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	CString strItem2("");
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strItem2);

	if( !CheckPartThickness( pDX, IDC_EDIT_PART_THICKNESS, atof(strItem), atof(strItem2)))
	{
		return FALSE;
	}

	SetPartThicknessData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsMaxPartThicknessValidate( CDataExchange *pDX )
{
	CString strItem("");
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strItem);
    
	if( !IsRealParse( pDX, IDC_EDIT_MAX_PART_THICKNESS, strItem ) )
    {
        return FALSE;
    }

	if( !CheckInputValue( pDX, IDC_EDIT_MAX_PART_THICKNESS, atof(strItem)))
	{
		return FALSE;
	}

	SetMaxPartThicknessData(atof(strItem));
	return TRUE;
}

BOOL CMDXProductPage::IsRealParse(CDataExchange *pDX, UINT nEditID, CString strValue)
{
    CMDXStringParser parser;

    if( !parser.IsRealParse( strValue ) )
    {
        CString strErrorMesg("");
		strErrorMesg = "請輸入數字";
		parser.ShowWarningMessage( pDX, nEditID,  strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );

        return FALSE;
    }

    return TRUE;
}

BOOL CMDXProductPage::CheckInputValue( CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue < 0 )
	{
		CString strErrorMesg("");
		strErrorMesg = "此設定值不能小於0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::CheckInputValueNotZero(CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue == 0 )
	{
		CString strErrorMesg("");
		strErrorMesg = "此設定值不能等於0";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::CheckPlasticVolumeValue(CDataExchange *pDX, UINT nEditID, double dValue)
{
	CMDXStringParser parser;
	if( dValue > 550 )
	{
		CString strErrorMesg("");
		strErrorMesg = "建議塑化體積需小於550";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::CheckPartThickness(CDataExchange *pDX, UINT nEditID, double part, double max)
{
	CMDXStringParser parser;
	
	if (part > max)
	{
		CString strErrorMesg("");
		strErrorMesg = "產品[平均肉厚]不可大於[最大肉厚]";
		parser.ShowWarningMessage( pDX, nEditID, strErrorMesg/*parser.GetTableString( AFX_IDP_PARSE_REAL )*/  );
	}
	return TRUE;
}

BOOL CMDXProductPage::UpDateEditData()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_VOLUME )->GetWindowText(strEditData);
	//m_cEditPartVolume.GetWindowTextW(strEditData);
	//::AfxMessageBox(strEditData);

	return TRUE;
}

void CMDXProductPage::UpdateAllData()
{		
	CString strTemp("");
	GetDlgItem(IDC_EDIT_VOLUME)->GetWindowText(strTemp);
	SetVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_CR_VOLUME)->GetWindowText(strTemp);
	SetColdRunnerVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_HR_VOLUME)->GetWindowText(strTemp);
	SetHotRunnerVolumeData(atof(strTemp));
	GetDlgItem(IDC_EDIT_GATE_THICKNESS)->GetWindowText(strTemp);
	SetGateThicknessData(atof(strTemp));
	GetDlgItem(IDC_EDIT_MAX_PART_THICKNESS)->GetWindowText(strTemp);
	SetMaxPartThicknessData(atof(strTemp));

	DataCenter::getInstance().SetPartVolume(GetVolumeData());
	DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
	DataCenter::getInstance().SetHotRunnerVolume(GetHotRunnerVolumeData());
	DataCenter::getInstance().SetGateThickness(GetGateThicknessData());
	DataCenter::getInstance().SetMaxPartThickness(GetMaxPartThicknessData());
}

void CMDXProductPage::OnEnChangeEditPartVolume()
{
	// 更新塑化體積
	CString strEditData("");
	GetDlgItem( IDC_EDIT_VOLUME )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	SetVolumeData(d);
	double modifiedPV = d + GetColdRunnerVolumeData();
	SetPlasticVolumeData(modifiedPV);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedPV);
	GetDlgItem( IDC_EDIT_PLASTIC_VOLUME )->SetWindowText(strTemp);

	//push part volume to data center
	DataCenter::getInstance().SetPartVolume(GetVolumeData());
}

void CMDXProductPage::OnEnChangeEditColdRunnerVolume()
{
	// 更新塑化體積
	CString strEditData("");
	GetDlgItem( IDC_EDIT_CR_VOLUME )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	SetColdRunnerVolumeData(d);
	double modifiedPV = GetVolumeData() + d;
	SetPlasticVolumeData(modifiedPV);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedPV);
	GetDlgItem( IDC_EDIT_PLASTIC_VOLUME )->SetWindowText(strTemp);

	//push cold runner volume to data center
	DataCenter::getInstance().SetColdRunnerVolume(GetColdRunnerVolumeData());
}

void CMDXProductPage::OnEnChangeEditPartThickness()
{
	// 更新澆口短邊肉厚
	CString strEditData("");
	GetDlgItem( IDC_EDIT_PART_THICKNESS )->GetWindowText(strEditData);
	double d = _tstof(strEditData);
	double modifiedGate = d *2 /3;
	SetGateThicknessData(modifiedGate);
	CString strTemp("");
	strTemp.Format("%.2f", modifiedGate);
	GetDlgItem( IDC_EDIT_GATE_THICKNESS )->SetWindowText(strTemp);

	//push gate thickness to data center
	DataCenter::getInstance().SetGateThickness(GetGateThicknessData());
}

void CMDXProductPage::OnEnChangeEditMaxPartThickness()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_MAX_PART_THICKNESS )->GetWindowText(strEditData);
	double t = _tstof(strEditData);
	SetMaxPartThicknessData(t);

	DataCenter::getInstance().SetMaxPartThickness(GetMaxPartThicknessData());
}

void CMDXProductPage::OnEnChangeEditHrVolume()
{
	CString strEditData("");
	GetDlgItem( IDC_EDIT_HR_VOLUME )->GetWindowText(strEditData);
	double HR = _tstof(strEditData);
	SetHotRunnerVolumeData(HR);

	DataCenter::getInstance().SetHotRunnerVolume(GetHotRunnerVolumeData());
}


void CMDXProductPage::OnBnClickedButtonVolumeInfo()
{
	MessageBox(_T("射出成型產品之體積，以 cc 計"), _T("產品體積 (product volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonCrVolumeInfo()
{
	MessageBox(_T("冷流道部分之體積，以 cc 計"), _T("冷流道體積 (cold runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonHrVolumeInfo()
{
	MessageBox(_T("熱流道部分之體積，以 cc 計"), _T("熱流道體積 (hot runner volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPlasticVolumeInfo()
{
	MessageBox(_T("產品體積 + 冷流道部分體積，建議 < 550 cc，以 cc 計"), _T("塑化體積 (plasticizing volume)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonPartThicknessInfo()
{
	MessageBox(_T("產品平均厚度，以 mm 計"), _T("產品平均肉厚 (product average thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonMaxPartThicknessInfo()
{
	MessageBox(_T("產品最大厚度，以 mm 計"), _T("產品最大肉厚 (product maximum thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}

void CMDXProductPage::OnBnClickedButtonGateThicknessInfo()
{
	MessageBox(_T("澆口短邊之厚度，預設值為 2/3 * 產品平均肉厚，以 mm 計"), _T("澆口短邊肉厚 (gate thickness)"), 
      MB_OK | MB_ICONINFORMATION);
}
