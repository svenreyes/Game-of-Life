// Life simulation
/*
  Nathaniel Ramirez
  Talal Elhitu
  Sven Reyes


*/




#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

const int MAXWORLDROWS = 25;
const int MAXWORLDCOLS = 80;
const int MAXROWS = MAXWORLDROWS + 2;
const int MAXCOLS = MAXWORLDCOLS + 2;
const int FILENAMESIZE = 255;

// ASCII characters to use for display
// https://theasciicode.com.ar/extended-ascii-code/block-graphic-character-ascii-code-219.html
// for interesting effect use code 219 and 176 instead of the asterisk and space
const unsigned char CELL = '*';  // 219;
const unsigned char EMPTY = ' '; // 176;

enum class State { dead = 0, alive = 1 };

/*
* initWorld is used to initialize all positions in the world
* array to the 'dead' state
*/
void initWorld(State world[][MAXCOLS]);


/*
* display is used to draw the 'world' onto the screen
* for each 'alive' cell, the value CELL is displayed
* for each 'dead' cell, the value EMPTY is displayed
* does NOT display any items in:
*   row 0, row MAXROWS-1, column 0, or column MAXCOLS-1
* since these rows and columns are used as a "border"
* around the world grid
*/
void display(State world[][MAXCOLS]);


/*
* getFile will get a filename from the user. It then attmpts
* to open the file, read its contents, and update the world
* based on the contents of the file. The file should contain
* only spaces and asterisks. A space represents a 'dead' cell
* and an asterisk represents an 'alive' cell.
* The function stops reading and exits the program if > MAXWORLDCOLS
* characters are found on one row, or if > MAXWORLDROWS rows are
* found in the file.
*/
void getFile(State world[][MAXCOLS]);

/*
* calcNewWorld is used to calculate the new state of the world
* (i.e. a new generation) based upon analyzing the current world state
*/
void calcNewWorld(State world[][MAXCOLS]);

/*
* neighborCount is used to count the number of 'alive' cells in
* the 8 neighboring positions which are surrounding position
* [row][col] in world
*/
int neighborCount(State world[][MAXCOLS], int row, int col);

/*
* This function takes two arrays as parameters, world and nWorld
* Then it goes through the entire world array and runs neighbor count ahead of time, and assigns those values to the nWorld array to be used in calcNewWorld.
*/
void neighborAssign(State world[][MAXCOLS], int nWorld[][MAXCOLS]);

int main()
{
	State world[MAXROWS][MAXCOLS];

	int generation = 0;
	bool stop = false;
	char userInput;

	// TODO: set up and initialize the 'world' array

	// function call for initializing the 'world' array to start the game
	initWorld(world);

	// function call to obtain the file name from user
	getFile(world);

	do
	{
		// system("cls") clears the screen; only works on Windows machines
		// You will probably need to comment this out if working on
		// a non-Windows machine
		system("cls");

		display(world);
		printf("\n");
		generation++;
		cout << "Generation: " << generation << "\t";
		cout << "<ENTER> to continue / <Q + ENTER> to quit: ";

		// TODO: get input from user and decide whether to quit the loop
		// and whether to compute a new generation

		// used to store the user's input
		cin.get(userInput);

		// unifies the case to get uppercase
		userInput = toupper(userInput);

		//check if user wants to quit the program
		if (userInput == 'Q' && cin.peek() == '\n')
		{
			// User wants to quit
			stop = true;
		}
		else if (userInput == '\n')
		{
			//this is used to make sure we know exactly what the value of stop would be at this point
			stop = false;

			// Compute a new generation
			calcNewWorld(world);
		}
		else
		{
			//this is used to make sure we know exactly what the value of stop would be at this point
			stop = false;

			//this ignores any character in the stream buffer so no matter what is inputted outside of 'q' or 'Q' the generation only advances by one
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}


	} while (!stop);

	return 0;
}

int neighborCount(State world[][MAXCOLS], int row, int col)
{
	// This code checks to make sure you aren't trying to count neighbors for any
	// position on row #0, or on row #MAXWORLDROWS+1,
	// or in column 0, or in columnn MAXWORLDCOLUMNS+1
	// because if you are, you are going to run into array out-of-bounds problems
	if (row < 1 || row > MAXWORLDROWS)
	{
		cerr << "ERROR: invalid row parameter " << row << " in neighborCount\n";
		exit(1);
	}
	else if (col < 1 || col > MAXWORLDCOLS)
	{
		cerr << "ERROR: invalid col parameter " << col << " in neighborCount\n";
		exit(1);
	}

	int i = 0;

	// TODO: write neighborCount code
	//this loops through the 9 positions in the array around the given row and column and increments the count for every alive cell in that area that is not the inital cell
	for (int _i = row - 1; _i <= row + 1; _i++)
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			if (!(_i == row && j == col) && world[_i][j] == State::alive)
			{
				i++;
			}
		}
	}
	return i;
}

void calcNewWorld(State world[][MAXCOLS])
{
	// TODO: write calcNewWorld code
	//creates an array to hold the neighbor count of each cell in the world array at the corresponding index
	int neighborArray[MAXROWS][MAXCOLS];

	//Sets the neighbor count of each cell in the world array to a corresponding index of the neighborArray
	neighborAssign(world, neighborArray);

	// This for loop goes through all of the elements in the 2D array to check every point in the world
	for (int j = 1; j < MAXWORLDROWS + 1; j++)
	{
		for (int k = 1; k < MAXWORLDCOLS + 1; k++)
		{

			// If an Alive cell's number of neighbors is 0 or 1, it dies of loneliness 
			// If an Alive cell's number of neighbors is 4 or higher, it dies of overcrowding
			if (world[j][k] == State::alive && (neighborArray[j][k] <= 1 || neighborArray[j][k] >= 4))
			{
				world[j][k] = State::dead;
			}
			// If the number of neighbors is 3 and there is no cell in the spot, a new cell is born in the spot 
			else if (world[j][k] == State::dead && neighborArray[j][k] == 3)
			{
				world[j][k] = State::alive;
			}
		}
	}
}

void getFile(State world[][MAXCOLS])
{
	char file[FILENAMESIZE];
	char line[MAXWORLDCOLS + 1];
	int row = 1;
	size_t lineSize;
	printf("Enter the name of the starter file you want to use: ");
	cin.getline(file, FILENAMESIZE);
	ifstream inFile(file);

	//This checks if the file could be opened, and if it can't then it generates the appropriate error message and then closes the file and exits the program
	if (!inFile.is_open())
	{
		cerr << "\nERROR: Input file cannot be opened\n";
		inFile.close();
		exit(1);
	}

	// TODO: Write getFile code
	// Make sure row is incremented each time you read a line from the file

	//This loop runs as long as the value of row is less than MAXWORLDROWS + 1 and there are more lines in the file to read and then increments row by 1 at the end
	while (row < MAXWORLDROWS + 1 && inFile.getline(line, MAXWORLDCOLS + 1))
	{
		//This get the length of the cstring gotten from the file 
		lineSize = strlen(line);
		//This loop runs through the cstring gotten from the file and then uses an if statement to check what character is in each index of the cstring
		for (int i = 0; i < lineSize; i++)
		{
			//checks to see if the character at index i in the cstring is equal to '*' if so then it assigns the alive state to the corresponding index of the 2d array
			if (line[i] == '*')
			{
				world[row][i + 1] = State::alive;
			}
			//checks to see if the character at the index is equal to ' ' if so then it assigns the dead state to the corresponding index of the 2d array
			else if (line[i] == ' ')
			{
				world[row][i + 1] = State::dead;
			}
			//if any other character is encountered then the state dead is assigned to the corresponding index of the 2d array
			else
			{
				world[row][i + 1] = State::dead;
			}
		}
		row++;
	}


	//Used to update the EndOfFile status by checking if there are more values in the file to read without extracting any characters
	inFile.peek();

	// After file reading is finished, this code checks to see if the reading stopped
	// because of too many characters on a line in the file, or too many rows in the file
	// It is possible that you might have to change the conditions here depending on
	// exactly how you choose to read the file
	if (!inFile.eof())
	{
		if (row <= MAXWORLDROWS)
		{
			cerr << "\nERROR: Line " << row << " in input file contains more than " << MAXWORLDCOLS << " chars\n";
		}
		else
		{
			cerr << "\nERROR: There are more than " << MAXWORLDROWS << " lines in the file\n";
		}
		inFile.close();
		exit(1);
	}

	inFile.close();
}

void display(State world[][MAXCOLS])
{
	// TODO: write the display code
	// loops through the rows and colums and prints the contents of the screen
	for (int row = 1; row < MAXWORLDROWS + 1; row++)
	{
		for (int col = 1; col < MAXWORLDCOLS + 1; col++)
		{
			if (world[row][col] == State::alive)
			{
				printf("%c", CELL);
			}
			else
			{
				printf("%c", EMPTY);
			}

		}
		cout << endl;
	}
}

void initWorld(State world[][MAXCOLS])
{
	// TODO: write initWorld code
	//loops through the entire world array to set every index as State::dead
	for (int x = 0; x < MAXROWS; x++)
	{
		for (int y = 0; y < MAXCOLS; y++)
		{
			world[x][y] = State::dead;
		}
	}
}

void neighborAssign(State world[][MAXCOLS], int nWorld[][MAXCOLS])
{
	//loops through the entire world array to assign the neighbor counts to the array holding the neighbor counts
	for (int _x = 1; _x < MAXWORLDROWS + 1; _x++)
	{
		for (int _y = 1; _y < MAXWORLDCOLS + 1; _y++)
		{
			nWorld[_x][_y] = neighborCount(world, _x, _y);
		}
	}

}