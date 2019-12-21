#include "stdafx.h"
#include "Actor.h"


Actor::Actor(): Player()
{
}

void Actor::SetName(const std::string name)
{
	_name = name;
}

std::string Actor::GetName() const
{
	return _name;
}
