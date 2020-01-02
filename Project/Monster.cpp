#include "Monster.h"

Monster::Monster(Cell _pos)
{
	position = _pos;
	dir = UP;//starting direction is up;
}




void Monster::changeDirection()
{
	if (dir == UP)
		dir = LEFT;
	else if (dir == LEFT)
		dir = DOWN;
	else if (dir == DOWN)
		dir = RIGHT;
	else
		dir = UP;
}

Cell Monster::getMonsterPosition() const
{
	return position;
}

DIRECTION Monster::getDirection() const
{
	return dir;
}

void Monster::moveMonster(Cell & newPos)
{
	position = newPos;//this will be checked in labyrinth function for mooving monsters
}
