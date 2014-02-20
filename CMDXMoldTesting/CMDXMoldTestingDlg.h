
// CMDXMoldTestingDlg.h : header file
//

#pragma once


// CCMDXMoldTestingDlg dialog
class CCMDXMoldTestingDlg : public CDialogEx
{
// Construction
public:
	CCMDXMoldTestingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CMDXMOLDTESTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
