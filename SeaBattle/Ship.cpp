#include "stdafx.h"
#include "Ship.h"

int Ship::_maxCountDeck = 10;
Ship::Ship(const int countDeck)
	:GameFieldItem()
{
	SetCountDeck(countDeck);
	_orientation = vertically;
}

bool Ship::IsPointBelongs(const MatrixPoint point)
{
	for(auto deck:_decks)
	{
		if (deck.GetGamePosition() == point) return true;
	}
	return false;
}

Ship::ShipState Ship::SetDamage(const MatrixPoint point)
{
	const auto deck = GetDeck(point);
	if(deck != nullptr)
	{
		GetDeck(point)->Damage();
	}
	
	return GetShipCurrentState();
}

Ship::ShipState Ship::GetShipCurrentState()
{
	int countDamaged = 0;
	ShipState result = ShipState::noDamage;
	for(auto deck:_decks)
	{
		if (deck.IsDamage())
		{
			result = ShipState::injured;
			countDamaged++;
		}
	}

	if(countDamaged == _decks.size())
	{
		result = ShipState::killed;
	}

	return result;
}

void Ship::CreateDecks()
{
	_decks.clear();
	for (int i = 0; i < _countDeck; i++)
	{
		_decks.push_back(ShipDeck());
	}
}

void Ship::PutShip(const MatrixPoint gPoint, const CRect rect, const ShipOrientation orientation)
{
	SetOrientation(orientation);
	SetGamePosition(gPoint);
	SetRect(rect);
}


void Ship::SetGamePosition(MatrixPoint point)
{
	for (int i = 0; i < _decks.size(); i++)
	{
		if (_orientation == horizontally)
		{
			_decks[i].SetGamePosition({ point.GetI(),point.GetJ() + i });
		}
		else
		{
			_decks[i].SetGamePosition({ point.GetI() + i,point.GetJ() });
		}
	}
}

int Ship::GetCountDecks() const
{
	return _countDeck;
}

void Ship::Show(CPaintDC* dc)
{
	dc->Rectangle(GetRect());
	for(auto deck:_decks)
	{
		deck.Show(dc);
	}
}

void Ship::SetRect(const CRect rect)
{
	const int deckWidth = rect.Width() < rect.Height() ? rect.Width() : rect.Height();
	for(int i = 0;i<_decks.size();i++)
	{
		if(_orientation == ShipOrientation::horizontally)
		{
			_decks[i].SetRect(CRect(CPoint(rect.left + deckWidth * i, rect.top), CPoint(rect.left + deckWidth * (i+1), rect.bottom)));
		}
		else
		{
			_decks[i].SetRect(CRect(CPoint(rect.left , rect.top + deckWidth * i), CPoint(rect.right , rect.top + deckWidth * (i+1))));
		}
	}
	GameFieldItem::SetRect(rect);
}

void Ship::SetState(const ShipState state)
{
	 if(state == ShipState::killed || state == ShipState::noDamage)
	 {
		 for(auto&deck:_decks)
		 {
			 if(state == ShipState::killed) deck.Damage();
			 else if (state == ShipState::noDamage)deck.SetNoDamage();
		 }
	 }
}

Ship::ShipState Ship::GetState() 
{
	return GetShipCurrentState();
}

void Ship::SetOrientation(const ShipOrientation orientation)
{
	_orientation = orientation;
	SetGamePosition(GetGamePosition());
}

Ship::ShipOrientation Ship::GetOrientation() const
{
	return _orientation;
}

void Ship::SetMaxCountDeck(const int maxCountDeck)
{
	_maxCountDeck = maxCountDeck;
}

void Ship::SetCountDeck(const int countDeck)
{
	if(countDeck > _maxCountDeck)
	{
		throw std::invalid_argument("countDeck > _maxCountDeck");
	}

	_countDeck = countDeck;
	CreateDecks();
}

ShipDeck* Ship::GetDeck(const MatrixPoint point)
{
	for(auto& deck:_decks)
	{
		if (deck.GetGamePosition() == point)
			return &deck;
	}

	return nullptr;
}
void Ship::SetMark(const GameFieldItemMark mark)
{
	for(auto&deck:_decks)
	{
		deck.SetMark(mark);
	}
	GameFieldItem::SetMark(mark);
}


