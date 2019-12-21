#pragma once
#include "GameFieldItem.h"
class ShipDeck:public GameFieldItem
{
private:
	bool _damage;
public:
	ShipDeck();
	ShipDeck(MatrixPoint gPoint, bool visible, CRect rect, GameFieldItemMark mark);
	void Damage();
	void SetNoDamage();
	bool IsDamage() const;
	void Show(CPaintDC* dc) override;
};

