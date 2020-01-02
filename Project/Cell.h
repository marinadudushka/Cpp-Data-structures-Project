#pragma once
#include <iostream>
using namespace std;
struct Cell
{
	int x, y;
	
	Cell(int _x = 0, int _y = 0) :x(_x), y(_y) {}
	Cell(const Cell&other)
	{
		x = other.x;
		y = other.y;
		
	}
	Cell& operator=(const Cell& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
			
		}
		return *this;
	};
	bool operator==(const Cell& other)
	{
		if (x == other.x && y == other.y)
			return true;
		return false;
	}
	bool operator!=(const Cell& other)
	{
		return (x!=other.x&&y!=other.y);
	}


};