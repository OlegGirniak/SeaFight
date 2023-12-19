#pragma once

struct Point
{
	int x;
	int y;

	Point() = default;

	Point(int x, int y) : x(x), y(y) { }

	bool operator==(Point& other) 
	{
		return (x == other.x) && (y == other.y);
	}

	bool operator!=(Point& other)
	{
		return (x != other.x) || (y != other.y);
	}
};