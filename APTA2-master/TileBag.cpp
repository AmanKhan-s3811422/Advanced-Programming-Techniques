#include "TileBag.h"
#include "TileCodes.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void TileBag::init() {

	std::vector<Tile*> tiles;

	char colors[6] = {
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		BLUE,
		PURPLE
	};

	// Adding tiles the tiles vector
	for (int i = 0; i < 6; i++) {
		for (int x = 0; x < 6; x++) {
			Tile* temp = new Tile();
			temp->colour = colors[x];
			temp->shape = i + 1;

			// Two of each type of tile must be generated
			tiles.push_back(temp);
			temp = new Tile(*temp);

			tiles.push_back(temp);
		}
	}


	// Shuffling the tiles vector using the stl shuffle algorithm
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));



	// Trasnfering shuffled tiles from the vector to the linked list
	for (Tile* tile : tiles) {
		Node* ptrTemp = new Node(tile, nullptr);
		tilebag->addToBack(ptrTemp);
	}
}


Node* TileBag::getTile() {
	return tilebag->removeFromFront();
}

Node* TileBag::getTile(std::string tileCode) {
	return tilebag->removeNode(tileCode);
}

void TileBag::addTile(Node* const ptrNode) {
	tilebag->addToBack(ptrNode);
}

TileBag::TileBag() {
	tilebag = new LinkedList();
}

TileBag::~TileBag() {
	delete tilebag;
}

std::string TileBag::getRemainingTiles(bool shouldPrint) {
	return tilebag->getOrderedList(shouldPrint);
}

int TileBag::getNumberOfTileLeft() const {
	return tilebag->getListSize();
}