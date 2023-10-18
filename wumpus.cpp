/********************************************************************
** Program: wumpus.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Wumpus class
** Input: N/A
** Output: Percept and encounter for Wumpus class
********************************************************************/

#include "event.h"
#include "wumpus.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

/********************************************************************
** Function: Wumpus class constructor
** Description: Default constructor for Wumpus class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Wumpus::Wumpus() : Event()
{

}

/********************************************************************
** Function: eventChar
** Description: Returns Wumpus character for debug mode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type string
********************************************************************/
string Wumpus::eventChar() const
{
    return "W";
}

/********************************************************************
** Function: percept
** Description: Return percept for Wumpus
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Wumpus::percept() const
{
    cout << "\nYou smell a terrible stench.";
}

/********************************************************************
** Function: encounter
** Description: Encounter logic for Wumpus
** Parameters: Game& g
** Pre-Conditions: g must be of type Game&
** Post-Conditions: Does not return a value
********************************************************************/
void Wumpus::encounter(Game& g)
{
    cout << "\nUh oh! You ran into the Wumpus. He chews you into pieces and spits you out.\n";

    // player is dead
    g.setPlayerDead(true);

    cout << "\033[1;31mYOU DIED\033[0m\n";
}