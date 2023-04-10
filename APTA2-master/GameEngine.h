#ifndef ASSIGN2_GAMEENGINE_H
#define ASSIGN2_GAMEENGINE_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"
#include "TileBag.h"
#include "Callback.h"

#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <vector>

using std::string;
using std::ofstream;
using std::ifstream;
using std::stringstream;
using std::exception;
using std::cin;
using std::endl;

class GameEngine {
public:

    GameEngine();
    ~GameEngine();

    /**
     * Getting user input for the player names.
     * Setting currentPlayer to player 1
     */
    void newGame();

    /**
     * Validate player name contains capital letters only
     */
    bool validateName(string name);

    /**
    * Initiated game loop
    */
    void begin();

    /**
     * Returns a pointer to the game
     */
    static GameEngine* getInstance();

    /**
     * Function which saves the game
     */
    bool saveGame(const string fileName);

    /**
     * Function which loads a previously saved game
     */
    bool loadGame(const string fileName);

private:

    TileBag* tilebag;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    Board* board;
    Callback* log;
    static GameEngine* ptrInstance;

    bool kwirk = false;
    bool isGameOver = false;

    /**
     * Returns -1 to exit current game
     * Returns 0 if game over
     * Returns 1 for the current game to continue
     */
    int checkInput(string input);

    /**
     * Function takes in a string which has a delimeter
     * Removes the delimter from from the string
     * Returns the string without the delimeter
     */
    std::vector<string> splitByDelimiter(const string theString, char delimiter);

    /**
     * Checks if a tile code/ location is valid in format
     */
    bool characterValidation(string code);

    /**
     * Validates placing a tile on the board
     * Returns -1 to exit current game
     * Returns 0 if the tile cannot be placed (invalid command)
     * Returns 1 for the current game to continue
     */
    int placeTile(const string tilecode, const string locationOnBoard,
        bool* ptrIsKwirkle, bool* ptrGameOver);

    /**
     * Validating a tile being replaced
     */
    bool replaceTile(const string tileCode);

    /**
     * Switches the players turn
     */
    void switchPlayerTurn();

};

#endif // ASSIGN2_GAMEENGINE_H

