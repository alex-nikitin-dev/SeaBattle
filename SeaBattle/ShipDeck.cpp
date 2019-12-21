#include "stdafx.h"
#include "ShipDeck.h"


ShipDeck::ShipDeck()
	:GameFieldItem(),
	_damage(false)
{
}

ShipDeck::ShipDeck(MatrixPoint gPoint, bool visible, CRect rect, GameFieldItemMark mark) :
	GameFieldItem(gPoint,visible,rect,mark),
	_damage(false)
{
}

void ShipDeck::Damage()
{
	_damage = true;
	SetMark(GameFieldItemMark::crossMark);
}
void ShipDeck::SetNoDamage()
{
	_damage = false;
	SetMark(GameFieldItemMark::none);
}
bool ShipDeck::IsDamage() const
{
	return _damage;
}

void ShipDeck::Show(CPaintDC* dc)
{
	GameFieldItem::Show(dc);
}


