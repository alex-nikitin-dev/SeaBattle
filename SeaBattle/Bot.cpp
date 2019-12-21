#include "stdafx.h"
#include "Bot.h"


Bot::Bot(): Player()
{

}

MatrixPoint Bot::GetRandomPoint() const
{
  const int countCells = _enemyField.GetCountCells();
  return MatrixPoint(rand() % countCells, rand() % countCells);
}

MatrixPoint Bot::GetNextPoint()
{
	auto point = GetRandomPoint();
	if (!_enemyField.IsContainMarkNone()) return MatrixPoint::GetNotexistPoint();
	while(_enemyField.GetMarkByPoint(point) != GameFieldItem::GameFieldItemMark::none)
	{
		point = GetRandomPoint();
	}
	return point;
}
