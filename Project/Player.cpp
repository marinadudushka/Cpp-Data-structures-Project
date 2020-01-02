#include "Player.h"

Player::Player(string _name, PLAYER_TYPE _type) :pathLen(0), currPosOnPath(0), position(Cell(0, 0)) 
{
	name = _name;
	type = _type;
}

Player::Player(const Player &other)
{
	pathLen = other.pathLen;
	currPosOnPath = other.currPosOnPath;
	name = other.name;
	type = other.type;
	position = other.position;
}

Player & Player::operator=(const Player &other)
{
	if (this != &other)
	{
		pathLen = other.pathLen;
		currPosOnPath = other.currPosOnPath;
		name = other.name;
		type = other.type;
		position = other.position;
	}
	return *this;
	// TODO: insert return statement here
}

Cell Player::getPosition() const
{
	return position;
}

void Player::setPath(vector<Cell>& _path)
{
	pathLen = _path.size();
	for(int i =0;i<pathLen;i++)
	path.push_back( _path[i]);
}

Cell Player::moveThroughMaze()
{
	Cell temp;
	if (currPosOnPath<pathLen)
	{
		temp.x = position.x;
		temp.y = position.y;
		currPosOnPath++;
		position.x = path[currPosOnPath].x;
		position.y = path[currPosOnPath].y;
		return temp;
	}
	return Cell(-1, -1);
}

PLAYER_TYPE Player::getPlayerType()
{
	return type;
}

string Player::getName() const
{
	return name;
}
