//Marina Dudushka 45488 1group

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int MAX_SIZE = 100;

struct node {
	int x, y;
	node(int _x, int _y) :x(_x), y(_y) {}
	node(const node& other) { x = other.x; y = other.y; }
	bool operator==(const node& other)
	{
		if (x == other.x&&y == other.y)
			return true;
		return false;
	}

};
// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
	node start(startX, startY), end(goalX, goalY);
	bool visited[MAX_SIZE][MAX_SIZE] = { false };
	int gridSize = grid.size();//number of rows and columns
	int minMoves = 0;
	queue<node> nodesToVisit;
	nodesToVisit.push(start);
	visited[start.x][start.y] = true;
	int currMoves = 1;
	while (!nodesToVisit.empty())
	{
		node current = nodesToVisit.front();
		nodesToVisit.pop();
		currMoves--;
		if (current == end)
		{
			return minMoves;
		}
		int tempX = current.x, tempY = current.y;

		//go up
		tempX--;
		while (tempX >= 0 && grid[tempX][tempY] != 'X')
		{
			if (!visited[tempX][tempY])
			{
				visited[tempX][tempY] = true;
				node temp(tempX, tempY);
				nodesToVisit.push(temp);
			}
			tempX--;
		}
		tempX = current.x;
		//go down
		tempX++;
		while (tempX<gridSize&&grid[tempX][tempY] != 'X')
		{
			if (!visited[tempX][tempY])
			{
				visited[tempX][tempY] = true;
				node temp(tempX, tempY);
				nodesToVisit.push(temp);
			
			}
			tempX++;
		}
		//go right, we haven't changed tempY
		tempX = current.x;
		tempY++;
		while (tempY<gridSize&&grid[tempX][tempY]!='X')
		{
			if (!visited[tempX][tempY])
			{
				visited[tempX][tempY] = true;
				node temp(tempX, tempY);
				nodesToVisit.push(temp);
			}
			tempY++;
		}
		//go left
		tempY = current.y;
		tempY--;
		while (tempY >= 0 && grid[tempX][tempY]!='X')
		{
			if (!visited[tempX][tempY])
			{
				visited[tempX][tempY] = true;
				node temp(tempX, tempY);
				nodesToVisit.push(temp);
	
			}
			tempY--;
		}
		
		if (currMoves == 0)
		{
			minMoves++;
			currMoves = nodesToVisit.size();
		}
		
	}
	return 0;
}

int main()
{
	cout << "enter n " << endl;
	int n;
	do {

		cin >> n;

	} while (n < 0 && n>100);
	cin.get();
	vector<string> grid(n);
	cout << "Write grid" << endl;
	for (int i = 0; i < n; i++) {
		string grid_item;
		getline(cin, grid_item);

		grid[i] = grid_item;
	}

	cout << "Write start and end" << endl;
	int startX,startY,endX,endY;
	do
	{
		cin >> startX >> startY >> endX >> endY;
	} while (startX < 0 || startX>99 || startY < 0 || startY>99 || endX < 0 || endX>99 || endY < 0 || endY>99);

	int result = minimumMoves(grid, startX, startY, endX, endY);

	cout << result << "\n";

	
	system("pause");
	return 0;
}
