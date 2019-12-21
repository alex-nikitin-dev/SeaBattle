#include "stdafx.h"
#include "Game.h"

Game::Game()
	:_firstSubject(sActor),
	_isBotVisible(false)
{
	srand(time(nullptr));
}
void Game::SetBounds(const CPoint topLeft, const int width)
{
	_actor.SetBoundsFields(topLeft, width);
	CRect actorBounds =  _actor.GetBoundsOneField();
	_bot.SetBoundsFields(CPoint(actorBounds.left, actorBounds.top + actorBounds.Width()*1.1), width);
}

CRect Game::GetBounds() const
{
	CRect result = _actor.GetBoundsFields();
	if(_isBotVisible)
	{
		result.bottom = _bot.GetBoundsFields().bottom;
	}
	return result;
}

void Game::StartNew()
{
	_actor.ShipsLayout();
	/*if(!_actor.IsShipLayoutAlready())
	{
		_actor.ShipsLayout();
	}*/
	_bot.ShipsLayout();
	_actor.ResetEnemyField();
	_bot.ResetEnemyField();
	_actor.ResetMyFieldItemsStateButShipsLayout();
	_bot.ResetMyFieldItemsStateButShipsLayout();
	if(_firstSubject == sBot)
	{
		BotNextStep();
	}
}

void Game::Show(CPaintDC * dc)
{
	_actor.ShowFields(dc);
	if(_isBotVisible) _bot.ShowFields(dc);
}

void Game::ActorShipsAutoLayout()
{
	_actor.ShipsLayout();
}

void Game::ShowBot()
{
	_isBotVisible = true;
}

bool Game::HideBot() const
{
	return _isBotVisible;
}

bool Game::StepBy(const MatrixPoint matrixPoint, Player& subject, Player& object)
{
	if (matrixPoint != MatrixPoint(-1, -1))
	{
		const auto fireResult = object.GetDamage(matrixPoint);
		subject.SetEnemyFieldMark(matrixPoint, fireResult);
		if (fireResult == GameField::FireResult::Missed)
		{
			return false;
		}
		return true;
	}
	return false;
}
bool Game::ActorStep(const MatrixPoint point)
{
	return StepBy(point, _actor, _bot);
}
bool Game::BotNextStep()
{
	return StepBy(_bot.GetNextPoint(), _bot, _actor);
}

bool Game::IsGameOver()
{
	return GetWinner() != sNone;
}

Game::Subject Game::GetWinner()
{
	if (!_actor.IsContainAliveShip()) return sBot;
	if (!_bot.IsContainAliveShip()) return sActor;
	return sNone;
}
CString Game::GetNameWinner()
{
	const auto win = GetWinner();
	CString result = L"";
	switch (win)
	{
	case sActor:
		result = "Actor";
		break;
	case sBot:
		result = "Bot";
		break;
	default: 
		break;
	}

	return result;
}
void Game::DoGameOver()
{
	MessageBox(nullptr, _T("GameOver. The winner is " + GetNameWinner()), L"Game", MB_OK);
}
void Game::Fire(const CPoint point)
{
	if (IsGameOver()) { DoGameOver(); return; }
	const auto tPair = _actor.TranslatePoint(point);
	
	if (tPair.second == Player::FieldType::Enemy)
	{
		const auto matrixPoint = tPair.first;
		if (matrixPoint.IsNotexist() || _actor.IsEnemyPointContainMark(matrixPoint)) return;
		if(!ActorStep(matrixPoint))
		{
			while (!IsGameOver() && BotNextStep()){}
		}
		if (IsGameOver()) DoGameOver();
	}
}
