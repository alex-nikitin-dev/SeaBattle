#include "stdafx.h"
#include "GameField.h"
#include <math.h>
#include<vector>
using namespace std;
GameField::GameField()
	:GameField(CPoint(0, 0), 200, 10, { {1,4},{2,3},{3,2},{4,1} })
{
}
void GameField::CreateCells(const int countCells)
{
	_cells.clear();
	const int sizeCell = round(_sideLength / double(countCells));
	for (int i = 0; i < countCells; i++)
	{
		_cells.push_back({});
		for (int j = 0; j < countCells; j++)
		{
			_cells[i].push_back(Cell(MatrixPoint(i, j), true,
				GetCellRect(MatrixPoint(i, j), sizeCell), GameFieldItem::GameFieldItemMark::none));
		}
	}
}
void GameField::CreateShips()
{
	_ships.clear();
	for(const auto typeCountItem:_shipsTypesCount)
	{
		for (int i = 0; i < typeCountItem.second; i++)
		{
			_ships.push_back(Ship(typeCountItem.first));
		}
	}
}

Ship* GameField::GetShip(const MatrixPoint point)
{
	for(auto& ship:_ships)
	{
		if (ship.IsPointBelongs(point)) return &ship;
	}
	return nullptr;
}

GameField::GameField(const CPoint topLeft, const int sideLength, const int countCells, const map<int, int> typesCount)
	:_sideLength(sideLength),
	_countCells(countCells),
	_topLeft(topLeft),
	_shipsTypesCount(typesCount)
{
	CreateCells(countCells);
	CreateShips();
}
void GameField::ShowCells(CPaintDC * dc)
{
	for (auto &cellRow : _cells)
	{
		for (auto &cell : cellRow)
		{
			cell.Show(dc);
		}
	}
}
void GameField::ShowShips(CPaintDC * dc)
{
	for (auto &ship : _ships)
	{
		ship.Show(dc);
	}
}
void GameField::Show(CPaintDC * dc)
{
	ShowCells(dc);
	ShowShips(dc);
}
bool  GameField::IsPointAroundHas(const MatrixPoint point, const Cell::CellState state)
{
	for(const auto matrixPoint:GetNearlyPoints(point,true))
	{
		if (GetCellByPoint(matrixPoint).GetState() == state)
			return true;
	}
	return false;
}

vector<MatrixPoint> GameField::GetNearlyPoints(MatrixPoint point, const bool exceptThePoint) const
{
	vector<MatrixPoint> result;
	for (int i = point.GetI() - 1; i <= point.GetI() + 1; i++)
	{
		for (int j = point.GetJ() - 1; j <= point.GetJ() + 1; j++)
		{
			const auto newPoint = MatrixPoint(i, j);
			if (IsMatrixPointFit(newPoint) && !(exceptThePoint && i == point.GetI() && j == point.GetJ()))
			{
				result.push_back(newPoint);
			}
		}
	}
	return result;
}

GameFieldItem::GameFieldItemMark GameField::GetMarkByPoint(const MatrixPoint point)
{
	return GetCellByPoint(point).GetMark();
}
bool  GameField::IsMatrixPointFit(MatrixPoint point) const
{
	if (point.GetI() >= _countCells || point.GetJ() >= _countCells
		|| point.GetI() < 0 || point.GetJ() < 0) return false;
	return true;
}

bool GameField::IsPlaceAvailable(MatrixPoint point, const int countCellsToVerify, const Ship::ShipOrientation orientation)
{
	const int fixedIndex = orientation == Ship::ShipOrientation::horizontally ? point.GetI() : point.GetJ();
	const int startMovedIndex = orientation == Ship::ShipOrientation::horizontally ? point.GetJ() : point.GetI();
	for (int movedIndex = startMovedIndex; movedIndex < _countCells && movedIndex < countCellsToVerify + startMovedIndex; movedIndex++)
	{
		MatrixPoint curPoint;
		if (orientation == Ship::ShipOrientation::horizontally)
		{
			curPoint = MatrixPoint(fixedIndex, movedIndex);
		}
		else
		{
			curPoint = MatrixPoint(movedIndex, fixedIndex);
		}
		auto nearlyPoints= GetNearlyPoints(curPoint, false);
		for (const auto nearlyPoint : nearlyPoints)
		{
			if (GetCellByPoint(nearlyPoint).GetState() == Cell::CellState::HasShip)
			{
				return false;
			}
		}
	}
	return true;
}

vector<MatrixPoint>  GameField::GetShipsPoints(MatrixPoint startPoint, const int countDecks, const Ship::ShipOrientation orientation)
{
	vector<MatrixPoint> result;
	int startMoveIndex = startPoint.GetJ();
	if(orientation == Ship::ShipOrientation::vertically)
	{
		startMoveIndex = startPoint.GetI();
	}
	
	for (int moveIndex = startMoveIndex; moveIndex < countDecks+ startMoveIndex; moveIndex++)
	{
		if (orientation == Ship::ShipOrientation::vertically)
		{
			result.push_back(MatrixPoint(moveIndex, startPoint.GetJ()));
		}
		else
		{
			result.push_back(MatrixPoint(startPoint.GetI(), moveIndex));
		}
	}

	return result;
}

vector<MatrixPoint>  GameField::GetNearlyShipPoints(const MatrixPoint startPoint, const int countDecks, const Ship::ShipOrientation orientation) const
{
	vector<MatrixPoint> result;
	auto shipsPoints = GetShipsPoints(startPoint,countDecks,orientation);
	for(const auto shipPoint:shipsPoints)
	{
		auto nearlyPoints =  GetNearlyPoints(shipPoint, true);
		for(const auto nearlyPoint:nearlyPoints)
		{
			result.push_back(nearlyPoint);
		}
	}

	for (const auto shipPoint : shipsPoints)
	{
		for (int i = 0; i < result.size(); i++)
		{
			if(shipPoint==result[i])
			{
				result.erase(result.begin() + i);
				i--;
			}
		}
	}
	return result;
}

bool GameField::TrySetShipByIndex(const int index, const MatrixPoint& point, const Ship::ShipOrientation orientation)
{
	if (!IsMatrixPointFit(point)) return false;

	if(orientation == Ship::ShipOrientation::horizontally
		&& point.GetJ() + _ships[index].GetCountDecks() > _countCells)
	{
			return false;
	}

	if (orientation == Ship::ShipOrientation::vertically
		&& point.GetI() + _ships[index].GetCountDecks() > _countCells)
	{
		return false;
	}
	
	if (!IsPlaceAvailable(point, _ships[index].GetCountDecks(), orientation)) return false;

	auto shipPoints = GetShipsPoints(point,_ships[index].GetCountDecks(),orientation);

	auto startShipCell = GetCellByPoint(shipPoints.front());
	auto endShipCell = GetCellByPoint(shipPoints.back());
	const CRect shipRect(startShipCell.GetRect().TopLeft(), endShipCell.GetRect().BottomRight());

	_ships[index].PutShip(point,shipRect,orientation);
	SetCellsAsBusy(shipPoints,Cell::CellState::HasShip);
	SetCellsAsBusy(GetNearlyShipPoints(shipPoints.front(), _ships[index].GetCountDecks(), orientation), Cell::CellState::NearlyShip);

	return true;
}
bool GameField::IsContainMarkNone()
{
	return IsContainMark(GameFieldItem::GameFieldItemMark::none);
}
bool GameField::IsContainMark(const GameFieldItem::GameFieldItemMark mark)
{
	for(auto rowCell:_cells)
	{
		for(auto cell:rowCell)
		{
			if (cell.GetMark() == mark) return true;
		}
	}

	return false;
}

void  GameField::SetCellsAsBusy(vector<MatrixPoint> points, const Cell::CellState state)
{
	for(const auto point: points)
	{
		GetCellByPoint(point).SetState(state);
	}
}

Cell & GameField::GetCellByPoint(MatrixPoint point)
{
	if(point.GetI()>=_countCells || point.GetJ()>=_countCells)
	{
		throw range_error("GetCellByPoint point out of range");
	}
	return _cells[point.GetI()][point.GetJ()];
}
void GameField::ResetCellsState()
{
	for(auto &row:_cells)
	{
		for(auto &cell:row)
		{
			cell.SetState(Cell::CellState::Available);
			cell.SetMark(GameFieldItem::GameFieldItemMark::none);
		}
	}
}
void GameField::ResetShipsState()
{
	for(auto& ship:_ships)
	{
		ship.SetState(Ship::ShipState::noDamage);
		ship.SetMark(GameFieldItem::GameFieldItemMark::none);
	}
}
void GameField::ResetCellsMarks()
{
	for (auto &row : _cells)
	{
		for (auto &cell : row)
		{
			cell.SetMark(GameFieldItem::GameFieldItemMark::none);
		}
	}
}
void GameField::ShipsAutoLayout()
{
	Ship::ShipOrientation orientation;
	ResetCellsState();

	for (int i = _ships.size() - 1, countCycle = 0; i >= 0; i--, countCycle++)
	{
		const MatrixPoint point = MatrixPoint(rand() % _countCells, rand() % _countCells);
		if (IsPointAroundHas(point, Cell::CellState::HasShip))
		{
			i++;
			continue;
		}
		if (rand() % 2 == 0)
		{
			orientation = Ship::ShipOrientation::horizontally;
		}
		else
		{
			orientation = Ship::ShipOrientation::vertically;
		}
		if (!TrySetShipByIndex(i, point, orientation))
		{
			i++;
			if (countCycle > 1000)
			{
				ResetCellsState();
				i = 0;
				countCycle = 0;
			}
		}
	}
}

int GameField::GetCountCells() const
{
	return _countCells;
}
CRect GameField::GetCellRect(MatrixPoint gPoint, const int size) const
{
	const int xi = _topLeft.x + size*gPoint.GetJ();
	const int yi = _topLeft.y + size*gPoint.GetI();
	return CRect(CPoint(xi, yi), CSize(size, size));
}
void GameField::ResizeCells()
{
	const int sizeCell = round(_sideLength / double(_cells.size()));
	for (int i = 0; i < _cells.size(); i++)
	{
		for (int j = 0; j < _cells[i].size(); j++)
		{
			_cells[i][j].SetRect(GetCellRect(MatrixPoint(i, j), sizeCell));
		}
	}
}
bool GameField::IsPointBelongsTo(const CPoint point, const CRect rect)
{
	return (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom);
}
MatrixPoint GameField::TranslatePoint(const CPoint point)
{
	for (auto row : _cells)
	{
		for (auto cell : row)
		{
			if (IsPointBelongsTo(point, cell.GetRect())) return cell.GetGamePosition();
		}
	}

	return MatrixPoint(-1, -1);
}
GameField::FireResult GameField::ConvertState(const Ship::ShipState state)
{
	switch (state)
	{
	case Ship::injured:
		return ShipInjured;
	case Ship::killed:
		return ShipKilled;
	case Ship::noDamage:
		return Missed;
	}

	return Missed;
}
GameFieldItem::GameFieldItemMark GameField::ConvertShipStateToMark(const GameField::FireResult fireResult)
{
	switch (fireResult)
	{
	case GameField::ShipKilled:
		return Cell::GameFieldItemMark::crossMark;
	case GameField::ShipInjured:
		return Cell::GameFieldItemMark::crossMark;
	case GameField::Missed:
		return Cell::GameFieldItemMark::dotMark;
	case GameField::PointIsntBelongsTo:
		return Cell::GameFieldItemMark::none;
	}

	return Cell::GameFieldItemMark::none;
}
GameField::FireResult GameField::Fire(const MatrixPoint point)
{
	auto ship = GetShip(point);
	if(ship != nullptr)
	{
		const auto shipState =  ship->SetDamage(point);
		return ConvertState(shipState);
	}
	SetCellMark(point, ConvertShipStateToMark(Missed), false);
	return Missed;
}

void GameField::SetSideLength(const int sideLength)
{
	_sideLength = sideLength;
	ResizeCells();
}

int GameField::GetSideLength() const
{
	return _sideLength;
}

void GameField::SetCountCells(const int countCells)
{
	_countCells = countCells;
}

void GameField::SetTopLeft(const CPoint topLeft)
{
	_topLeft = topLeft;
	ResizeCells();
}

CRect GameField::GetBounds() const
{
	return CRect(_topLeft, CPoint(_sideLength + _topLeft.x, _sideLength + _topLeft.y));
}

vector<MatrixPoint> GameField::GetCellPredicted(MatrixPoint point) const
{
	vector<MatrixPoint> result;
	vector<MatrixPoint> temp;
	temp.push_back(MatrixPoint(point.GetI()-1,point.GetJ()-1));
	temp.push_back(MatrixPoint(point.GetI()-1, point.GetJ()+1));
	temp.push_back(MatrixPoint(point.GetI()+1, point.GetJ()-1));
	temp.push_back(MatrixPoint(point.GetI()+1, point.GetJ()+1));

	for(const auto t:temp)
	{
		if(IsMatrixPointFit(t))
		{
			result.push_back(t);
		}
	}
	return result;
}
void GameField::SetCellMark(const MatrixPoint point, const GameFieldItem::GameFieldItemMark mark, const bool markNearlyPoints)
{
	GetCellByPoint(point).SetMark(mark);
	if(markNearlyPoints && mark == GameFieldItem::GameFieldItemMark::crossMark)
	{
		auto cellPredicted = GetCellPredicted(point);
		for (const auto cp : cellPredicted)
		{
			GetCellByPoint(cp).SetMark(GameFieldItem::GameFieldItemMark::dotMark);
		}
	}
}

int GameField::GetCountAliveShips()
{
	int count =0;
	for(auto ship:_ships)
	{
		if (ship.GetState() != Ship::ShipState::killed)
			count++;
	}

	return count;
}

bool GameField::IsContainAliveShips()
{
	for (auto ship : _ships)
	{
		if (ship.GetState() != Ship::ShipState::killed)
			return true;
	}
	return false;
}


