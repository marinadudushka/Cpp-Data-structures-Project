#pragma once
#include <fstream>
#include "Labyrinth.h"
#include "Player.h"

const string filename = "file.txt";

class Game
{
	vector<Labyrinth> levels;
	Player* player;
	int currentLevel;
	int numberOfLevels;
	void setPlayer(PLAYER_TYPE, string);
	void sort();//use cocktail sort
	void swap(Labyrinth&, Labyrinth&);
	void play();
public:
	Game();
	~Game();

};