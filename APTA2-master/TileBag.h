#ifndef ASSIGN2_TILEBAG_H
#define ASSIGN2_TILEBAG_H

#include "LinkedList.h"

#include <string>
#include <memory>

class TileBag
{
private:
	LinkedList* tilebag = nullptr;
					

public:
	TileBag();
	~TileBag();


	/**
	* Returns a tile from the tilebag
	*/
	Node* getTile();

	Node* getTile(std::string tileCode);

	/**
	* perform the initialization of the tile bag (generating and shuffling the tiles) 
	*/
	void init();

	/**
	* Adds a tile to the tilebag
	*/
	void addTile(Node* const ptrNode);

	/**
	* Returns the remaining tiles in the tilebag as a string
	*/
	std::string getRemainingTiles(bool shouldPrint);

	/**
	* Returns the number of tiles remaining in the tilebags
	*/
	int getNumberOfTileLeft() const;


	//returns a tile from the tile bag to the caller (always from the front from the list)
//	std::shared_ptr<Node> getTileSafe();

	//returns a named tile from the bag, (testing purposes-not a requirement)
//	std::shared_ptr<Node> getTileSafe(std::string tileCode);

};

#endif // ASSIGN2_TILEBAG_H