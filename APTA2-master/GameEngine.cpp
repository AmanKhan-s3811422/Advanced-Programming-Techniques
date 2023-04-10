#include "GameEngine.h"

#define INVALID     -10
#define ONE         1
#define TWO         2
#define THREE       3
#define FOUR        4

using namespace std;

GameEngine::GameEngine() {
    tilebag = new TileBag();
    tilebag->init();

    board = new Board();
    player1 = new Player(tilebag, board);
    player2 = new Player(tilebag, board);

    player1->init();
    player2->init();

    log = new Callback();
}

GameEngine::~GameEngine() {
    delete tilebag;
    tilebag = nullptr;
    delete player1;
    player1 = nullptr;
    delete player2;
    player2 = nullptr;
    currentPlayer = nullptr;
    delete board;
    board = nullptr;
    delete log;
    log = nullptr;
}

GameEngine* GameEngine::ptrInstance = nullptr;

GameEngine* GameEngine::getInstance() {
    if (ptrInstance == nullptr) {
        ptrInstance = new GameEngine();
    }
    return ptrInstance;
}

void GameEngine::newGame() {
    string player1Name;
    string player2Name;
    cout << "Enter a name for player 1 (uppercase characters only)" << endl;
    log->enterCommandPrompt();
    getline(cin, player1Name);

    while (!validateName(player1Name)) {
        cout << "Invalid name. Player name must be all uppercase letters, no numbers and no symbols\n" << endl;
        log->enterCommandPrompt();

        getline(cin, player1Name);
    }

    player1->setScore(0);
    player1->setName(player1Name);

    cout << "\nEnter a name for player 2 (uppercase characters only)" << endl;
    log->enterCommandPrompt();

    getline(cin, player2Name);

    while (!validateName(player2Name)) {
        cout << "Invalid name. Player name must be all uppercase letters, no numbers and no symbols\n" << endl;
        log->enterCommandPrompt();

        getline(cin, player2Name);
    }

    player2->setScore(0);
    player2->setName(player2Name);
    currentPlayer = player1;
    cout << "\nLet's Play!\n" << endl;
}

bool GameEngine::validateName(string name) {
    bool returnValue = true;
    string::size_type i = 0;
    while (i < name.size()) {
        if ((int)name[i] < 65 || (int)name[i] > 90) {
            returnValue = false;
        }
        i++;
    }
    return returnValue;
}

void GameEngine::begin() {

    bool conditionOne = true;
    bool conditionTwo = true;
    bool haveQuit = false;
    bool isLoaded = false;
    string strChoice;
    int choice;
    int result;
    string input;
    string filename = "";

    log->welcomeMessage();

    while (conditionOne) {
        log->menu();

        // Try receiving input and converting to an integer
        try{
            // Check for input. If EOF is read, exit
            if(getline(cin, strChoice)){
                choice = stoi(strChoice);
                } else {
                    choice = 4;
                    }
        } 
        // Catch an exception thrown and run through invalid input condition
        catch (...){
            choice = 0;
        }

        log->menuResponse(choice);

        // Start a new game
        if (choice == ONE) {
            newGame();
            conditionOne = false;
        }
        // Load a previous game
        else if (choice == TWO) {
            log->fileNameRequest();
            getline(cin, filename);
            isLoaded = loadGame(filename);

            // Display if game has been successfully loaded or not
            log->loaded(isLoaded);

            // Exit loop and continue with regular gameplay if loaded successfully
            if (isLoaded) {
                conditionOne = false;
            } 
            // If Game is not successfully loaded, go back to menu input
            else {
                log->invalidInput();
            }
            
        }
        // Display credits
        else if (choice == THREE) {
            log->credits();
        }
        // Quit
        else if (choice == FOUR) {
            conditionOne = false;
            haveQuit = true;
        }
        else {
            log->invalidInput();
        }
    }

    while (conditionTwo && !haveQuit) {
        log->playerTurnStart(currentPlayer->getName());
        log->playerScores(player1->getName(), player2->getName(), player1->getScore(), player2->getScore());
        log->boardState(board);
        log->playerHand(currentPlayer->getPlayersHand());

        log->enterCommandPrompt();
        // Check for EOF, quit if detected
        if(!getline(cin, input)){
            input = "quit";
        }
        result = checkInput(input);

        // Exit the game
        if (result == -1) {
            conditionTwo = false;
            conditionOne = false;
            log->goodbyeMessage();
        }
        // Invalid Command
        else if (result == 0) {
            log->invalidInput();
        }
        // Regular game play
        else {
            if (kwirk) {
                log->qwirkled();
            }

            if (isGameOver) {
                if (player1->getScore() > player2->getScore()) {
                    currentPlayer = player1;
                }
                else {
                    currentPlayer = player2;
                }

                log->gameOver(player1->getName(), player2->getName(),
                    currentPlayer->getName(), player1->getScore(), player2->getScore());

                //conditionOne = false;
                conditionTwo = false;
                haveQuit = true;

                // NEED TO DEALLOCATE MEMORY HERE
            }
        }
    }
}

int GameEngine::checkInput(string input) {

    char delimiter = ' ';
    string tileCode;
    vector<string> commands;
    int returnValue = INVALID;

    // Making sure that there is a command
    if (!input.empty()) {
        commands = splitByDelimiter(input, delimiter);

        if (commands[0] == "place") {
            if (commands.size() == 4) {
                string atCommand = commands[2];
                string position = commands[3];
                tileCode = commands[1];

                if (atCommand.compare("at") == 0 && characterValidation(tileCode) &&
                    characterValidation(position)) {
                    kwirk = false;
                    isGameOver = false;

                    bool* isQwirkle = &kwirk;
                    bool* ptrGameOver = &isGameOver;

                    returnValue = placeTile(tileCode, position, isQwirkle, ptrGameOver);
                }
                else {
                    returnValue = 0;
                }
            }
        }
        else if (commands[0] == "replace") {
            if (commands.size() == 2) {
                tileCode = commands[1];
                if (characterValidation(tileCode)) {
                    bool tempState = replaceTile(tileCode);

                    // Successfully replaced
                    if (tempState) {
                        returnValue = 1;
                    }
                    // Tile could not be replaced
                    else {
                        returnValue = 0;
                    }
                }
                else {
                    returnValue = 0;
                }
            }
        }
        else if (commands[0].compare("save") == 0 && commands.size() == 2) {
            // Commands[1] will contain the file name which is assumed to be correct
            bool tempState = saveGame(commands[1]);

            log->saveStatus(tempState);

            // Saved successfully
            if (tempState) {
                returnValue = 1;
            }
            // Error occured while saving
            else {
                returnValue = 0;
            }
        }
        else if (commands[0].compare("quit") == 0 && commands.size() == 1) {
            returnValue = -1;
        }
        else {
            returnValue = 0;
        }
    }

    return returnValue;
}

int GameEngine::placeTile(const string tilecode, const string locationOnBoard, bool* isQwirkle, bool* ptrGameOver) {
    bool result = currentPlayer->placeTile(tilecode, locationOnBoard, isQwirkle);
    int retVal = 1;

    // Tile was not placed successfully (invalid move)
    if (!result)
        retVal = 0;


    // Checking if the game is over
    else if (tilebag->getNumberOfTileLeft() == 0 && currentPlayer->getNumTiles() == 0)
        *ptrGameOver = true;
    else
        switchPlayerTurn();


    return retVal;
}

bool GameEngine::replaceTile(const string tileCode) {
    bool retVal = currentPlayer->replaceTile(tileCode);

    // Switch players if tile was successfully replaced
    if (retVal) {
        switchPlayerTurn();
    }

    return retVal;
}

bool GameEngine::saveGame(const string fileName) {
    bool retVal = false;

    try {
        //check whether the file exisit
        std::ofstream outFile(fileName);

        //construct the string to be saved 
        std::string gameSaveData = "";
        std::stringstream stream;

        stream << player1->getName() << endl;
        stream << player1->getScore() << endl;
        stream << player1->getPlayersHand() << endl;

        stream << player2->getName() << endl;
        stream << player2->getScore() << endl;
        stream << player2->getPlayersHand() << endl;

        stream << board->getCurrentBoardShape() << endl;
        stream << board->getCurrentBoardState() << endl;

        stream << tilebag->getRemainingTiles(false) << endl;
        stream << currentPlayer->getName() << endl;

        gameSaveData = stream.str();

        outFile << gameSaveData;

        outFile.close();

        retVal = true;
    }
    catch (std::exception& ex) {
        retVal = false;
    }

    return retVal;
}

bool GameEngine::loadGame(std::string fileName) {

    bool returnValue = false;

    // Attempt read the given file 
    try {
        std::ifstream inFile(fileName);

        if (!inFile.is_open()) {
            returnValue = false;
        }
        else {
            std::stringstream stream;

            // Read file into the stringstream
            stream << inFile.rdbuf();

            std::string player1Name;
            std::string player1Score;
            std::string player1Hand;

            std::string player2Name;
            std::string player2Score;
            std::string player2Hand;

            std::string boardShape;
            std::string boardState;

            std::string tileInBag;

            std::string curPlayerName;

            getline(stream, player1Name);
            getline(stream, player1Score);
            getline(stream, player1Hand);

            getline(stream, player2Name);
            getline(stream, player2Score);
            getline(stream, player2Hand);

            getline(stream, boardShape);
            getline(stream, boardState);

            getline(stream, tileInBag);
            getline(stream, curPlayerName);

            tilebag = new TileBag();

            // Setting up the tilebag
            if (tileInBag.length() > 0) {

                // Removing commas from the input data of the tilecode
                std::vector<string> tilesbag = splitByDelimiter(tileInBag, ',');

                // Initialising the tilebag with tiles from the saved game
                for (std::string tilecode : tilesbag) {
                    Tile* anotherTile = new Tile();
                    anotherTile->colour = tilecode.at(0);
                    anotherTile->shape = atoi(tilecode.substr(1, tilecode.length()).c_str());

                    // Creating a node to add to the tilebag of the current (loaded) game
                    Node* theNode = new Node(anotherTile, nullptr);
                    tilebag->addTile(theNode);
                }
            }


            // Setting up the board
            std::vector<string> boardShapeStr = splitByDelimiter(boardShape, ',');
            int width = atoi(boardShapeStr[0].c_str());
            int height = atoi(boardShapeStr[1].c_str());

            board = new Board(width, height);


            if (boardState.length() > 0) {

                // Removing commas between tile@location, tile@location etc...
                std::vector<string>boardStateStr = splitByDelimiter(boardState, ',');

                for (std::string tileAtLocation : boardStateStr) {

                    // Removinf @ between tile@location
                    std::vector<string> tempTileAtLocation = splitByDelimiter(tileAtLocation, '@');
                    std::string tileCode = tempTileAtLocation[0];
                    std::string tileCoord = tempTileAtLocation[1];

                    // Create the node with the tile
                    Tile* anotherTile = new Tile();
                    anotherTile->colour = tileCode.at(0);
                    anotherTile->shape = atoi(tileCode.substr(1, tileCode.length()).c_str());

                    // Getting the position (cordinate) of the tile on the board
                    char rowOnBoard = tileCoord.at(0);
                    int rowIndex = rowOnBoard - 'A';
                    int colIndex = atoi(tileCoord.substr(1, tileCoord.length()).c_str());

                    // Creating a node for the tile
                    Node* loadedNode = new Node(anotherTile, nullptr);

                    /** Adding the tile onto its respective position on the board
                     * Rules are not checked before adding the tile. Assumed that
                     * rules have already been checked while game was being played.
                     * (before game was saved and then loaded)
                     */
                    board->putTile(rowIndex, colIndex, loadedNode);
                }

            }

            // Initialising the players
            player1 = new Player(tilebag, board);
            player2 = new Player(tilebag, board);


            if (player1Hand.length() > 0) {

                // Adding player1's tiles
                std::vector<std::string> player1Tiles = splitByDelimiter(player1Hand, ',');
                for (std::string s : player1Tiles) {

                    // Adding player1's tiles to thier hand 
                    Tile* theTile = new Tile();
                    theTile->colour = s.at(0);
                    theTile->shape = atoi(s.substr(1, s.length()).c_str());

                    Node* theNode = new Node(theTile, nullptr);
                    player1->addTile(theNode);
                }
            }


            if (player2Hand.length() > 0) {

                // Adding player2's tiles 
                std::vector<std::string> player2Tiles = splitByDelimiter(player2Hand, ',');
                for (std::string s : player2Tiles) {

                    // Adding player2's tiles to thier hand 
                    Tile* theTile = new Tile();
                    theTile->colour = s.at(0);
                    theTile->shape = atoi(s.substr(1, s.length()).c_str());

                    Node* theNode = new Node(theTile, nullptr);
                    player2->addTile(theNode);
                }
            }

            player1->setName(player1Name);
            player1->setScore(atoi(player1Score.c_str()));

            player2->setName(player2Name);
            player2->setScore(atoi(player2Score.c_str()));

            // Setting current player
            if (curPlayerName.compare(player1Name) == 0)
                currentPlayer = player1;
            else
                currentPlayer = player2;

            inFile.close();

            returnValue = true;

        }
    }
    catch (std::exception& ex) {
        // Error occured
        returnValue = false;
    }

    return returnValue;
}

vector<string> GameEngine::splitByDelimiter(const string theString, char delimiter) {
    int nextCharacter = 0;
    int currentPosition = 0;
    vector<string> noDelimeterString;
    string tempString = "";

    // While loop continues until the last delimeter is reached
    while ((currentPosition = theString.find(delimiter, nextCharacter + 1)) > 0) {
        tempString = theString.substr(nextCharacter, currentPosition - nextCharacter);

        /**
         * currentPosition will contain the index of a delimiter in the string
         * Assigning that inidex to nextCharacter
         */
        nextCharacter = currentPosition;

        /** Increasing the value of nextCharacter by one to it will contain the index
         * of the next non-delimeter character in the string.
         */
        nextCharacter++;

        // Adding the string without the dilimeter to the vector
        noDelimeterString.push_back(tempString);
    }

    /**
     * The substring after the last delimeter will not get added to the vector.
     * Therefore it has been added to the vector below
     */
    tempString = theString.substr(nextCharacter);
    noDelimeterString.push_back(tempString);
    return noDelimeterString;
}

bool GameEngine::characterValidation(string code) {
    bool isValid = true;

    if (code.length() == 2 || code.length() == 3) {
        char characterOne = code.at(0);
        char characterTwo = code.at(1);

        isValid = true;

        if (characterOne < 'A' || characterOne > 'Z')
            isValid = false;

        if (characterTwo < '0' || characterTwo > '9')
            isValid = false;
    }
    else {
        isValid = false;
    }

    return isValid;
}

void GameEngine::switchPlayerTurn() {
    if (currentPlayer == player1) {
        currentPlayer = player2;
    }
    else {
        currentPlayer = player1;
    }
}