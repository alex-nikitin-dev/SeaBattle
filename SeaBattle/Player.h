#pragma once
#include"GameField.h"
#include"Ship.h"
class Player
{
public:
	enum FieldType
	{
		Own,
		Enemy,
		none
	};
	Player();
	void ShipsLayout();
	GameField::FireResult  GetDamage(MatrixPoint point);
	void ShowFields(CPaintDC *dc);
	void  SetBoundsFields(CPoint topLeft, int width);
	CRect Player::GetBoundsFields() const;
	CRect GetBoundsOneField() const;
	bool IsContainAliveShip();
	std::pair<MatrixPoint, FieldType> TranslatePoint(CPoint point);
	bool IsShipLayoutAlready() const;
	static Cell::GameFieldItemMark ConvertShipStateToMark(const Ship::ShipState state);
	bool IsEnemyPointContainMark(MatrixPoint point);
	void SetEnemyFieldMark(const MatrixPoint point, const GameField::FireResult fireResult);
	void ResetEnemyField();
	void ResetMyFieldItemsStateButShipsLayout();
protected:
	GameField _myField;
	GameField _enemyField;
	int _winsCount;
	bool _lastStepSuccessful;
	bool _isShipsLayoutAlready;

};

