/********************************************************************
** Program: pit.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Pit class
** Input: N/A
** Output: Percept and encounter for Pit class
********************************************************************/

#include "event.h"
#include "pit.h"

#include <iostream>
#include <string>

using namespace std;

/********************************************************************
** Function: Pit class constructor
** Description: Default constructor for Pit class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Pit::Pit() : Event()
{

}

/********************************************************************
** Function: eventChar
** Description: Returns Pit character for debug mode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type string
********************************************************************/
string Pit::eventChar() const
{
    return "P";
}

/********************************************************************
** Function: percept
** Description: Return percept for Pit
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Pit::percept() const
{
    cout << "\nYou feel a breeze.";
}

/********************************************************************
** Function: encounter
** Description: Encounter logic for Pit
** Parameters: Game& g
** Pre-Conditions: g must be of type Game&
** Post-Conditions: Does not return a value
********************************************************************/
void Pit::encounter(Game& g)
{
    cout << "\nOops! You accidentally slipped and fell into a bottomless pit\n";

    // player is dead
    g.setPlayerDead(true);
    
    cout << "\033[1;31mYOU DIED\033[0m\n";
}