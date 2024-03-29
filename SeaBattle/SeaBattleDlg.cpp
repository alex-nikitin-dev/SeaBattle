
// SeaBattleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SeaBattle.h"
#include "SeaBattleDlg.h"
#include "afxdialogex.h"

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


// CSeaBattleDlg dialog



CSeaBattleDlg::CSeaBattleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SEABATTLE_DIALOG, pParent),
	_game()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_game.SetBounds(CPoint(10, 10), 600);
}

void CSeaBattleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSeaBattleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_GAME_EXIT, &CSeaBattleDlg::OnGameExit)
	ON_COMMAND(ID_GAME_SHIPSAUTOLAYOUT, &CSeaBattleDlg::OnGameShipsautolayout)
	ON_COMMAND(ID_GAME_STARTNEW, &CSeaBattleDlg::OnGameStartnew)
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_GAME_ABOUT, &CSeaBattleDlg::OnGameAbout)
END_MESSAGE_MAP()


// CSeaBattleDlg message handlers

BOOL CSeaBattleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	StartNewGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSeaBattleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSeaBattleDlg::OnPaint()
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
		CPaintDC dc(this);
		auto oldBrush = dc.GetCurrentBrush();
		CBrush newBrush;
		newBrush.CreateSolidBrush(RGB(255, 255, 255));
		dc.SelectObject(newBrush);
		CRect rect;
		this->GetClientRect(&rect);
		dc.Rectangle(rect);
		dc.SelectObject(oldBrush);

		
		//dc.Rectangle(_game.GetBounds());
		_game.Show(&dc);

		

		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSeaBattleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeaBattleDlg::OnGameExit()
{
	exit(0);
}


void CSeaBattleDlg::OnGameShipsautolayout()
{
	_game.ActorShipsAutoLayout();
	Invalidate();
}

void CSeaBattleDlg::StartNewGame()
{
	_game.StartNew();
#ifdef DEBUG 
	_game.ShowBot();
#endif
	SetWindowPos(nullptr, -1, -1, _game.GetBounds().Width()*1.05, _game.GetBounds().Height()*1.1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	Invalidate();
}
void CSeaBattleDlg::OnGameStartnew()
{
	StartNewGame();
}


void CSeaBattleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	_game.Fire(point);
	Invalidate();
	CDialog::OnLButtonUp(nFlags, point);
}


void CSeaBattleDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	SetWindowPos(nullptr, -1, -1, _game.GetBounds().Width()*1.05, _game.GetBounds().Height()*1.05+50, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}


void CSeaBattleDlg::OnGameAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}
