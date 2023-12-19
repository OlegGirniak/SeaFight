#pragma once
#include <vector>
#include "Point.h"

struct Ship
{
	std::vector<Point> Coordinates;

	Ship()
	{

	}

	Ship& operator=(Ship other)
	{
		for (size_t i = 0; i < other.Coordinates.size(); i++)
		{
			this->Coordinates.push_back(other.Coordinates[i]);
		}

		return *this;
	}

	Ship(std::vector<Point>& points)
	{
		for (size_t i = 0; i < points.size(); i++)
		{
			this->Coordinates.push_back(points[i]);
		}
	}
};