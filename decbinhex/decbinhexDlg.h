
// decbinhexDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "number.h"

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
	Number numberConverter;
	afx_msg void OnLbnSelchangeList1();
	CListBox showList;
	CListCtrl stringList;
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit1();
	
};
