#pragma once
#include "Player.h"
#include <string>

class Actor :
	public Player
{
public:
	Actor();
	void SetName(std::string name);
	std::string GetName() const;
private:
	std::string _name;
};

