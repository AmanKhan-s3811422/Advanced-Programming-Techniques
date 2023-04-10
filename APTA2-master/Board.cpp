#include "Board.h"
#include <iostream>



void Board::init() {
	// Set up initial board with null pointers
	for (int c = 0; c < HEIGHT; c++) {
		std::vector<Node*> tmpRow;
		for (int r = 0; r < WIDTH; r++)
			tmpRow.push_back(nullptr);

		board.push_back(tmpRow);
	}
}

void Board::putTile(int row, int col, Node* const node) {
	board[row][col] = node;
	tileCount++;
}

Node* const Board::getTile(int row, int col) const {
	return board[row][col];
}

bool Board::hasTile(int row, int col) const {
	return (board[row][col] != nullptr);
}

bool Board::isSameColor(Node* const current, Node* const compare) {
	char c1 = current->tile->getTileCode().at(0);
	char c2 = compare->tile->getTileCode().at(0);

	return (c1 == c2);
}

bool Board::isSameShape(Node* const current, Node* const compare) {
	char c1 = current->tile->getTileCode().at(1);
	char c2 = compare->tile->getTileCode().at(1);

	return (c1 == c2);
}

bool Board::isDuplicate(Node* const current, Node* const compare) {
	char c1 = current->tile->getTileCode().at(0);
	char c2 = compare->tile->getTileCode().at(0);

	char s1 = current->tile->getTileCode().at(1);
	char s2 = compare->tile->getTileCode().at(1);

	return ((c1 == c2) && (s1 == s2));
}

bool Board::isRepeated(int row, int col, Node* const node) {
	bool left = false, up = false, right = false, down = false;

	// Check left for adjacent tile
	if (col - 1 >= 0)
		if (hasTile(row, col - 1))
			left = true;

	// Check up for adjacent tile
	if (row - 1 >= 0)
		if (hasTile(row - 1, col))
			up = true;

	// Check right for adjacent tile
	if (col + 1 < WIDTH)
		if (hasTile(row, col + 1))
			right = true;

	// Check down for adjacent tile
	if (row + 1 < HEIGHT)
		if (hasTile(row + 1, col))
			down = true;


	bool retStatus = false;
	bool loopExit = false;

	// If there is an adjacent tile to the left
	if (left)
	{
		// The horizontal line must be checked to the left
		for (int c = 0; c < col && !loopExit; c++)
			if (hasTile(row, c))
			{
				Node* const n = getTile(row, c);
				if (isDuplicate(node, n))
				{
					loopExit = true;
					retStatus = true;
				}
			}
	}

	// If there is an adjacent tile to the right
	else if (right)
	{
		// The horizontal line must be checked to the right
		loopExit = false;
		for (int c = WIDTH - 1; c >= col && !loopExit; c--)
			if (hasTile(row, c))
			{
				Node* const n = getTile(row, c);
				if (isDuplicate(node, n))
				{
					loopExit = true;
					retStatus = true;
				}
			}
	}

	// If there is an adjacent tile above
	else if (up)
	{
		// The vertical line must be checked above
		for (int r = 0; r < row && !loopExit; r++)
			if (hasTile(r, col))
			{
				Node* const n = getTile(r, col);
				if (isDuplicate(node, n))
				{
					loopExit = true;
					retStatus = true;
				}
			}

	}

	// If there is an adjacent tile below
	else if (down)
	{
		// The vertical line must be checked below
		for (int r = row + 1; r < HEIGHT && !loopExit; r++)
			if (hasTile(r, col))
			{
				Node* const n = getTile(r, col);
				if (isDuplicate(node, n))
				{
					loopExit = true;
					retStatus = true;
				}
			}

	}

	return retStatus;
}

bool Board::isSameColorLine(char direction, int row, int col, Node* const node) {
	bool retVal = false;

	char color = node->tile->colour;

	int count = 0;
	int tileCount = 0;

	bool loopExit = false;

	if (direction == 'l')
	{
		// Check the left line for tiles with the same colour
		for (int c = col - 1; c >= 0 && !loopExit; c--)
		{
			if (hasTile(row, c))
			{
				tileCount++;
				Node* t = getTile(row, c);
				if (color == t->tile->colour)
					count++;
			}
			else
				loopExit = true;
		}
	}
	else if (direction == 'r')
	{
		loopExit = false;
		//check the right line for tiles with the same colour
		for (int c = col + 1; c < WIDTH && !loopExit; c++)
		{
			if (hasTile(row, c))
			{
				tileCount++;
				Node* t = getTile(row, c);
				if (color == t->tile->colour)
					count++;
			}
			else
				loopExit = true;
		}
	}
	else if (direction == 'u')
	{
		loopExit = false;
		// Check the line above for tiles with the same colour
		for (int r = row - 1; r >= 0 && !loopExit; r--)
		{
			if (hasTile(r, col))
			{
				tileCount++;
				Node* t = getTile(r, col);
				if (color == t->tile->colour)
					count++;
			}
			else
				loopExit = true;
		}
	}
	else if (direction == 'd')
	{
		loopExit = false;
		// Check the line below for tiles with the same colour
		for (int r = row + 1; r < HEIGHT && !loopExit; r++)
		{
			if (hasTile(r, col))
			{
				tileCount++;
				Node* t = getTile(r, col);
				if (color == t->tile->colour)
					count++;
			}
			else
				loopExit = true;
		}
	}

	if (count > 0 && (tileCount == count))
		retVal = true;

	return retVal;
}

bool Board::isSameShapeLine(char direction, int row, int col, Node* const node) {
	bool retVal = false;

	int shape = node->tile->shape;

	int count = 0;
	int tileCount = 0;

	bool loopExit = false;

	if (direction == 'l')
	{
		// Check the left line for tiles with the same shape
		for (int c = col - 1; c >= 0 && !loopExit; c--)
		{
			if (hasTile(row, c))
			{
				tileCount++;
				Node* t = getTile(row, c);
				if (shape == t->tile->shape)
					count++;
			}
			else
				loopExit = true;
		}

	}
	else if (direction == 'r')
	{
		loopExit = false;
		// Check the right line for tiles with the same shape
		for (int c = col + 1; c < WIDTH && !loopExit; c++)
		{
			if (hasTile(row, c))
			{
				tileCount++;
				Node* t = getTile(row, c);
				if (shape == t->tile->shape)
					count++;
			}
			else
				loopExit = true;
		}
	}
	else if (direction == 'u')
	{
		loopExit = false;
		// Check the line above for tiles with the same shape
		for (int r = row - 1; r >= 0 && !loopExit; r--)
		{
			if (hasTile(r, col))
			{
				tileCount++;
				Node* t = getTile(r, col);
				if (shape == t->tile->shape)
					count++;
			}
			else
				loopExit = true;
		}
	}
	else if (direction == 'd')
	{
		loopExit = false;
		// Check the line below for tiles with the same shape
		for (int r = row + 1; r < HEIGHT && !loopExit; r++)
		{
			if (hasTile(r, col))
			{
				tileCount++;
				Node* t = getTile(r, col);
				if (shape == t->tile->shape)
					count++;
			}
			else
				loopExit = true;
		}
	}

	if (count > 0 && (tileCount == count))
		retVal = true;

	return retVal;
}

Board::Board() {
	init();
}

Board::Board(int width, int height) {
	WIDTH = width;
	HEIGHT = height;

	init();
}

Board::~Board() {

	// Traverse through the board and delete all nodes within the board
	for (int c = 0; c < HEIGHT; c++)
	{
		std::vector<Node*> tmpRow;
		for (int r = 0; r < WIDTH; r++)
			delete(board[c][r]);
	}

	// Remove all items in the board 
	board.clear(); 
}

void Board::drawBoard() {

	// Draw the columns header
	std::cout << "\n";
	std::cout << "  ";
	for (int col = 0; col < WIDTH; col++)
	{
		if (col < 10)
			std::cout << "  " << col;
		else
			std::cout << " " << col;
	}

	std::cout << std::endl;
	std::cout << "  ";
	
	// Seperator drawn
	for (int i = 0; i < WIDTH * 3; i++)
		std::cout << "-";

	std::cout << std::endl;

	// Traverse and draw the following rows
	for (int r = 0; r < HEIGHT; r++)
	{
		// Print the row header
		std::cout << (char)(r + 65) << " |";

		for (int c = 0; c < WIDTH; c++)
		{
			// Access each pointer within the vector and determine whether its blank or not
			Node* ptr = board[r][c];
			if (ptr == nullptr)
				std::cout << "  |";
			else
				std::cout << ptr->tile->getTileCode() << "|";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl << std::endl;
}

int Board::placeTile(const std::string coord, Node* const node, bool onlyCheckIfValidMove, bool* ptrIsKwirkle) {
	
	int retVal = 0;

	// Extracting column and row value as characters
	char r = coord.at(0);
	std::string x = coord.substr(1, coord.length() - 1);

	// Converting row and colums as integers
	int col = atoi(x.c_str());
	int row = r - 'A';
	
	// Check for valid row
	if (row < 0 || row >  HEIGHT)
		retVal = 0;

	// Check for valid column
	else if (col < 0 || col > WIDTH)
		retVal = 0;		
	
	// Check if it is the first tile placement
	else if (tileCount == 0)						
	{
		if (!onlyCheckIfValidMove)
			putTile(row, col, node);

		retVal = 1;
	}
	
	// Checks if there is already a tile placed in a given location
	else if (hasTile(row, col))
		retVal = 0;		
	
	else
	{
		//  Check for duplicate tiles in the same line
		if (isRepeated(row, col, node))
			retVal = 0;
		
		else
		{
			bool hasAdjLeftTile = false, hasAdjTileAbove = false, hasAdjTileRight = false, hasAdjTileBelow = false;

			// Check left for adjacent tiles
			if (col - 1 >= 0)
				if (hasTile(row, col - 1))
					hasAdjLeftTile = true;

			// Check up for adjacent tiles
			if (row - 1 >= 0)
				if (hasTile(row - 1, col))
					hasAdjTileAbove = true;

			// Check right for adjacent tiles
			if (col + 1 < WIDTH)
				if (hasTile(row, col + 1))
					hasAdjTileRight = true;

			// Check down for adjacent tiles
			if (row + 1 < HEIGHT)
				if (hasTile(row + 1, col))
					hasAdjTileBelow = true;

			bool leftLineValid = false, topLineValid = false, rightLineValid = false, bottomLineValid = false;

			retVal = 1;

			// If there is an adjacent tile to the left
			if (hasAdjLeftTile)
			{
				// Making sure the line contains same colour or shape
				if (!isSameColorLine('l', row, col, node) && !isSameShapeLine('l', row, col, node))
					retVal = 0;
				else
					leftLineValid = true;
			}

			// If there is an adjacent tile above
			if (hasAdjTileAbove && retVal != 0)
			{
				// Making sure the line contains same colour or shape
				if (!isSameColorLine('u', row, col, node) && !isSameShapeLine('u', row, col, node))
					retVal = 0;
				else
					topLineValid = true;

			}

			// If there is an adjacent tile to the right
			if (hasAdjTileRight && retVal != 0)
			{
				// Making sure the line contains same colour or shape
				if (!isSameColorLine('r', row, col, node) && !isSameShapeLine('r', row, col, node))
					retVal = 0;
				else
					rightLineValid = true;
			}

			// If there is an adjacent tile below
			if (hasAdjTileBelow && retVal != 0)
			{
				// Making sure the line contains same colour or shape
				if (!isSameColorLine('d', row, col, node) && !isSameShapeLine('d', row, col, node))
					retVal = 0;
				else
					bottomLineValid = true;
			}

			// Score calculation...

			int score = 0;
			int localScore = 0;
			int kwircle = 0;

			if (retVal == 0)
				;

			// retVal = 0 if placement is not valid
			else if (!leftLineValid && !topLineValid && !rightLineValid && !bottomLineValid)
				retVal = 0;

			// If the tile is to be placed
			else if (!onlyCheckIfValidMove)
			{
				putTile(row, col, node);

				
				bool endLoop = false;
				
				// Score calculation if there is a line to the left
				if (leftLineValid)
				{
					localScore = 1;
					// Look through the left row and set up score
					for (int c = col - 1; c >= 0 && !endLoop; c--)
					{
						if (!hasTile(row, c))
							endLoop = true;
						else
							localScore++;
					}

					// Is there a "Qwirkle"
					if (localScore == 6)
					{
						kwircle = 6;		
						*ptrIsKwirkle = true;
					}

					score += localScore;
				}

				endLoop = false;

				// Score calculation if there is a line to the right
				if (rightLineValid)
				{
					localScore = 1;
					// Look through the right row and set up score
					for (int c = col + 1; c < WIDTH && !endLoop; c++)
					{
						if (!hasTile(row, c))
							endLoop = true;
						else
							localScore++;

					}

					// Is there a "Qwirkle"
					if (localScore == 6)
					{
						kwircle = 6;
						*ptrIsKwirkle = true;
					}

					score += localScore;
				}

				endLoop = false;

				// Score calculation if there is a line above
				if (topLineValid)
				{
					localScore = 1;
					// Look through the row above and set up score
					for (int r = row - 1; r >= 0 && !endLoop; r--)
					{
						if (!hasTile(r, col))
							endLoop = true;
						else
							localScore++;
					}

					// Is there a "Qwirkle"
					if (localScore == 6)
					{
						kwircle = 6;
						*ptrIsKwirkle = true;
					}

					score += localScore;
				}


				endLoop = false;

				// Score calculation if there is a line below
				if (bottomLineValid)
				{
					localScore = 1;
					// Look through the row below and set up score
					for (int r = row + 1; r < HEIGHT && !endLoop; r++)
					{
						if (!hasTile(r, col))
							endLoop = true;
						else
							localScore++;
					}

					// Is there a "Qwirkle"
					if (localScore == 6)
					{
						kwircle = 6;
						*ptrIsKwirkle = true;
					}
					score += localScore;
				}

				
				if ((leftLineValid || rightLineValid) && (topLineValid || bottomLineValid))
					score *= 1;

				// Bonus points added if there is a "Qwirkle"
				score += kwircle;

				retVal = score;
			}
			else
				retVal = 1;			
		}
	}

	return retVal;
}

std::string Board::getCurrentBoardShape() {
	std::stringstream str;
	str << WIDTH << "," << HEIGHT;
	return str.str();
}

std::string Board::getCurrentBoardState() {
	std::stringstream str;

	for (int c = 0; c < HEIGHT; c++)
		for (int r = 0; r < WIDTH; r++)
		{
			Node* tmp = board[r][c];
			if (tmp != nullptr)
			{
				std::string tileCode = tmp->tile->getTileCode();
				char row = 'A' + r;

				str << tileCode << "@" << row << c << ",";
			}
		}


	// Get the final string
	std::string stateString = str.str();

	// Remove the last comma and space
	if (stateString.length() > 0)
		stateString = stateString.substr(0, stateString.length() - 1);

	return stateString;
}