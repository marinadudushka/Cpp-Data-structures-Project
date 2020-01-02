#include "Labyrinth.h"
#include <limits.h>
void Labyrinth::countTakenCells() 
{
	takenCells = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Lab[i][j] == WALL)
				takenCells++;
		}
	}
}

void Labyrinth::printLabyrinth() const
{
	for (int i = 0; i < N; i++)
	{
		cout << Lab[i] << endl;

	}
}

bool Labyrinth::createVisitedMatrix(vector<vector<bool>>& visited) const
{
	for (int i = 0; i < N; i++)
	{
		vector<bool> tempRow;
		for (int j = 0; j < M; j++)
		{
			if (Lab[i][j] != WALL && Lab[i][j] != FREE&&Lab[i][j]!=BLOCKED)
				return false;
			if (Lab[i][j] == WALL)
				tempRow.push_back(true);
			if (Lab[i][j] == FREE)
				tempRow.push_back(false);
		}
		visited.push_back(tempRow);
	}
}

void Labyrinth::moveMonsters()
{
	for (int i = 0; i < numberOfMonsters; i++)
	{
		Cell currPos = monstersInLabyrinth[i].getMonsterPosition();
		Cell tempPos = currPos;
		bool newPosSet = false;
		while (!newPosSet)
		{
			DIRECTION currDir = monstersInLabyrinth[i].getDirection();

			if (currDir == UP)
			{
				Cell temp(currPos.x - 1, currPos.y);
				if (cellIsFreeForMonster(temp))
				{
					
					monstersInLabyrinth[i].moveMonster(temp);
					newPosSet = true;
				}
				else
					monstersInLabyrinth[i].changeDirection();

			} 
			else if (currDir == DOWN)
			{
				Cell temp(currPos.x + 1, currPos.y);
				if (cellIsFreeForMonster(temp))
				{
					
					monstersInLabyrinth[i].moveMonster(temp);
					newPosSet = true;
				}
				else
					monstersInLabyrinth[i].changeDirection();

			}
			else if (currDir == LEFT )
			{
				Cell temp(currPos.x, currPos.y +1);
				if (cellIsFreeForMonster(temp))
				{
					
					monstersInLabyrinth[i].moveMonster(temp);
					newPosSet = true;
				}
				else
					monstersInLabyrinth[i].changeDirection();
			}
			else if (currDir == RIGHT)
			{
				Cell temp(currPos.x, currPos.y -1);
				if (cellIsFreeForMonster(temp))
				{
					
					monstersInLabyrinth[i].moveMonster(temp);
					newPosSet = true;
				}
				else
					monstersInLabyrinth[i].changeDirection();
			}
		}
	}
}

bool Labyrinth::cellHasMonster(Cell &cell)
{
	int monstNum = monstersInLabyrinth.size();
	for (int i = 0; i < monstNum ; i++)
	{
		if (cell == monstersInLabyrinth[i].getMonsterPosition())
			return true;
	}
	return false;
}

void Labyrinth::putMonsters()
{
	int tempNumOfMonst = numberOfMonsters;
	int posX, posY;
	while (tempNumOfMonst > 0)
	{
		posX = rand() % N;
		posY = rand() % M;
		Cell pos(posX, posY);
		if (cellIsFreeForMonster(pos)&&pos!=start&&Lab[pos.x][pos.y]!=BLOCKED)//monsters are placed in free and not blocked cells, but can move through blocked cells
		{
			monstersInLabyrinth.push_back(pos);
			--tempNumOfMonst;

		}
	}
}

bool Labyrinth::blockCells(vector<string>& temp)
{
	
	for (int i = 0; i < N; i++)
	{
		temp.push_back(Lab[i]);
	}
	int F;
	do
	{
		cout << "How many cells do you want to block?" << endl;
		cin >> F;

	} while (F<0 || F>N*M - takenCells - 2 - numberOfMonsters);
	for (int i = 0; i < F; i++)
	{
		int x, y;
	
		do
		{
			cout << "Enter valid coordinates :" << endl;
			cin >> x >> y;
			
		} while (!(cellValid(x,y) && temp[x][y]=='.'));
		temp[x][y] = BLOCKED;
	}
	Labyrinth check(temp, numberOfMonsters);
	return check.isValid();
}

double Labyrinth::calculateH(int x,int y)
{
	double H = abs(x - end.x) + abs(y - end.y);
	return H;
}







bool Labyrinth::cellValid(int x,int y)
{
	if (x >= 0 && y >= 0 && x <= N - 1 && y <= M - 1)
		return true;
	return false;
}

bool Labyrinth::cellIsFreeForMonster(Cell &monstPos)
{
	return cellValid(monstPos.x,monstPos.y)&&Lab[monstPos.x][monstPos.y]!=WALL&& !cellHasMonster(monstPos);

	return false;
}

bool Labyrinth::cellFree(Cell & c)
{
	return cellValid(c.x,c.y) && !cellHasMonster(c) && Lab[c.x][c.y] == '.';
}

bool Labyrinth::aStarCellCheck(int x,int y)
{
	return cellValid(x, y)&&Lab[x][y]=='.';
}

bool Labyrinth::isEnd(int x, int y)
{
	return x == end.x && y == end.y;
}

void Labyrinth::aStarSearch()
{
	vector<vector<bool>> closedList;
	bool created = createVisitedMatrix(closedList);
	vector<vector<AStarNode>> nodeDetails;
	if (!created)
		cerr << "Couldn't create visited matrix" << endl;
	for (int i = 0; i < N; i++)
	{	
		vector<AStarNode> row;
		for (int j = 0; j < M; j++)
		{
			AStarNode temp;
			temp.f = FLT_MAX;
			temp.g = FLT_MAX;
			temp.h = FLT_MAX;
			temp.parent.x = -1;
			temp.parent.y = -1;
			row.push_back(temp);
		}
		nodeDetails.push_back(row);
	}
	int i = start.x;
	int j = start.y;
	nodeDetails[i][j].f = 0.0;
	nodeDetails[i][j].g = 0.0;
	nodeDetails[i][j].h = 0.0;
	nodeDetails[i][j].parent.x = i;
	nodeDetails[i][j].parent.y = j;
	vector<openListNode> openList;
	openListNode node(0.0, start);
	openList.push_back(node);

	
	
	while (!openList.empty())
	{
		std::vector<openListNode>::iterator minEl = openList.begin();

		for (std::vector<openListNode>::iterator iterate = openList.begin(); iterate != openList.end(); ++iterate)
		{
			if (iterate->f < minEl->f)
			{
				minEl = iterate;
			}
		}

		openListNode p = *minEl;
		openList.erase(minEl);
		i = p.cell.x;
		j = p.cell.y;
		closedList[i][j] = true;

		double gNew, fNew, hNew;
		//UP -1
		Cell currCell(i, j);
		if (aStarCellCheck(i -1, j))
		{
			if (isEnd(i -1, j))
			{
				// Set the Parent of the destination cell 
				nodeDetails[i -1][j].parent.x = i;
				nodeDetails[i -1][j].parent.y = j;
				findSorceressPath(nodeDetails);
				return;
			}
	
			else if (closedList[i -1][j] == false &&aStarCellCheck(i -1, j))
			{
				gNew = nodeDetails[i][j].g + 1.0;
				hNew = calculateH(i-1,j);
				fNew = gNew + hNew;
				if (nodeDetails[i - 1][j].f == FLT_MAX || nodeDetails[i -1][j].f > fNew)
				{
					Cell pair(i - 1, j);
					openListNode temp(fNew, pair);
					openList.push_back(temp);

					nodeDetails[i -1][j].f = fNew;
					nodeDetails[i -1][j].g = gNew;
					nodeDetails[i -1][j].h = hNew;
					nodeDetails[i -1][j].parent.x = i;
					nodeDetails[i -1][j].parent.x = j;
				}
			}
		}

		// DOWN +1
		if (aStarCellCheck(i + 1, j))
		{
			if (isEnd(i + 1, j))
			{
				nodeDetails[i + 1][j].parent.x = i;
				nodeDetails[i + 1][j].parent.y = j;
				findSorceressPath(nodeDetails);
				return;
			}
			
			else if (closedList[i + 1][j] == false &&
				aStarCellCheck(i + 1, j))
			{
				gNew = nodeDetails[i][j].g + 1.0;
				hNew = calculateH(i + 1,j);
				fNew = gNew + hNew;
				if (nodeDetails[i + 1][j].f == FLT_MAX || nodeDetails[i + 1][j].f > fNew)
				{
					Cell pair(i + 1, j);
					openListNode temp(fNew, pair);
					openList.push_back(temp);

					nodeDetails[i + 1][j].f = fNew;
					nodeDetails[i + 1][j].g = gNew;
					nodeDetails[i + 1][j].h = hNew;
					nodeDetails[i + 1][j].parent.x = i;
					nodeDetails[i + 1][j].parent.y = j;
				}
			}
		}


		//LEFT -1
		if (aStarCellCheck(i, j -1))
		{
			if (isEnd(i, j - 1))
			{
				nodeDetails[i][j - 1].parent.x = i;
				nodeDetails[i][j - 1].parent.y = j;
				findSorceressPath(nodeDetails);
				return;
			}
			
			else if (closedList[i][j - 1] == false &&
				aStarCellCheck(i, j - 1))
			{
				gNew = nodeDetails[i][j].g + 1.0;
				hNew = calculateH(i,j-1);
				fNew = gNew + hNew;
				if (nodeDetails[i][j - 1].f == FLT_MAX || nodeDetails[i][j - 1].f > fNew)
				{
					Cell pair(i, j - 1);
					openListNode temp(fNew, pair);
					openList.push_back(temp);

					nodeDetails[i][j - 1].f = fNew;
					nodeDetails[i][j - 1].g = gNew;
					nodeDetails[i][j - 1].h = hNew;
					nodeDetails[i][j - 1].parent.x = i;
					nodeDetails[i][j - 1].parent.y = j;
				}
			}
		}

	
	//RIGHT
	if (aStarCellCheck(i, j + 1))
	{
		if (isEnd(i, j + 1))
		{
			nodeDetails[i][j + 1].parent.x = i;
			nodeDetails[i][j + 1].parent.y = j;
			findSorceressPath(nodeDetails);
			return;
		}
		else if (closedList[i][j + 1] == false &&
			aStarCellCheck(i, j + 1))
		{
			gNew = nodeDetails[i][j].g + 1.0;
			hNew = calculateH(i,j+1);
			fNew = gNew + hNew;
			if (nodeDetails[i][j + 1].f == FLT_MAX || nodeDetails[i ][j+1].f > fNew)
			{
				Cell pair(i, j + 1);
				openListNode temp(fNew, pair);
				openList.push_back(temp);

				nodeDetails[i][j + 1].f = fNew;
				nodeDetails[i][j + 1].g = gNew;
				nodeDetails[i][j + 1].h = hNew;
				nodeDetails[i][j + 1].parent.x = i;
				nodeDetails[i][j + 1].parent.y = j;
			}
		}
	}
	}

}

bool Labyrinth::movePlayer(Player *pl)
{
	Cell currPos;
	do
	{
		currPos = pl->moveThroughMaze();

	} while (cellValid(currPos.x,currPos.y) && !cellHasMonster(currPos)&&currPos!=end);
	if (currPos == end)
		return false;//not gameOver yet
	return true;//game over
}

void Labyrinth::setPlayerPath(Player *pl)
{
	pl->setPath(playerPath);
}

Labyrinth::Labyrinth()
{
	numberOfMonsters = 0;
	N = M = takenCells = 0;
	
}

Labyrinth::Labyrinth(vector<string>& maze,int K)
{
	
	N = maze.size();
	M = maze[0].size();
	for (int i = 0; i < N; i++)
	{
		Lab.push_back( maze[i]);
	}
	numberOfMonsters = K;
	countTakenCells();
	Cell tempStart(0, 0);
	Cell tempEnd(N - 1, M - 1);
	start = tempStart;
	end = tempEnd;


}
Labyrinth::Labyrinth(const Labyrinth &other)
{
	N = other.N;
	M = other.M;
	for (int i = 0; i < N; i++)
	{
		Lab.push_back(other.Lab[i]);
	}
	numberOfMonsters = other.numberOfMonsters;
	monstersInLabyrinth = other.monstersInLabyrinth;
	playerPath = other.playerPath;
	start = other.start;
	end = other.end;
}
Labyrinth & Labyrinth::operator=(const Labyrinth &other)
{
	if (this != &other)
	{
		Lab.clear();
		monstersInLabyrinth.clear();
		N = other.N;
		M = other.M;
		for (int i = 0; i < N; i++)
		{
			Lab.push_back(other.Lab[i]);
		}
		numberOfMonsters = other.numberOfMonsters;
		for (int i = 0; i < numberOfMonsters; i++)
		{
			monstersInLabyrinth[i] = other.monstersInLabyrinth[i];
		}
		playerPath = other.playerPath;
		start = other.start;
		end = other.end;
	}
	return *this;
}
bool Labyrinth::operator>(const Labyrinth &rhs)
{
	if (M*N > rhs.M*rhs.N)
		return true;
	else if (M*N == rhs.M*rhs.N)
		return numberOfMonsters > rhs.numberOfMonsters;
	return false;
}
int Labyrinth::numOfMonsters() const
{
	return numberOfMonsters;
}
int Labyrinth::row() const
{
	return N;
}
int Labyrinth::col() const
{
	return M;
}

bool Labyrinth::playLevel(Player* pl)
{
	printLabyrinth();
	bool restart = false;
	do {
		cout << "Do you want to block any cells? Y/N" << endl;
		string answer;
		do
		{
			getline(cin, answer);
		} while (!(answer == "Y" || answer == "N"));
		if (answer == "Y")
		{
			vector<string> temp;
			restart = blockCells(temp);
			if (restart)
			{
				for (int i = 0; i < N; i++)
					Lab[i] = temp[i];
			}
			else
			{
				cout << "Level restarted!" << endl;
				restart = true;
			}
		}
		
	} while (restart);
	PLAYER_TYPE type = pl->getPlayerType();
	if (type == SORCERESS)
	{
		sorceressPath();
		pl->setPath(playerPath);
	}
	else if (type == MAGICIAN)
	{
		magicianPath();
		pl->setPath(playerPath);
	}
	putMonsters();

	return movePlayer(pl);
}




void Labyrinth::findSorceressPath(vector<vector<AStarNode>> nodeDetails)
{
	vector<Cell> path;
	int row = end.x;
	int col = end.y;
	while (!(nodeDetails[row][col].parent.x == row	&& nodeDetails[row][col].parent.y == col))
	{
		Cell temp(row, col);
		path.push_back(temp);
		int tempRow = nodeDetails[row][col].parent.x;
		int tempCol = nodeDetails[row][col].parent.y;
		row = tempRow;
		col = tempCol;
		
	}
	Cell temp2(row, col);
	path.push_back(temp2);
	int pathLen = path.size();
	
	for (int i = 0; i < pathLen; i++)
	{
		playerPath.push_back(path[i]);
	}
}

void Labyrinth::sorceressPath()
{
	aStarSearch();
}

void Labyrinth::magicianPath()
{
	//DFS
	vector<vector<bool>> visited;
	
	bool isCreated = createVisitedMatrix(visited);
	if(!isCreated)
		return ;
	stack<Cell> s;
	s.push(start);
	DIRECTION dir = DOWN;
	vector<Cell> currPath;
	bool changeDir = false;
	bool deadEnd = false;
	while (!s.empty())
	{
		Cell curr = s.top();
		s.pop();
		currPath.push_back(curr);
		if (curr == end)
		{
			
			int len = currPath.size();
			for (int i = 0; i < len; i++)
			{
				playerPath.push_back(currPath[i]);
			}
			return ;
		}
		
		if (cellValid(curr.x - 1, curr.y) && visited[curr.x - 1][curr.y] == false)
		{
			Cell temp(curr.x - 1, curr.y);
			s.push(temp);
			visited[curr.x - 1][curr.y] = true;
		}
		
		if (cellValid(curr.x + 1, curr.y) && visited[curr.x + 1][curr.y] == false)
		{
			Cell temp(curr.x + 1, curr.y);
			s.push(temp);
			visited[curr.x + 1][curr.y] = true;
		}		
		if (cellValid(curr.x, curr.y + 1) && visited[curr.x][curr.y + 1] == false)
		{
					Cell temp(curr.x, curr.y + 1);
					s.push(temp);
					visited[curr.x][curr.y + 1] = true;
		}
		if (cellValid(curr.x, curr.y - 1) && visited[curr.x][curr.y - 1] == false)
		{
			Cell temp(curr.x, curr.y - 1);
			s.push(temp);
			visited[curr.x][curr.y - 1] = true;
		}
			
	}
}

void Labyrinth::changeMagicianDirection(DIRECTION& dir)
{

	if (dir == DOWN)
		dir = RIGHT;
	else if (dir == RIGHT)
		dir = LEFT;
	else if (dir == LEFT)
		dir = UP;
	else
		dir = DOWN;
}

bool Labyrinth::isValid() const
{
	
	if(Lab[0][0]!='.'||Lab[N-1][M-1]!='.'||(numberOfMonsters>=N*M - 1 - takenCells))
		return false;
	

	else
	{
		Cell start(0, 0), end(N - 1, M - 1);
		vector<vector<bool>> visited;
		//initialize visited bool matrix
		bool created = createVisitedMatrix(visited);
		//check if path exists between start and end
		queue<Cell> q;
		q.push(start);
		if (!created)
			cerr << "couldn't create visited bool matrix!" << endl;
		while (!q.empty())
		{
			Cell curr = q.front();
			int tempX = curr.x, tempY = curr.y;
			q.pop();
			visited[0][0] = true;

			if (curr == end)
				return true;
			//go up
			tempX--;
			while (tempX >= 0 && Lab[tempX][tempY] != WALL)
			{
				if (!visited[tempX][tempY])
				{
					visited[tempX][tempY] = true;
					Cell temp(tempX, tempY);
					q.push(temp);
				}
				tempX--;
			}
			tempX = curr.x;
			//go down
			tempX++;
			while (tempX<N&&Lab[tempX][tempY] != WALL)
			{
				if (!visited[tempX][tempY])
				{
					visited[tempX][tempY] = true;
					Cell temp(tempX, tempY);
					q.push(temp);

				}
				tempX++;
			}
			//go right, we haven't changed tempY
			tempX = curr.x;
			tempY++;
			while (tempY<M&&Lab[tempX][tempY] != WALL)
			{
				if (!visited[tempX][tempY])
				{
					visited[tempX][tempY] = true;
					Cell temp(tempX, tempY);
					q.push(temp);
				}
				tempY++;
			}
			//go left
			tempY = curr.y;
			tempY--;
			while (tempY >= 0 && Lab[tempX][tempY] != WALL)
			{
				if (!visited[tempX][tempY])
				{
					visited[tempX][tempY] = true;
					Cell temp(tempX, tempY);
					q.push(temp);

				}
				tempY--;
			}
		}
		return false;
	}

}



