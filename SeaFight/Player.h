#pragma once
#include "User.h"
#include "Field.h"


struct Player : User
{
	std::string password;
	Field field, EnemyField;
	int countWins = 0;
	
	std::vector<Ship> PlayerShips;

	Player()
	{
		password = "";
	}

	Player(std::string name)
		: User(name)
	{ }

	Player(std::string name, int countWins)
		: User(name), countWins(countWins)
	{ }

	Player(std::string name, std::string password, int countWins)
		: User(name), countWins(countWins), password(password)
	{ }

	bool operator<(Player& other)
	{
		return this->countWins < other.countWins;
	}

	bool operator>(Player& other)
	{
		return this->countWins > other.countWins;
	}
};