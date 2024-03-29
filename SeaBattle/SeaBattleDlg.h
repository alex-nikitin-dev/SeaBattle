
// SeaBattleDlg.h : header file
//

#pragma once
#include"Game.h"

// CSeaBattleDlg dialog
class CSeaBattleDlg : public CDialog
{
// Construction
public:
	CSeaBattleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEABATTLE_DIALOG };
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
	DECLARE_MESSAGE_MAP()
private:
	Game _game;
public:
	afx_msg void OnGameExit();
	afx_msg void OnGameShipsautolayout();
	void StartNewGame();
	afx_msg void OnGameStartnew();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGameAbout();
};
