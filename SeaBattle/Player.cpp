#include "stdafx.h"
#include "Player.h"
#include <math.h>

Player::Player()
	: _winsCount(0),
	_lastStepSuccessful(false),
	_isShipsLayoutAlready(false)
{
}

void Player::ShipsLayout()
{
	_myField.ShipsAutoLayout();
	_isShipsLayoutAlready = true;
}

void  Player::SetBoundsFields(const CPoint topLeft, const int width)
{
	const int deltaW = round(width*0.05);
	const int fieldSideLength = round((width - deltaW) / 2.0);
	_myField.SetSideLength(fieldSideLength);
	_myField.SetTopLeft(topLeft);

	_enemyField.SetSideLength(fieldSideLength);
	_enemyField.SetTopLeft(CPoint(topLeft.x + fieldSideLength + deltaW, topLeft.y));
}

CRect Player::GetBoundsOneField() const
{
	return _myField.GetBounds();
}

bool Player::IsContainAliveShip()
{
	return _myField.IsContainAliveShips();
}

std::pair<MatrixPoint, Player::FieldType> Player::TranslatePoint(const CPoint point)
{
	std::pair<MatrixPoint, FieldType> result;
	result.first =  _myField.TranslatePoint(point);
	result.second = Own;
	if (result.first != MatrixPoint(-1, -1)) return result;

	result.first = _enemyField.TranslatePoint(point);
	result.second = Enemy;
	if (result.first != MatrixPoint(-1, -1)) return result;
	
	
	return { MatrixPoint(-1,-1),none };
}

GameField::FireResult Player::GetDamage(const MatrixPoint point)
{
	return  _myField.Fire(point);
}

CRect Player::GetBoundsFields() const
{
	auto br = _enemyField.GetBounds().BottomRight();
	br.x*=1.05;
	br.y *= 1.05;
	return CRect(_myField.GetBounds().TopLeft(), br);
}
bool Player::IsShipLayoutAlready() const
{
	return _isShipsLayoutAlready;
}
Cell::GameFieldItemMark Player::ConvertShipStateToMark(const Ship::ShipState state)
{
	switch (state)
	{
	case Ship::injured:
		return Cell::GameFieldItemMark::crossMark;
	case Ship::killed:
		return Cell::GameFieldItemMark::crossMark;
	case Ship::noDamage:
		return Cell::GameFieldItemMark::dotMark;
	}

	return Cell::GameFieldItemMark::none;
}

bool Player::IsEnemyPointContainMark(const MatrixPoint point)
{
	return _enemyField.GetMarkByPoint(point) != GameFieldItem::GameFieldItemMark::none;
}

void Player::SetEnemyFieldMark(const MatrixPoint point, const GameField::FireResult fireResult)
{
	_enemyField.SetCellMark(point, GameField::ConvertShipStateToMark(fireResult),true);
}

void Player::ResetEnemyField()
{
	_enemyField.ResetCellsState();
}

void Player::ResetMyFieldItemsStateButShipsLayout()
{
	_myField.ResetShipsState();
	_myField.ResetCellsMarks();
}

void Player::ShowFields(CPaintDC *dc)
{
	_myField.Show(dc);
	_enemyField.Show(dc);
}


