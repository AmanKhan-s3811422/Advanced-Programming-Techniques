#include "LinkedList.h"
#include "TileBag.h"
#include "Player.h"
#include "GameEngine.h"

#include <iostream>
#include <memory>

int main(void){
	
	GameEngine* newGame = GameEngine::getInstance();
	newGame->begin();
	delete newGame;

	return EXIT_SUCCESS;
}