// OptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ColorMatch.h"
#include "OptionsDialog.h"
#include "afxdialogex.h"


// COptionsDialog dialog

IMPLEMENT_DYNAMIC(COptionsDialog, CDialog)

COptionsDialog::COptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
{

}

COptionsDialog::~COptionsDialog()
{
}

void COptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionsDialog, CDialog)
END_MESSAGE_MAP()


// COptionsDialog message handlers
