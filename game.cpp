/********************************************************************
** Program: game.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Game class
** Input: Debug mode and cave dimensions, if user wants to move or shoot an arrow, play again/quit options
** Output: User prompts, cave, instructions, inventory, percepts
********************************************************************/

#include "game.h"
#include "room.h"
#include "bats.h"
#include "gold.h"
#include "pit.h"
#include "rope.h"
#include "wumpus.h"

#include <iostream> // cout/cin/endl
#include <cstdlib> // for random # generation
#include <ncurses.h> // for ncurses

// ======================================== GAME RUCTORS AND DESTRUCTOR ========================================
/********************************************************************
** Function: Game class constructor
** Description: Default constructor for Game class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Game::Game()
{
    this->debugMode = this->debugInput();
    this->leaveGame = false;
    this->caveSize = this->sizeInput();
    
    // initialize the cave
    for (int i = 0; i < this->caveSize; i++) {
        vector<Room> row;

        for (int j = 0; j < this->caveSize; j++) {
            row.push_back(Room());
        }
        this->cave.push_back(row);
    }

    this->randomizeRooms();
    this->populateCave();
}

/********************************************************************
** Function: Game class non-default constructor
** Description: Constructs Game class with parameters listed below
** Parameters: bool debug, int cave
** Pre-Conditions: debug must be of type bool, cave must be of type int
** Post-Conditions: Class is constructed
********************************************************************/
Game::Game(vector<int> loc, int cave)
{
    this->debugMode = this->debugInput();
    this->leaveGame = false;
    // if user chooses to keep settings, cave size remains the same
    this->caveSize = cave;

    // initialize the cave
    for (int i = 0; i < this->caveSize; i++) {
        vector<Room> row;

        for (int j = 0; j < this->caveSize; j++) {
            row.push_back(Room());
        }
        this->cave.push_back(row);
    }

    // locations vector is same as previous game
    this->locations = loc;
    // populate cave using same locations
    this->populateCave();
}

/********************************************************************
** Function: Game class destructor
** Description: Destructs Game class and frees all dynamic memory
** Parameters: N/A
** Pre-Conditions: Function will be called by class when class is out of scope
** Post-Conditions: Class is destructed
********************************************************************/
Game::~Game()
{
    // free memory
    for (int i = 0; i < this->caveSize; i++)
        for (int j = 0; j < this->caveSize; j++)
            this->cave[i][j].removeEvent();

    this->cave.clear();
}

// ======================================== UTILITY ========================================
/********************************************************************
** Function: pressEnter
** Description: Prompts user to press enter
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::pressEnter() const
{
    cout << "Press enter to continue...";

    cin.ignore();
}

/********************************************************************
** Function: debugInput
** Description: Get and check user input for debugMode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Game::debugInput() const
{
    string input;

    while (1) {
        // prompt user
        cout << "\nWould you like to run in debug mode? (true/false): ";
        cin >> input; // get user input

        // return correct bool based on input
        if (input == "true" || input == "True")
            return true;
        if (input == "false" || input == "False")
            return false;
        
        // print error message
        cout << "\n\nPlease enter an acceptable input";
    }
}

/********************************************************************
** Function: sizeInput
** Description: Get and check user input for caveSize
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int Game::sizeInput() const
{
    string input;

    while (1) {
        // prompt user
        cout << "\nEnter cave dimension (must be greater than or equal to 4): ";
        cin >> input; // get user input

        // return correct int based on input
        if (stoi(input) >= 4)
            return stoi(input);
        
        // print error message
        cout << "\n\nPlease enter an acceptable input";
    }
}

/********************************************************************
** Function: ncursesFunctionality
** Description: Functionality for ncurses library
** Parameters: char& input
** Pre-Conditions: input must be of type char&
** Post-Conditions: Does not return a value
********************************************************************/
void ncursesFunctionality(char& input)
{
    initscr();
    cbreak();
    input = getch();
    endwin();
}

// ======================================== ACCESSORS ========================================
/********************************************************************
** Function: getPlayerX
** Description: X coordinate for Player struct accessor
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int Game::getPlayerX()
{
    return this->p.x_val;
}

/********************************************************************
** Function: getPlayerY
** Description: Y coordinate for Player struct accessor
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int Game::getPlayerY()
{
    return this->p.y_val;
}

/********************************************************************
** Function: getDefeatWumpus
** Description: Accessor for defeatWumpus bool
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Game::getDefeatWumpus()
{
    return this->p.defeatWumpus;
}

/********************************************************************
** Function: getHasGold
** Description: Accessor for hasGold bool
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Game::getHasGold()
{
    return this->p.hasGold;
}

/********************************************************************
** Function: getCaveSize
** Description: Cave dimension accessor
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int Game::getCaveSize()
{
    return this->caveSize;
}

/********************************************************************
** Function: getCave
** Description: Accessor for given Room in cave vector
** Parameters: int x, int y
** Pre-Conditions: x must be of type int, y must be of type int
** Post-Conditions: Function returns value of type Room
********************************************************************/
Room Game::getCave(int x, int y)
{
    return this->cave[x][y];
}

/********************************************************************
** Function: getDebugSetting
** Description: Accessor for debugMode bool
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Game::getDebugSetting() const
{
    return this->debugMode;
}

/********************************************************************
** Function: getLocations
** Description: Accessor for locations vector
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
vector<int> Game::getLocations() const
{
    return this->locations;
}

// ======================================== MUTATORS ========================================
/********************************************************************
** Function: setLeaveGame
** Description: Mutator for leaveGame bool
** Parameters: const bool newLeave
** Pre-Conditions: newLeave must be of type bool
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setLeaveGame(const bool newLeave)
{
    this->leaveGame = newLeave;
}

/********************************************************************
** Function: setPlayerX
** Description: X coordinate in Player struct mutator
** Parameters: const int newX
** Pre-Conditions: newX must be of type int
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setPlayerX(const int newX)
{
    this->p.x_val = newX;
}

/********************************************************************
** Function: setPlayerY
** Description: Y coordinate in Player struct mutator
** Parameters: const int newY
** Pre-Conditions: newY must be of type int
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setPlayerY(const int newY)
{
    this->p.y_val = newY;
}

/********************************************************************
** Function: setPlayerGold
** Description: Mutator for hasGold bool
** Parameters: const bool newGold
** Pre-Conditions: newGold must be of type bool
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setPlayerGold(const bool newGold)
{
    this->p.hasGold = newGold;
}

/********************************************************************
** Function: setPlayerDead
** Description: Mutator for isDead bool
** Parameters: const bool newDead
** Pre-Conditions: newDead must be of type bool
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setPlayerDead(const bool newDead)
{
    this->p.isDead = newDead;
}

// ======================================== PRINT CAVE ========================================
/********************************************************************
** Function: randomizeRooms
** Description: Populate int vector with unique random numbers
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::randomizeRooms()
{
    int randNum = 0; // initalize rand
    bool uniqueNum;

    // loop through number of events
    for (int i = 0; i < 7; i++) {
        uniqueNum = false;
        while (!uniqueNum) {
            uniqueNum = true;
            // generate a random number between 0 and cave size - 1
            randNum = rand() % (this->caveSize * this->caveSize);
            // loop through vector member variables
            for (int entry : this->locations)
                // if random number already exists, uniqueNum = false (while loop continues)
                if (randNum == entry)
                    uniqueNum = false;
        }
        // add unique number to vector
        this->locations.push_back(randNum);
    }
}

/********************************************************************
** Function: populateCave
** Description: Populate cave using numbers vector
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::populateCave()
{
    // assign room in cave to events
    this->cave[this->locations[0] / this->caveSize][this->locations[0] % this->caveSize].setEvent(new Wumpus());
    this->cave[this->locations[1] / this->caveSize][this->locations[1] % this->caveSize].setEvent(new Gold());
    this->cave[this->locations[2] / this->caveSize][this->locations[2] % this->caveSize].setEvent(new Bats());
    this->cave[this->locations[3] / this->caveSize][this->locations[3] % this->caveSize].setEvent(new Bats());
    this->cave[this->locations[4] / this->caveSize][this->locations[4] % this->caveSize].setEvent(new Pit());
    this->cave[this->locations[5] / this->caveSize][this->locations[5] % this->caveSize].setEvent(new Pit());
    this->cave[this->locations[6] / this->caveSize][this->locations[6] % this->caveSize].setEvent(new Rope());

    // player starts in same room as Rope
    this->p.x_val = this->locations[6] / this->caveSize, this->p.y_val = this->locations[6] % this->caveSize;
}

/********************************************************************
** Function: getRoomString
** Description: Print room characters
** Parameters: int x_val, int y_val
** Pre-Conditions: x_val must be of type int, y_val must be of type int
** Post-Conditions: Function returns value of type string
********************************************************************/
string Game::getRoomString(int x_val, int y_val)
{
    // if on left of cave, print bar
    string row = (x_val == 0 ? "║    " : "     ");

    // if player, print *
    if (x_val == this->p.x_val && y_val == this->p.y_val)
        row += "*";
    // if room has event, print event character
    else if (this->debugMode && this->cave[x_val][y_val].hasEvent())
        row += this->cave[x_val][y_val].getEvent()->eventChar();
    // if room is empty, print space
    else
        row += " ";
    
    // add hanging spaces to row
    return row + "    ";
}

/********************************************************************
** Function: printCave
** Description: Print cave
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::printCave()
{
    cout << "\n\n";

    // one row at a time
    for(int y = 0; y < this->caveSize; y++) {
        // == print a row of cave rooms ==
        // print ceiling
        for (int j = 0; j < this->caveSize; j++)
            cout << (y == 0 ? "╬═════════" : "╬════ ════");
        cout << "╬" << endl;

        // print rest
        for(int n = 0; n < 3; n++) {
            for (int x = 0; x < this->caveSize; x++) {
                cout << (n == 1 ? this->getRoomString(x, y) : "║         ");
            }
            cout << "║" << endl;
        }
    }
    
    // print floor
    for (int j = 0; j < this->caveSize; j++)
        cout << "╬═════════";
    cout << "╬" << endl;
}

// ======================================== GAME PRINT FUNCTIONS ========================================
/********************************************************************
** Function: printInstructions
** Description: Print game instructions to terminal
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::printInstructions() const
{
    cout << "\n===== HOW TO PLAY =====\n";
    cout << "To move north, east, south, or west, type \"w\", \"a\", \"s\", or \"d\", respectively\n";
    cout << "To fire an arrow, type a space followed by the desired direction\n";
    cout << "The adventurer will die if you encounter the Wumpus or a Pit. ";
    cout << "To win, kill the Wumpus with an arrow, take the Gold, and escape the cave using the Rope at your original starting room.\n";
    cout << "\033[31mThe terminal will clear due to ncurses on the first game. Input a character other than w, a, s, d, or space when this happens.\033[0m\n";
    cout << "Good luck!\n\n";

    cin.ignore();
    this->pressEnter();
}

/********************************************************************
** Function: printInventory
** Description: Print player inventory to terminal
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::printInventory() const
{
    // print inventory to terminal (arrows, gold, wumpus)
    cout << "\n===== INVENTORY =====\n";
    if (this->p.arrows > 0)
        cout << "Arrows x" << this->p.arrows << endl;
    if (this->p.hasGold)
        cout << "Pile of gold\n";
    if (this->p.defeatWumpus)
        cout << "Wumpus head\n";
}

/********************************************************************
** Function: checkSeenVector
** Description: Utility function, check if character has been encountered
** Parameters: vector<string>& seen, string character
** Pre-Conditions: seen must be of type vector<string>&, character must be of type string
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool checkSeenVector(vector<string>& seen, string character)
{
    bool charSeen = false;

    // check if we have seen the char
    for (string entry : seen) 
        if (entry == character)
            charSeen = true;
    
    // if we didn't see the char, add it to seen
    if (!charSeen) 
        seen.push_back(character);
    
    return charSeen;
}

/********************************************************************
** Function: printPercepts
** Description: Print correct percepts to terminal
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::printPercepts()
{
    // for each adjacent room, if percept has not been printed, call percept function
    vector<string> seen;

    // north (y_val - 1)
    if (this->p.y_val - 1 >= 0 && cave[this->p.x_val][this->p.y_val - 1].hasEvent())
        if (!checkSeenVector(seen, cave[this->p.x_val][this->p.y_val - 1].getEvent()->eventChar()))
            cave[this->p.x_val][this->p.y_val - 1].getEvent()->percept();

    // east (x_val + 1)
    if (this->p.x_val + 1 < this->caveSize && cave[this->p.x_val + 1][this->p.y_val].hasEvent())
        if (!checkSeenVector(seen, cave[this->p.x_val + 1][this->p.y_val].getEvent()->eventChar()))
            cave[this->p.x_val + 1][this->p.y_val].getEvent()->percept();

    // south (y_val + 1)
    if (this->p.y_val + 1 < this->caveSize && cave[this->p.x_val][this->p.y_val + 1].hasEvent())
        if (!checkSeenVector(seen, cave[this->p.x_val][this->p.y_val + 1].getEvent()->eventChar()))
            cave[this->p.x_val][this->p.y_val + 1].getEvent()->percept();
    
    // west (x_val - 1)
    if (this->p.x_val - 1 >= 0 && cave[this->p.x_val - 1][this->p.y_val].hasEvent())
        if (!checkSeenVector(seen, cave[this->p.x_val - 1][this->p.y_val].getEvent()->eventChar()))
            cave[this->p.x_val - 1][this->p.y_val].getEvent()->percept();
}

// ======================================== MOVE ========================================
/********************************************************************
** Function: move
** Description: Game logic for move functionality
** Parameters: char input
** Pre-Conditions: input must be of type char
** Post-Conditions: Does not return a value
********************************************************************/
void Game::move(char input)
{
    // move the player
    this->setPlayerCoord(input);

    // if room at new coordinates has event, call encounter function
    if (this->cave[this->p.x_val][this->p.y_val].hasEvent())
        this->cave[this->p.x_val][this->p.y_val].getEvent()->encounter(*this);
}

/********************************************************************
** Function: setPlayerCoord
** Description: Adjust coordinates in Player struct depending on user input for move
** Parameters: char direction
** Pre-Conditions: direction must be of type char
** Post-Conditions: Does not return a value
********************************************************************/
void Game::setPlayerCoord(char direction)
{
    // move north
    if (direction == 'w' && this->p.y_val > 0) {
        this->p.y_val--;
        return;
    }

    // move east
    if (direction == 'd' && this->p.x_val < this->caveSize - 1) {
        this->p.x_val++;
        return;
    }

    // move south
    if (direction == 's' && this->p.y_val < this->caveSize - 1) {
        this->p.y_val++;
        return;
    }

    // move west
    if (direction == 'a' && this->p.x_val > 0) {
        this->p.x_val--;
        return;
    }

    // player going out of bounds
    cout << "You cannot walk through walls! Enter input again\n";
    this->getUserInput();
}

// ======================================== SHOOT ARROW ========================================
/********************************************************************
** Function: shootArrow
** Description: Main logic for shooting arrow functionality
** Parameters: char input
** Pre-Conditions: input must be of type char
** Post-Conditions: Does not return a value
********************************************************************/
void Game::shootArrow(char input)
{
    // if player has no arrows left, call function and return
    if (this->p.arrows == 0) {
        this->noArrows();
        return;
    }

    // decrement arrows
    this->p.arrows--;

    // if the user has already defeated the Wumpus, return
    if (this->p.defeatWumpus)
        return;

    // call function with correct parameters based on direction in user input
    if (input == 'w')
        this->checkArrow(this->p.x_val, this->p.y_val, 0, -1);
    if (input == 'a')
        this->checkArrow(this->p.x_val, this->p.y_val, -1, 0);
    if (input == 's')
        this->checkArrow(this->p.x_val, this->p.y_val, 0, 1);
    if (input == 'd')
        this->checkArrow(this->p.x_val, this->p.y_val, 1, 0);

    // call function that deals with Wumpus logic
    this->wumpusLogic();
}

/********************************************************************
** Function: noArrows
** Description: Logic for no arrows left
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::noArrows()
{
    // if player has not arrows left, print error message and prompt for input again
    cout << "\n\nYou are out of arrows. Please enter an acceptable input";
    this->getUserInput();
}

/********************************************************************
** Function: checkArrow
** Description: Check for bounds, if Room has Event, if Event is Wumpus
** Parameters: int x, int y, int hor, int ver
** Pre-Conditions: x must be of type int, y must be of type int, hor must be of type int, ver must be of type int
** Post-Conditions: Does not return a value
********************************************************************/
void Game::checkArrow(int x, int y, int hor, int ver)
{
    // if Room is in bounds, Room has an Event, and Event is Wumpus, Wumpus is dead
    if (this->inBounds(x, y, hor, ver) && this->cave[x + hor][y + ver].hasEvent() && this->cave[x + hor][y + ver].getEvent()->eventChar() == "W")
        this->p.defeatWumpus = true;
    if (this->inBounds(x, y, hor * 2, ver * 2) && this->cave[x + hor * 2][y + ver * 2].hasEvent() && this->cave[x + hor * 2][y + ver * 2].getEvent()->eventChar() == "W")
        this->p.defeatWumpus = true;
    if (this->inBounds(x, y, hor * 3, ver * 3) && this->cave[x + hor * 3][y + ver * 3].hasEvent() && this->cave[x + hor * 3][y + ver * 3].getEvent()->eventChar() == "W")
        this->p.defeatWumpus = true;
}

/********************************************************************
** Function: inBounds
** Description: Check if Room is in bounds of cave
** Parameters: int x, int y, int hor, int ver
** Pre-Conditions: x must be of type int, y must be of type int, hor must be of type int, ver must be of type int
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Game::inBounds(int x, int y, int hor, int ver)
{
    if (x + hor > this->caveSize - 1 || x + hor < 0 || y + ver > this->caveSize - 1 || y + ver < 0)
        // if coordinates fall outside of cave, return false
        return false;
    else
        // else, return true
        return true;
}

/********************************************************************
** Function: wumpusLogic
** Description: Main logic for Wumpus and arrow relationship
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
** Over 15 Line Justification: The function fulfills one main purpose. Excluding print lines, there are 15 lines
********************************************************************/
void Game::wumpusLogic()
{
    // print correct message for defeated wumpus
    if (this->p.defeatWumpus) {
        cout << "\nYou successfully shot the Wumpus!\n";
        this->removeGoldWumpus("W");
        this->pressEnter();
    }
    else {
        // else, inform user that their error missed the wumpus
        cout << "\nYou missed the Wumpus\n";
        this->pressEnter();

        // if player missed Wumpus, 75% chance Wumpus moves
        int moveWumpus = rand() % 4;
        if (!(moveWumpus == 0)) {
            bool noEvent = false;

            while (!noEvent) {
                // create two random coordinates
                int newX = rand() % this->caveSize;
                int newY = rand() % this->caveSize;

                // if room at coordinates has no event, end while loop
                if (!(this->cave[newX][newY].hasEvent())) {
                    noEvent = true;
                    this->removeGoldWumpus("W"); // remove Wumpus event
                    this->cave[newX][newY].setEvent(new Wumpus()); // set new Wumpus at new location
                }
            }
        }
    }
}

// ======================================== MAIN GAME LOGIC ========================================
/********************************************************************
** Function: getUserInput
** Description: Get user input for move versus shooting an arrow
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
** Over 15 Line Justification: Some extra lines are necessary for ncurses functionality. Function fulfills one main purpose
********************************************************************/
void Game::getUserInput()
{
    bool goodInput = false;
    
    while (!goodInput) {
        char input;
        // prompt user for move
        cout << "\n\nEnter move: ";
        cout << endl;
        // get move using ncurses
        ncursesFunctionality(input);
        // if first character is w, a, s, d call move function
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            goodInput = true;
            this->move(input);
        }
        // call arrow function
        else if (input == ' ') {
            // if first character is a space, get another input using ncurses
            ncursesFunctionality(input);
            // if second character is w, a, s, d call shoot arrow function
            if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                this->shootArrow(input);
                goodInput = true;
            }
        }
        else {
            // otherwise, continue while loop and print error message
            goodInput = false;
            cout << "\n\nPlease enter an acceptable input";
        }
    }
}

/********************************************************************
** Function: removeGoldWumpus
** Description: Remove Gold or Wumpus Event depending on parameter
** Parameters: string character
** Pre-Conditions: character must be of type string
** Post-Conditions: Does not return a value
********************************************************************/
void Game::removeGoldWumpus(string character)
{
    // loop through cave
    for (int i = 0; i < this->caveSize; i++)
        for (int j = 0; j < this->caveSize; j++)
            // if room has event with character, remove the event
            if (this->cave[i][j].hasEvent() && this->cave[i][j].getEvent()->eventChar() == character)
                this->cave[i][j].removeEvent();
}

/********************************************************************
** Function: play
** Description: Main logic for game flow
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::play()
{
    this->printInstructions();

    while (1) {
        this->printCave();
        // key for cave, print all characters if in debug mode
        cout << (this->debugMode ? "Player: * | Bats: B | Gold: G | Pit: P | Rope: R | Wumpus : W\n" : "Player: *\n");
        this->printInventory();
        this->printPercepts();
        this->getUserInput();
        
        if (this->p.isDead || this->leaveGame) {
            this->winLosePrint();
            break;
        }
    }
}

// ======================================== POST GAME ========================================
/********************************************************************
** Function: winLosePrint
** Description: Print correct message post game
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Game::winLosePrint() const
{
    // if user left the game and did not get gold or defeat wumpus, user lost game
    if (this->leaveGame && (!this->p.hasGold || !this->p.defeatWumpus))
        cout << "\n\nYou Lost\n";
    // if user left the game and has gold and defeat wumpus, user won game
    else if (this->leaveGame && this->p.hasGold && this->p.defeatWumpus)
        cout << "\n\nYou Won\n";
}

/********************************************************************
** Function: checkContinue
** Description: Get input for play again/quit options
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int Game::checkContinue()
{
    string input;

    while (1) {
        // prompt user
        cout << "\nChoose from the following options:\n(1) Play again with same cave configuration\n(2) Play again with new settings\n(3) Quit\n\n";
        cin >> input;

        // if user gave acceptable input, return as an int
        if (input == "1" || input == "2" || input == "3")
            return stoi(input);

        // print error message
        cout << "\nPlease enter an acceptable input";
    }
}