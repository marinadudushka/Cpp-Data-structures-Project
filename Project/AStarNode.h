#pragma once
#include "Cell.h"

struct AStarNode
{
	Cell parent;
	double g;
	double h;
	double f;
	
};

