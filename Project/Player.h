#pragma once
#include <iostream>
#include <string>
#include <queue>
#include "Cell.h"
using namespace std;

enum PLAYER_TYPE {DEFAULT=0,SORCERESS,MAGICIAN};
class Player
{
protected:
	string name;
	PLAYER_TYPE type;
	vector<Cell> path;
	int pathLen, currPosOnPath;
	Cell position;//has a default constructor setting it to the start cell
public:
	Player(string = nullptr, PLAYER_TYPE = DEFAULT);
	Player(const Player&);
	Player& operator=(const Player&);

	Cell getPosition() const;
	void setPath(vector<Cell>& _path);
	 Cell moveThroughMaze();
	 PLAYER_TYPE getPlayerType();
	 string getName() const;
	
};