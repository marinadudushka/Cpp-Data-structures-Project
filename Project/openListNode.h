#pragma once
#include "Cell.h"
struct openListNode
{
	Cell cell;
	double f;
	openListNode(double _f, Cell& _c):f(_f),cell(_c){}
};