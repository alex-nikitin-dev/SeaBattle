#pragma once
#include "GameFieldItem.h"
#include "ShipDeck.h"
#include<vector>
class Ship : public GameFieldItem
{
public:
	enum ShipState
	{
		injured,
		killed,
		noDamage
	};
	enum ShipOrientation
	{
		vertically,
		horizontally
	};
	Ship(int countDeck);
	bool IsPointBelongs(MatrixPoint point);
	ShipState SetDamage(MatrixPoint point);
	ShipState GetShipCurrentState();
	
	ShipState GetState();
	void SetOrientation(ShipOrientation orientation);
	ShipOrientation GetOrientation() const;
	static void SetMaxCountDeck(int maxCountDeck);
	void PutShip(MatrixPoint gPoint, CRect rect, ShipOrientation orientation);
	void SetGamePosition(MatrixPoint point) override;
	int GetCountDecks() const;
	void Show(CPaintDC *dc) override;
	void SetRect(CRect rect) override;
	void SetMark(GameFieldItemMark mark) override;
	void SetState(ShipState state);
private:
	void SetCountDeck(int countDeck);
	ShipDeck* GetDeck(MatrixPoint point);
	void CreateDecks();
	std::vector<ShipDeck> _decks;
	ShipState _state;
	ShipOrientation _orientation;
	static int _maxCountDeck;
	int _countDeck;
};

