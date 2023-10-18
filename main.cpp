/********************************************************************
** Program: main.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Loop gameplay and constructors/destructs games
** Input: N/A
** Output: N/A
********************************************************************/

#include "game.h"

#include <time.h>
#include <ncurses.h>

/********************************************************************
** Function: main
** Description: Main program logic, entry point of program
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type int
********************************************************************/
int main()
{
    srand(time(NULL));

    Game* g = new Game(); // create Game object
    
    while (1) {
        g->play(); // play game

        int playSetting = g->checkContinue();

        // if playSetting evaluates to 1, create new Game with new settings
        if (playSetting == 1) {
            int size = g->getCaveSize();
            vector<int> loc = g->getLocations();
            delete g;
            g = new Game(loc, size);
        }
        // if playSetting evaluates to 2, create new Game with same settings
        else if (playSetting == 2) {
            delete g;
            g = new Game();
        }
        // if playSetting evaluates to 3, call Game destructor
        else if (playSetting == 3) {
            delete g;
            break;
        }
    }
    return 0;
}