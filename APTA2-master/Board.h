#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Node.h"

#include <vector>
#include <string>
#include <memory>

class Board {

private:
	int WIDTH = 26;
	int HEIGHT = 26;

	int tileCount = 0;

	std::vector<std::vector<Node*> > board;


	// Initialisinig the board
	void init();

	// Returns the pointer to the node of the given cordinate
	Node* const getTile(int row, int col) const;

	// Returns true if a tile exist in the given cordinate
	bool hasTile(int row, int col) const;

	// Returns true if any two tiles are of the same colour
	bool isSameColor(Node* const current, Node* const compare);

	// Returns true if any two tiles are of the same shape
	bool isSameShape(Node* const current, Node* const compare);

	// Returns true comparing tiles are identical (same shape and colour)
	bool isDuplicate(Node* const current, Node* const compare);

	// Returns true if the passing tile is repeated atleast in 1 direction from up ,right, left, down
	bool isRepeated(int row, int col, Node* const node);

	// Returns true if all the tiles in a line of a given direction have the same colour
	bool isSameColorLine(char direction, int row, int col, Node* const node);

	// Returns true if all the tiles in a line of a given direction have the same shape
	bool isSameShapeLine(char direction, int row, int col, Node* const node);



public:
	Board();
	Board(int width, int height);
	~Board();

	// Draws the board on the console output as string
	void drawBoard();

	// Places the tile on the board, if the move is valid the score is calculated and returned, otherwise 0 score is returned
	int placeTile(const std::string coord, Node* const node, bool onlyCheckIfValidMove, bool* ptrIsKwirkle);

	/**
	 * Returns the dimensions of the board (height and width)
	 * Board always has square dimensions, therefore only the height
	 * is returned as the width will be the same
	 * NOTE: max dimensions is 26x26
	 */
	std::string getCurrentBoardShape();				

	/**
	 * Returns the state of the board:
	 * the tile and its position on the board in the format tile@position
	 * e.g. B4@B2
	 */
	std::string getCurrentBoardState();


	// Places a tile on the board at a particular location
	void putTile(int row, int col, Node* const node);


};
#endif // ASSIGN2_BOARD_H