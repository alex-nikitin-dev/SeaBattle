#pragma once
#include "Player.h"
class Bot :
	public Player
{
public:
	Bot();
	MatrixPoint GetRandomPoint() const;
	MatrixPoint GetNextPoint();
};

