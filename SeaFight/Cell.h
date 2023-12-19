#pragma once
#include "CellType.h"

struct Cell
{
	CellType Sign;

	Cell()
	{
		Sign = CellType::Empty;
	}

	Cell(CellType cell)
	{
		Sign = cell;
	}
};