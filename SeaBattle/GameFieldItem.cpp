#include "stdafx.h"
#include "GameFieldItem.h"
#include "GameColors.h"

GameFieldItem::GameFieldItem()
	:_visible(false),
	_coordinates(),
	_mark(none),
	_rect()
{
}



GameFieldItem::GameFieldItem(const MatrixPoint gPoint, const bool visible, const CRect rect, const GameFieldItemMark mark) :
	_visible(visible),
	_coordinates(gPoint), _mark(mark),
	_rect(rect)
{
}

void GameFieldItem::SetMark(const GameFieldItemMark mark)
{
	_mark = mark;
}

GameFieldItem::GameFieldItemMark GameFieldItem::GetMark() const
{
	return _mark;
}

MatrixPoint GameFieldItem::GetGamePosition() const
{
	return _coordinates;
}

void GameFieldItem::SetGamePosition(MatrixPoint point)
{
	_coordinates = point;
}

bool GameFieldItem::IsVisible() const
{
	return _visible;
}

void GameFieldItem::SetVisible(const bool visible)
{
	_visible = visible;
}

void GameFieldItem::SetRect(const CRect rect)
{
	_rect = rect;
}

CRect GameFieldItem::GetRect() const
{
	return _rect;
}

void GameFieldItem::Show(CPaintDC* dc)
{
	const auto oldBrush = dc->GetCurrentBrush();
	const auto oldPen = dc->GetCurrentPen();
	CBrush markBrush;
	CPen newPen;
	newPen.CreatePen(PS_SOLID, 1, GameColors::MarksColor());
	dc->SelectObject(newPen);

	const auto mark = GetMark();
	auto rect = GetRect();
	switch (mark)
	{
	case dotMark:
	{
		markBrush.CreateSolidBrush(GameColors::Missed());
		dc->SelectObject(markBrush);
		CPen markPen;
		markPen.CreatePen(PS_SOLID, 1, GameColors::RegularForPen());
		dc->SelectObject(markPen);
		const auto centre = rect.CenterPoint();
		dc->Ellipse(centre.x - 2, centre.y - 2, centre.x + 2, centre.y + 2);
	}
	break;
	case crossMark:
	{
		markBrush.CreateSolidBrush(GameColors::Regular());
		dc->SelectObject(markBrush);
		CPoint a[]{ rect.TopLeft(), rect.BottomRight() };
		CPoint b[]{ CPoint(rect.left,rect.bottom), CPoint(rect.right,rect.top) };
		dc->Polyline(a, 2);
		dc->Polyline(b, 2);
	}
	break;
	case none:
		markBrush.CreateSolidBrush(GameColors::Regular());
		dc->SelectObject(markBrush);
		break;
	}

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush);
}

