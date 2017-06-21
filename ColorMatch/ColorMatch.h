
// ColorMatch.h : main header file for the ColorMatch application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CColorMatchApp:
// See ColorMatch.cpp for the implementation of this class
//

class CColorMatchApp : public CWinApp
{
public:
	CColorMatchApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CColorMatchApp theApp;
