#pragma once

struct Cell
{
	bool hasMine = false;
	bool activated = false;
	bool hasFlag = false;
	int nearbyMines = 0;
};
