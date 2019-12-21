#pragma once
#include<vector>
#include"Cell.h"
#include"Ship.h"
#include <map>

class GameField
{
public:
	enum FireResult
	{
		ShipKilled,
		ShipInjured,
		Missed,
		PointIsntBelongsTo
	};
	GameField();
	GameField(CPoint topLeft, int sideLength, int countCells, std::map<int, int> typesCount);
	void ShipsAutoLayout();
	void SetSideLength(int sideLength);
	int GetSideLength() const;
	void SetTopLeft(CPoint topLeft);
	CRect GetBounds() const;
	bool IsContainAliveShips();
	FireResult Fire(MatrixPoint point);
	MatrixPoint TranslatePoint(CPoint point);
	GameFieldItem::GameFieldItemMark GetMarkByPoint(MatrixPoint point);
	static GameFieldItem::GameFieldItemMark ConvertShipStateToMark(const GameField::FireResult fireResult);
	void SetCellMark(MatrixPoint point, GameFieldItem::GameFieldItemMark mark, bool markNearlyPoints);
	void ResetCellsState();
	void ResetShipsState();
	void ResetCellsMarks();
	void Show(CPaintDC *dc);
	int GetCountCells() const;
	bool IsContainMarkNone();
private:
	void ShowCells(CPaintDC* dc);
	void ShowShips(CPaintDC* dc);
	bool IsPointAroundHas(MatrixPoint point, Cell::CellState state);
	std::vector<MatrixPoint> GetNearlyPoints(MatrixPoint point, bool exceptThePoint) const;
	bool IsMatrixPointFit(MatrixPoint point) const;
	bool IsPlaceAvailable(MatrixPoint point, int countCellsToVerify, Ship::ShipOrientation orientation);
	static std::vector<MatrixPoint> GetShipsPoints(MatrixPoint startPoint, int countDecks, Ship::ShipOrientation orientation);
	std::vector<MatrixPoint> GetNearlyShipPoints(MatrixPoint startPoint, int countDecks, Ship::ShipOrientation orientation) const;
	bool TrySetShipByIndex(int index, const MatrixPoint& point, Ship::ShipOrientation orientation);
	bool IsContainMark(GameFieldItem::GameFieldItemMark mark);
	void SetCellsAsBusy(std::vector<MatrixPoint> points, Cell::CellState state);
	Cell& GetCellByPoint(MatrixPoint point);
	void SetCountCells(int countCells);
	std::vector<MatrixPoint> GetCellPredicted(MatrixPoint point) const;
	int GetCountAliveShips();
	static FireResult ConvertState(Ship::ShipState state);
	int _sideLength;
	int _countCells;
	std::vector<std::vector<Cell>> _cells;
	std::vector<Ship> _ships;
	CPoint _topLeft;
	CRect GetCellRect(MatrixPoint gPoint, int size) const;
	std::map<int, int> _shipsTypesCount;
	void CreateCells(int countCells);
	void ResizeCells();
	static bool IsPointBelongsTo(CPoint point, CRect rect);
	void CreateShips();
protected:
	Ship *GetShip(MatrixPoint point);
};
