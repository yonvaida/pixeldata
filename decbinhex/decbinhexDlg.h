
// decbinhexDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CdecbinhexDlg dialog
class CdecbinhexDlg : public CDialogEx
{
// Construction
public:
	CdecbinhexDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DECBINHEX_DIALOG };
#endif

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
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

public:
	CString hexadecimal;
	CString binary;
	int integer;
	
	afx_msg void OnEnChangeEdit3();
	CString convertToHex(int number);
	CString convertToBin(int number);
	 
	afx_msg void OnLbnSelchangeList1();
	CListBox showList;
};
