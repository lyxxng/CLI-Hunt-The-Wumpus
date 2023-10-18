/********************************************************************
** Program: gold.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Gold class
** Input: N/A
** Output: Percept and encounter for Gold class
********************************************************************/

#include "event.h"
#include "gold.h"

#include <iostream>
#include <string>

using namespace std;

/********************************************************************
** Function: Gold class constructor
** Description: Default constructor for Gold class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Gold::Gold() : Event()
{

}

/********************************************************************
** Function: eventChar
** Description: Returns Wumpus character for debug mode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type string
********************************************************************/
string Gold::eventChar() const
{
    return "G";
}

/********************************************************************
** Function: percept
** Description: Return percept for Gold
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Gold::percept() const
{
    cout << "\nYou see a glimmer nearby.";
}

/********************************************************************
** Function: encounter
** Description: Encounter logic for Gold
** Parameters: Game& g
** Pre-Conditions: g must be of type Game&
** Post-Conditions: Does not return a value
********************************************************************/
void Gold::encounter(Game& g)
{
    cout << "\nYou have discovered a pile of gold! You decide to take it with you\n";
    
    g.pressEnter(); // prompt user to press enter
    g.setPlayerGold(true); // player has gold
    g.removeGoldWumpus("G"); // remove Gold event from cave
}