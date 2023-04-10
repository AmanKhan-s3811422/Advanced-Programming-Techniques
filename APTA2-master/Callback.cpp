#include "Callback.h"

Callback::Callback() {

}

Callback::~Callback() {

}

void Callback::playerTurnStart(string playerName) {
    cout << '\n' << playerName << ", it's your turn" << endl;
}

void Callback::playerScores(string player1Name, string player2Name, int player1Score, int player2Score) {
    cout << "Score for " << player1Name << " :" << player1Score << endl;
    cout << "Score for " << player2Name << " :" << player2Score << endl;
}

void Callback::boardState(Board* board) {
    board->drawBoard();
}

void Callback::playerHand(string playerHand) {
    cout << "Your hand is " << playerHand << endl;
}

void Callback::invalidInput() {
    cout << "\nInvalid input" << endl;
}

void Callback::enterCommandPrompt() {
    cout << "\n> ";
}

void Callback::menu() {
    cout << "Menu \n"
        << "---- \n"
        << "1. New Game \n"
        << "2. Load Game \n"
        << "3. Credits (Show student information) \n"
        << "4. Quit \n";
        enterCommandPrompt();
}

void Callback::menuResponse(int choice) {
    if (choice == 1) {
        cout << "\nStarting a New Game\n" << endl;
    }
    else if (choice == 2) {
        cout << "You selected Load Game!" << endl;
    }
    else if (choice == 3) {
        cout << "You selected Credits (Show student information)" << endl;
    }
    else if (choice == 4) {
        goodbyeMessage();
    }
}

void Callback::credits() {
    cout << "-------------------------------\n"
        << "Name: Devin Amalean\n" 
        << "Student ID: S3821117\n"
        << "Email: S3821117@student.rmit.edu.au\n\n"

        << "Name: Sasilu Mudalige\n"
        << "Student ID: S3824917\n"
        << "Email: S3824917@student.rmit.edu.au\n\n"

        << "Name: Matthew Smith\n"
        << "Student ID: S3769858\n"
        << "Email: S3769858@student.rmit.edu.au\n\n"

        << "Name: Aman Khan\n"
        << "Student ID: S3811422\n"
        << "Email: S3811422@student.rmit.edu.au\n"

        << "------------------------------------\n" << endl;
}

void Callback::welcomeMessage() {
    cout << "Welcome to Qwirkle!\n"
        << "------------------- " << endl;
}

void Callback::goodbyeMessage() {
    cout << "\nGoodbye\n" << endl;
}

void Callback::qwirkled() {
    cout << "\nQwirkle!" << endl;
}

void Callback::gameOver(string player1Name, string player2Name, string winnerName, int player1Score, int player2Score) {
    cout << "Game Over" << endl;
    playerScores(player1Name, player2Name, player1Score, player2Score);
    cout << "\nPlayer " << winnerName << " won!\n" << endl;
    cout << "\nGoodbye" << endl;
}

void Callback::fileNameRequest() {
    cout << "\nEnter the filename from which load a game" << endl;
    enterCommandPrompt();
}

void Callback::loaded(bool state) {
    if (state) {
        cout << "\nQwirkle game successfully loaded" << endl;
    }
}

void Callback::saveStatus(bool isSuccessful) {
    if (isSuccessful) {
        cout << "\nGame successfully saved" << endl;
    }
    else {
        // This output is not a part of the specification...thought it would be appropriate :)
        cout << "\nUnfortunately...the game has not been sucessfully saved" << endl;
    }
}