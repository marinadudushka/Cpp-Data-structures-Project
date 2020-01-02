#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <random>
#include <stack>
#include "Cell.h"
#include "Monster.h"
#include "Player.h"
#include "AStarNode.h"
#include "openListNode.h"

//add monster array 
//	enum DIRECTION {DOWN=1,RIGHT=1,LEFT=-1,UP=-1}; in the Monster.h


class Labyrinth
{
	//fields
	vector<string> Lab;//matrix
	int numberOfMonsters;
	int N, M,takenCells;
	
	vector<Monster> monstersInLabyrinth;

	Cell start, end;
	
	vector<Cell> playerPath;
	const char WALL = '#', FREE = '.',BLOCKED = '%';
private:
	//functions
	void countTakenCells();
	void printLabyrinth() const;
	bool createVisitedMatrix(vector<vector<bool>>&)const;
	void moveMonsters();

	bool cellHasMonster(Cell&);

	void putMonsters();//use rand to put monsters in labyrinth
	bool blockCells(vector<string>& temp);//user can block 
	
	double calculateH(int,int);

	bool cellValid(int ,int );
	bool cellIsFreeForMonster(Cell&);
	bool cellFree(Cell&);
	bool aStarCellCheck(int,int);
	bool isEnd(int, int);
	void aStarSearch();//search shortest path between start and end
	bool movePlayer(Player*);
	void setPlayerPath(Player*);
	
	void findSorceressPath(vector<vector<AStarNode>>);
	void sorceressPath();
	void magicianPath();
	void changeMagicianDirection(DIRECTION&);


public:
	Labyrinth();
	Labyrinth(vector<string>&  ,int K );
	Labyrinth(const Labyrinth&);
	Labyrinth& operator=(const Labyrinth&);
	bool operator>(const Labyrinth&);
	//~Labyrinth();
public:
	bool isValid() const;//check if the labyrinth is valid
	int numOfMonsters() const;
	int row() const;
	int col() const;
	bool playLevel(Player* );//true if leves is passed
};
