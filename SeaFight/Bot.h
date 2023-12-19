#pragma once
#include "User.h"
#include "Field.h"
#include <vector>

struct Bot : User
{
	Field field, EnemyField;

	std::vector<Ship> botShips;

	Bot(std::string name)
		: User(name)
	{ }
};