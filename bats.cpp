/********************************************************************
** Program: bats.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Bats class
** Input: N/A
** Output: Percept and encounter for Bats class
********************************************************************/

#include "event.h"
#include "bats.h"

#include <iostream>
#include <string>

using namespace std;

/********************************************************************
** Function: Bats class constructor
** Description: Default constructor for Bats class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Bats::Bats() : Event()
{

}

/********************************************************************
** Function: eventChar
** Description: Returns Bats character for debug mode
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type string
********************************************************************/
string Bats::eventChar() const
{
    return "B";
}

/********************************************************************
** Function: percept
** Description: Return percept for Bats
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Bats::percept() const
{
    cout << "\nYou hear wings flapping.";
}

/********************************************************************
** Function: encounter
** Description: Encounter logic for Bats
** Parameters: Game& g
** Pre-Conditions: g must be of type Game&
** Post-Conditions: Does not return a value
********************************************************************/
void Bats::encounter(Game& g)
{
    cout << "\nOh no! You walked into a room of super bats. You've been transported to a random room\n";

    g.pressEnter();

    bool newCoords = false;

    while (!newCoords) {
        // create two new random coordinates
        int newRandX = rand() % g.getCaveSize();
        int newRandY = rand() % g.getCaveSize();

        // if new coordinates are not equal to player's current room
        if (g.getPlayerX() != newRandX && g.getPlayerY() != newRandY) {
            newCoords = true; // end loop
            // set player coordinates equal to new coordinates
            g.setPlayerX(newRandX);
            g.setPlayerY(newRandY);
            // if room at new coordinates has an event, trigger encounter function
            if (g.getCave(newRandX, newRandY).hasEvent())
                g.getCave(newRandX, newRandY).getEvent()->encounter(g);
        }
    }
}