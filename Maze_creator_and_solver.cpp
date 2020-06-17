
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

int RoadOrWall() // Random Creator
{
	switch (rand() % 3)
	{
	case 0:
		return -2;  // Insert Wall
		break;
	case 1:
		return -2;  // Insert Wall
		break;
	case 2:
		return 0;   // Insert Road
		break;
	}
}

void createMaze(int** m, int x, int y, int r_c)  // Realistic Creator
{
	int s = 0, rnd, fx, fy;
	fx = x; // First X
	fy = y; // First Y
	for (int i = 0; i < 2; i++) // Adding long roads at two times
	{
		x = fx; // Back to First X
		y = fy; // Back to First Y
		while (x != 0 && x != r_c - 1 && y != r_c - 1 && y != 0) // Adding one road while floor exist
		{
			if (s == 0) { rnd = rand() % 4; } // Choose direction by random
			switch (rnd)
			{
			case 0:
				if (m[x - 1][y] != -1) { m[--x][y] = 0; } // left
				break;
			case 1:
				if (m[x + 1][y] != -1) { m[++x][y] = 0; } // right
				break;
			case 2:
				if (m[x][y + 1] != -1) { m[x][++y] = 0; } // forward
				break;
			case 3:
				if (m[x][y - 1] != -1) { m[x][--y] = 0; } // backward
				break;
			}
			if (s == 1) { s = 0; } // Same direction at two times
			else { s++; }
		}
	}

}

void inMaze(int** m, int r_c, int mod) // Mod 0: Random mode | Mod 1: Realistic mode | Mode 2: Show Maze | Mod 3: find Ýmpossible steps
{
	int c;
	for (int i = 0; i < r_c; i++) // Row
	{
		for (int j = 0; j < r_c; j++)  // Column
		{
			switch (mod)
			{
			case 0:
				m[i][j] = RoadOrWall();  // Random  Mode
				break;
			case 1:
				m[i][j] = -2;            // Realistic Mode | Firstly adding 'x' for every step
				break;
			case 2:						 // Show maze  |  -1 = '*'  -2 = 'x'   -3= 'u';
				c = m[i][j];
				switch (c)
				{
				case -1:
					cout << setw(3) << left << '*';
					break;
				case -2:
					cout << setw(3) << left << 'x';
					break;
				case -3:
					cout << setw(3) << left << 'u';
					break;
				default:
					cout << setw(3) << left << c;
					break;
				}
				break;
			case 3:								// Find impossible steps
				if (m[i][j] == 0) { m[i][j] = -3; }
				break;
			}
		}
		if (mod == 2) { cout << endl << endl; } // new column
	}
	if (mod == 2) { cout << endl; } // end of process
}

void solveMaze(int** m, int x, int y, int step, int r_c)
{
	if (m[x][y] == 0 || m[x][y] > step || m[x][y] == -1)  // Solve while road exist
	{

		if (m[x][y] != -1) { m[x][y] = ++step; } // if it is not first location : Write current step

		if (x != 0) { solveMaze(m, x - 1, y, step, r_c); } // left
		if (x != r_c - 1) { solveMaze(m, x + 1, y, step, r_c); } // right
		if (y != r_c - 1) { solveMaze(m, x, y + 1, step, r_c); } // forward
		if (y != 0) { solveMaze(m, x, y - 1, step, r_c); } // backward
	}
}

int** setMatrix(int r_c)
{
	int** m;

	m = new int*[r_c]; //row
	for (int i = 0; i < r_c; i++)
		m[i] = new int[r_c];  //column

	return m;
}

int main()
{
	srand(time(NULL));

	int** maze;
	int row_column, MStyle;
	do                                     // Specify Row and Column
	{
		cout << "Row and Column ( NxN ) : ";
		cin >> row_column;
	} while (row_column <= 2);
	system("cls");

	maze = setMatrix(row_column);

	do                                     // Specify Mod
	{
		cout << "         Create maze \n 0 = Random |  1 = Realistic \n\nChoose : ";
		cin >> MStyle;
	} while (MStyle != 0 && MStyle != 1);
	system("cls");

	inMaze(maze, row_column, MStyle);

	int Fx, Fy, DArea = -2;
	do                                     // Specify First Location
	{
		Fx = rand() % (row_column - 2) + 1;
		Fy = rand() % (row_column - 2) + 1;			    //                      -2   *   0                        -2   *   1
	} while (maze[Fx][Fy] != DArea * MStyle); //DArea = -2 && Random : DArea * MStyle = 0 || Realistic : DArea * MStyle = -2
	maze[Fx][Fy] = -1;						// deploy human

	if (MStyle == 1) { createMaze(maze, Fx, Fy, row_column); }

	inMaze(maze, row_column, 2);  // Show maze

	solveMaze(maze, Fx, Fy, 0, row_column); // Solve maze

	if (MStyle == 0) { inMaze(maze, row_column, 3); }  // find impossible steps : fix them ( change with 'u')

	inMaze(maze, row_column, 2);  // reShow maze
}


