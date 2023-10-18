/********************************************************************
** Program: rope.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Rope class
** Input: N/A
** Output: Encounter for Rope class
********************************************************************/

#include "event.h"
#include "rope.h"

#include <iostream>
#include <string>

using namespace std;

/********************************************************************
** Function: Rope class constructor
** Description: Default constructor for Rope class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Rope::Rope() : Event()
{
    
}

/********************************************************************
** Function: eventChar
** Description: Returns Rope character for debug mode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type string
********************************************************************/
string Rope::eventChar() const
{
    return "R";
}

/********************************************************************
** Function: percept
** Description: Empty function (Rope does not have a percept)
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Rope::percept() const
{
    
}

/********************************************************************
** Function: encounter
** Descirption: Encounter logic for Rope
** Parameters: Game& g
** Pre-Conditions: g must be of type Game&
** Post-Conditions: Does not return a value
********************************************************************/
void Rope::encounter(Game& g)
{
    string input;

    while (1) {
        cout << "\nYou found the rope! Would you like to escape? ";
        // if user has not defeated wumpus and gotten gold, print warning
        cout << (g.getDefeatWumpus() && g.getHasGold() ? "(y/n): " : "Note: If you leave now, you will lose the game! (y/n): ");
        getline(cin, input);

        if (input == "y" || input == "Y") {
            g.setLeaveGame(true); // user leaves game
            return;
        }
        if (input == "n" || input == "N")
            return;
        
        // print error message
        cout << "\n\nPlease enter an acceptable input";
    }
}