#include "Sorceress.h"

Cell Sorceress::moveThroughMaze()
{
	Cell temp;
	if (currPosOnPath<pathLen)
	{
		Cell temp = position;
		position = path[currPosOnPath];
		currPosOnPath++;
	}
	return temp;//check if valid
}
