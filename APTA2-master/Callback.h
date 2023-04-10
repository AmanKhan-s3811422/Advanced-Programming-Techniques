#ifndef ASSIGN2_CALLBACK_H
#define ASSIGN2_CALLBACK_H

#include "Board.h"
#include "LinkedList.h"
#include "Player.h"

#include <iostream>
#include <string>



using std::string;
using std::cout;
using std::endl;

class Callback {
public:

    Callback();
    ~Callback();

    /**
    * Output start of Player turn message
    */
    void playerTurnStart(string playerName);

    /**
    * Output current Player scores
    */
    void playerScores(string player1Name, string player2Name, int player1Score, int player2Score);

    /**
    * Output current state of the Board
    */
    void boardState(Board* board);

    /**
    * Output current tiles in Player hand
    */
    void playerHand(string playerHand);

    /**
     * Output "Invalid input"
     */
    void invalidInput();

    /**
    * Output "<Enter Command>"
    */
    void enterCommandPrompt();

    /**
    * Print menu options
    */
    void menu();

    /**
    * Print prompts based on option picked from the menu
    */
    void menuResponse(int choice);

    /**
    * Outputs credits
    */
    void credits();

    /**
    * Outputs welcome message
    */
    void welcomeMessage();

    /**
    * Outputs a goodbye message
    */
    void goodbyeMessage();

    /**
    * Output Qwirkle
    */
    void qwirkled();

    /**
    * Output end of  game prompt
    */
    void gameOver(string player1Name, string player2Name, string winnerName, int player1Score, int player2Score);

    /**
    * Ourputs request for file name prompt
    */
    void fileNameRequest();

    /**
    * Outputs game load status
    */
    void loaded(bool state);

    /**
    * Outputs whether the file has been saved successfully.
    */
    void saveStatus(bool isSuccessful);

private:

};

#endif // ASSIGN2_CALLBACK_H

