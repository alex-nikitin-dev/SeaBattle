#include "stdafx.h"
#include "Cell.h"
#include"GameColors.h"

void Cell::SetDisabled()
{
	_isDisabled = true;
}

bool Cell::IsDisabled() const
{
	return _isDisabled;
}

Cell::Cell(const MatrixPoint gPoint, const bool visible, const CRect rect, const GameFieldItemMark mark) :
	Cell(gPoint, visible, rect, mark, CellState::Available)
{
}

Cell::Cell(const MatrixPoint gPoint, const bool visible, const CRect rect, const GameFieldItemMark mark, const CellState state)
	: GameFieldItem(gPoint, visible, rect, mark),
	_isDisabled(false),
	_state(state)
{
}

void Cell::Show(CPaintDC * dc)
{
	const auto oldBrush = dc->GetCurrentBrush();
	const auto oldPen = dc->GetCurrentPen();
	CBrush newBrush;	
	CPen newPen;
	newPen.CreatePen(PS_SOLID,1, GameColors::RegularForPen());

	const auto mark = GetMark();
	switch (mark)
	{
	case dotMark:
	{
		newBrush.CreateSolidBrush(GameColors::Missed());
	}
	break;
	case crossMark:
	{
		newBrush.CreateSolidBrush(GameColors::Injured());
	}
	break;
	case none:
		newBrush.CreateSolidBrush(GameColors::Regular());
		break;
	}
	dc->SelectObject(newPen);
	dc->SelectObject(newBrush);
	dc->Rectangle(GetRect());
	dc->SelectObject(oldBrush);
	dc->SelectObject(oldPen);
	GameFieldItem::Show(dc);
}

void Cell::SetState(const CellState state)
{
	_state = state;
}

Cell::CellState Cell::GetState() const
{
	return _state;
}

