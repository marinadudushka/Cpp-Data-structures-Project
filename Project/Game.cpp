#include "Game.h"

/*void Game::setPlayer(PLAYER_TYPE type, string name)
{
	
	player = new Player(name, type);
	
}*/

void Game::sort()
{
	bool swapped = true;
	int forwardPass, backwardPass, start, end;
	start = 0;
	end = numberOfLevels-1;
	while (swapped)
	{
		swapped = false;
		for (int i = start; i < end; i++)
		{
			if (levels[i] > levels[i + 1])
			{
				swap(levels[i], levels[i + 1]);
				swapped = true;
			}
		}
		if (swapped)
		{
			swapped = false;
			--end;
			for (int i = end-1; i > start; i--)
			{
				if (levels[i] > levels[i + 1])
				{
					swap(levels[i], levels[i + 1]);
					swapped = true;
				}
			}
			++start;
		}
	}
}

void Game::swap(Labyrinth &rhs, Labyrinth &lhs)
{
	Labyrinth temp(rhs);
	lhs = rhs;
	rhs = temp;
}

Game::Game()
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		cerr << "Couldn't load levels" << endl;
	while (!file.eof())
	{
		int N, M;
		file >> N >> M;
		file.get();
		vector<string> maze;
		for (int i = 0; i < N; i++)//create labyrinth/maze
		{
			string buff;
			getline(file, buff);
			maze.push_back(buff);
		}
		int K;
		file >> K;
		

		Labyrinth temp(maze, K);
		if (temp.isValid())
			levels.push_back(temp);
	}
	//sort them by size 
	//sort();
	currentLevel = 0;
	numberOfLevels = levels.size();
	cout << "Welcome to the game of Labyrinths! Please choose a character: \n for Magician enter 1 \n for  Sorceress enter 2." << endl;
	int choice;
	do
	{
		cin >> choice;
		cin.get();
	} while (!(choice != 1 || choice != 2));
	string name;
	cout << "Enter your name: " << endl;
	getline(cin, name);

	PLAYER_TYPE type;
	if (choice == 1)
		type = MAGICIAN;
	else 
		type = SORCERESS;
	player = new (nothrow) Player(name, type);
	if (!player)
		cerr << "Error with player" << endl;
	play();
	
}

Game::~Game()
{
	delete player;
}

void Game::play()
{
	bool gameOver = false;
	do {
		cout << "You are on level: " << currentLevel + 1 << endl;
		gameOver = levels[currentLevel].playLevel(player);
		currentLevel++;
	} while (!gameOver&&currentLevel<numberOfLevels);
	if (gameOver)
		cout << "Game over, " << player->getName() << "!" << endl;
}
