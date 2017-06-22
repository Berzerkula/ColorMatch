// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ColorMatch.h"
#include "OptionsDialog.h"
#include "afxdialogex.h"


// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)

COptionsDialog::COptionsDialog(bool bRowColumn, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_ctrlStaticText1);
	DDX_Control(pDX, IDC_STATIC_STATIC_TEXT2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionsDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()


// COptionsDialog message handlers


void COptionsDialog::OnBnClickedButtonDefaults()
{
	//  Do things differently for the different dialogs
	if (m_bRowColumnDialog)
		m_nValue1 = m_nValue2 = 15; //  15x15 board
	else
		m_nValue1 = m_nValue2 = 35; //  35x35 blocks
									//  Have the controls updated to the new values
	UpdateData(false);
}


BOOL COptionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_bRowColumnDialog)
	{
		//  First update the title of the dialog
		SetWindowText(_T("Update Block Count"));
		//  Next change the static text labels
		m_ctrlStaticText1.SetWindowText(_T("Rows"));
		m_ctrlStaticText2.SetWindowText(_T("Columns"));
	}
	else
	{
		//  First update the title of the dialog
		SetWindowText(_T("Update Block Size"));
		//  Next change the static text labels
		m_ctrlStaticText1.SetWindowText(_T("Block Width"));
		m_ctrlStaticText2.SetWindowText(_T("Block Height"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
