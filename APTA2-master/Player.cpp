#include "Player.h"
#include <assert.h>

Player::Player(TileBag* const ptrTileBag, Board* const ptrBoard) {
	tileBag = ptrTileBag;
	board = ptrBoard;
	playersHand = new LinkedList();
}

Player::~Player() {
	delete(playersHand);
}

void Player::setScore(int sc) {
	score = sc;
}

int Player::getScore() {
	return score;
}

void Player::setName(std::string playerName) {
	name = playerName;
}

std::string Player::getName() const {
	return name;
}

void Player::init() {
	score = 0;

	if (playersHand == nullptr)
		playersHand = new LinkedList();

	//initialize the initial hand of the player 
	for (int i = 0; i < 6; i++) {
		Node* temp = tileBag->getTile();
		playersHand->addToBack(temp);
	}

}

std::string Player::showPlayersHand() const {
	
	// Players hand is printed and returned
	return playersHand->getOrderedList(true);
}

std::string Player::getPlayersHand() const {

	// Players hand is returned and NOT printd
	return playersHand->getOrderedList(false);
}


bool Player::placeTile(const std::string tileCode, const std::string location, bool* ptrIsKwirkle) {
	bool retVal = false;

	// Check if the tile is in the players hand
	if (!playersHand->containsTile(tileCode))
		retVal = false;
	
	else {
		// Before placing the tile, move validity is checked (onlyCheckIfValidMove = true)
		Node* ref = playersHand->getNode(tileCode);
		int cur_score = board->placeTile(location, ref, true, ptrIsKwirkle);
		
		// curr_score = 0 if the placement is invalid
		if (cur_score == 0)
			retVal = false;

		else {
			// Remove the node from the players hand and placing it in the board
			ref = playersHand->removeNode(tileCode);

			// Making sure that the tile is definitly in the players hand
			assert(ref != nullptr);

			// Placing the tile on the board
			cur_score = board->placeTile(location, ref, false, ptrIsKwirkle);

			// Update the score of the player
			score += cur_score;

			// Get a tile from the tile bag
			Node* newTileNode = tileBag->getTile();

			// Placing the tile in the players hand if it is not a nullptr
			if (newTileNode != nullptr)
				playersHand->addToBack(newTileNode);

			retVal = true;
		}
	}

	return retVal;

}

bool Player::replaceTile(const std::string tileCode) {
	bool retVal = false;

	// Check if the tile is in the players hand
	if (!playersHand->containsTile(tileCode))
		retVal = false;
	else if (tileBag->getNumberOfTileLeft() == 0)
		retVal = false;
	else {
		//get the tile from the players hand
		Node* ptrNode = playersHand->removeNode(tileCode);

		assert(ptrNode != nullptr);

		//add the tile to the bag
		tileBag->addTile(ptrNode);

		//get a tile from the bag
		ptrNode = tileBag->getTile();

		// Making sure that the node retured from the tile bag is not a nullptr
		assert(ptrNode != nullptr);

		//add the retrived tile to the players hand
		playersHand->addToBack(ptrNode);

		retVal = true;
	}

	return retVal;
}

void Player::addTile(Node* node) {
	playersHand->addToBack(node);
}

int Player::getNumTiles() const {
	return playersHand->getListSize();
}