#pragma once
#include <string>

struct User
{
	std::string Name;

	User() = default;

	User(std::string name)
	{
		Name = name;
	}
};