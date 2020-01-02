#pragma once
#include <iostream>
#include "Cell.h"
using namespace std;

enum DIRECTION { DOWN = 1, RIGHT, LEFT , UP  };
class Monster
{
	DIRECTION dir;
	Cell position;
	int limitX, limitY;//
public:
	Monster(Cell);
	void changeDirection();//change direction 
	Cell getMonsterPosition() const;
	DIRECTION getDirection() const;
	void moveMonster(Cell&);

};
