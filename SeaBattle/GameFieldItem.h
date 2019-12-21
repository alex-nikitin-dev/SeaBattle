#pragma once
#include"MatrixPoint.h"
class GameFieldItem
{
public:
	enum GameFieldItemMark
	{
		dotMark,
		crossMark,
		none
	};
	GameFieldItem();
	GameFieldItem(MatrixPoint gPoint, bool visible, CRect rect, GameFieldItemMark mark);
	MatrixPoint GetGamePosition() const;
	virtual void SetGamePosition(MatrixPoint point);
	virtual void SetRect(CRect rect);
	CRect GetRect() const;
	virtual void SetMark(GameFieldItemMark mark);
	GameFieldItemMark GetMark() const;
	virtual ~GameFieldItem() = default;
private:
	bool		_visible;
	MatrixPoint	_coordinates;
	GameFieldItemMark _mark;
	CRect _rect;
protected:
	bool IsVisible() const;
	void SetVisible(bool visible);
	virtual void Show(CPaintDC* dc);
};

