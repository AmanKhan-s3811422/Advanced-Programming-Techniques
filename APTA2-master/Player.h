#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include "TileBag.h"
#include "Board.h"

#include <string>

class Player {
private:

	int score;
	std::string name;
	LinkedList* playersHand = nullptr;
	TileBag* tileBag = nullptr;
	Board* board = nullptr;



	// Preventing copies of a player from being made
	Player(const Player& p) = delete;


public:

	Player(TileBag* const ptrTileBag, Board* const ptrBoard);
	~Player();

	// Set up the inital player hand
	void init();
	
	// Set the score of the player
	void setScore(int score);

	// Get the score of the player
	int getScore();

	// Set the name of the player
	void setName(std::string name);

	// Get the name of the player
	std::string getName() const;

	// Returns the tiles in the players hand as a string and prints it 
	std::string showPlayersHand() const;

	// Returns the tiles in the players hand
	std::string getPlayersHand() const;

	/**
	* Player attemps to place a tile on the board
	* Returns true if placement is valid
	* Returns false is placement is not valid
	*/
	bool placeTile(const std::string tileCode, const std::string location, bool* ptrIsKwirkle);

	/**
	* Player attemps to replace a tile 
	* Returns true if replacement is valid
	* Returns false is replacement is not valid
	*/
	bool replaceTile(const std::string tileCode);

	// Add a tile to the players hand
	void addTile(Node* node);

	// Returns the number of tiles in the player hand
	int getNumTiles() const;

};
#endif // ASSIGN2_TILE_H
