
// decbinhexDlg.cpp : implementation file
//

#include "stdafx.h"
#include "decbinhex.h"
#include "decbinhexDlg.h"
#include "afxdialogex.h"
#include <string.h>
#include <cstring>

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
	DDV_MinMaxInt(pDX, integer, -5555, INT_MAX);
}

BEGIN_MESSAGE_MAP(CdecbinhexDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT3, &CdecbinhexDlg::OnEnChangeEdit3)
	
	ON_LBN_SELCHANGE(IDC_LIST1, &CdecbinhexDlg::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT4, &CdecbinhexDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON2, &CdecbinhexDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CdecbinhexDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT5, &CdecbinhexDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT1, &CdecbinhexDlg::OnEnChangeEdit1)
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
	stringList.InsertColumn(0, _T("BIN"), 1, 300);
	stringList.InsertColumn(1, _T("DEZ (signed)"), 1, 100);
	stringList.InsertColumn(2, _T("DEZ (unsigned)"), 1, 100);
	stringList.InsertColumn(3, _T("HEX"), 1, 100);


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




BOOL CdecbinhexDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_RETURN)) 
			pMsg->wParam = VK_INSERT;
		if (pMsg->wParam == VK_INSERT) {
			unsigned int Unint;
			UpdateData(true);
			if (integer == 0) { 
				binary = "0";
				hexadecimal = "0";
			}
			Unint =4294967295;
			CString integerConverted(_T(""));
			CString unsignedIntConverted(_T(""));
			integerConverted.Format(_T("%d"), integer);
			unsignedIntConverted.Format(_T("%u"), integer);
			int currentItem;
			currentItem = stringList.InsertItem(0,binary);
			stringList.SetItemText(currentItem,1,integerConverted);
			stringList.SetItemText(currentItem, 2, unsignedIntConverted);
			stringList.SetItemText(currentItem,3,hexadecimal);
			UpdateData(false);
		}
		
			
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CdecbinhexDlg::OnEnChangeEdit3()
{
	UpdateData(true);
	if (integer != 0) {
		binary = numberConverter.toBin(integer);
		hexadecimal = numberConverter.toHex(integer);
	}
	UpdateData(false);
}


void CdecbinhexDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CdecbinhexDlg::OnEnChangeEdit4()
{
	UpdateData(true);
	integer = numberConverter.fromBin(binary);
	hexadecimal = numberConverter.toHex(integer);
	UpdateData(false);
}



void CdecbinhexDlg::OnBnClickedButton2()
{
	delete(this);
}


void CdecbinhexDlg::OnBnClickedButton1()
{
	stringList.DeleteAllItems();
}


void CdecbinhexDlg::OnEnChangeEdit5()
{
	UpdateData(true);
	integer = numberConverter.fromHex(hexadecimal);
	binary = numberConverter.toBin(integer);
	UpdateData(false);
}


void CdecbinhexDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
