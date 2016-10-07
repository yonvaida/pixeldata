
// decbinhexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "decbinhex.h"
#include "decbinhexDlg.h"
#include "afxdialogex.h"
#include <string.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdecbinhexDlg dialog



CdecbinhexDlg::CdecbinhexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DECBINHEX_DIALOG, pParent)
	, hexadecimal(_T(""))
	, binary(_T(""))
	, integer(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdecbinhexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, hexadecimal);
	DDX_Text(pDX, IDC_EDIT4, binary);
	DDX_Text(pDX, IDC_EDIT3, integer);

	
	DDX_Control(pDX, IDC_LIST2, stringList);
}

BEGIN_MESSAGE_MAP(CdecbinhexDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT3, &CdecbinhexDlg::OnEnChangeEdit3)
	
	ON_LBN_SELCHANGE(IDC_LIST1, &CdecbinhexDlg::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CdecbinhexDlg message handlers

BOOL CdecbinhexDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	stringList.InsertColumn(0, _T("BINARY"), 1, 200);
	stringList.InsertColumn(1, _T("INTEGER"), 1, 200);
	stringList.InsertColumn(2, _T("HEXADECIMAL"), 1, 200);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CdecbinhexDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CdecbinhexDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CdecbinhexDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CdecbinhexDlg::convertToHex(int number) {
	CString converted, temp;
	converted = "";
	while (number > 0) {
		switch (number % 16) {
		case 10:
			temp = "A";
			break;
		case 11:
			temp = "B";
			break;
		case 12:
			temp = "C";
			break;
		case 13:
			temp = "D";
			break;
		case 14:
			temp = "E";
			break;
		case 15:
			temp = "F";
			break;
		default:
			temp.Format(_T("%d"),number%16);
			break;
		}
		number = number / 16;
		converted = converted + temp;

	}
	return converted.MakeReverse();

};

CString CdecbinhexDlg::convertToBin(int number) {
	CString converted,temp;
	converted = "";
	while (number > 0) {
		int bin = number % 2;
		number = number / 2;
		temp.Format(_T("%d"), bin);
		converted = converted+temp;
	}
	return converted.MakeReverse();


};

BOOL CdecbinhexDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE)) 
			pMsg->wParam = VK_INSERT;
		if (pMsg->wParam == VK_INSERT) {

			UpdateData(true);
			if (integer == 0) { 
				binary = "0";
				hexadecimal = "0";
			}
			CString separator(_T("--->"));
			CString integerConverted(_T(""));
			integerConverted.Format(_T("%d"), integer);
			stringList.InsertItem(0,binary);
			stringList.InsertItem(0,integerConverted);
			stringList.InsertItem(0,hexadecimal);
			
			//binary = _T("Pressed enter key");
			UpdateData(false);


		}
		
			
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CdecbinhexDlg::OnEnChangeEdit3()
{
	UpdateData(true);
	if (integer != 0) {
		binary = convertToBin(integer);
		hexadecimal = convertToHex(integer);
	}
	
	UpdateData(false);
}




void CdecbinhexDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}
