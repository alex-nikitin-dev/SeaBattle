#pragma once
#include"Bot.h"
#include"Actor.h"
#include <afxwin.h>
class Game
{
public:
	enum Subject
	{
		sActor,
		sBot,
		sNone
	};
	Game();
	void SetBounds(CPoint topLeft, int width);
	CRect GetBounds() const;
	void StartNew();
	void Show(CPaintDC *dc);
	void ActorShipsAutoLayout();
	void ShowBot();
	bool HideBot() const;
	static bool StepBy(const MatrixPoint matrixPoint, Player& subject, Player& object);
	bool ActorStep(MatrixPoint point);
	bool BotNextStep();
	bool IsGameOver();
	Game::Subject GetWinner();
	CString GetNameWinner();
	void DoGameOver();
	void Fire(CPoint point);
	
private:
	Actor _actor;
	Bot _bot;
	Subject _firstSubject;
	bool _isBotVisible;
};