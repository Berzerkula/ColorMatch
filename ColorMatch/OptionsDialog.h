#pragma once


// COptionsDialog dialog

class COptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(COptionsDialog)

public:
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionsDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OPTIONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
