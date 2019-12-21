#pragma once
#include"GameFieldItem.h"
class Cell 
	:public GameFieldItem
{
public:
	enum CellState
	{
		HasShip,
		NearlyShip,
		Available
	};
	void SetDisabled();
	bool IsDisabled() const;
	Cell(MatrixPoint gPoint, bool visible, CRect rect, GameFieldItemMark mark);
	Cell(MatrixPoint gPoint, bool visible, CRect rect, GameFieldItemMark mark, CellState state);
	void Show(CPaintDC * dc) override;
	void SetState(CellState state);
	CellState GetState() const;
private:
	bool _isDisabled;
	CellState _state;
};

