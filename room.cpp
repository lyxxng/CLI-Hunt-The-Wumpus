/********************************************************************
** Program: room.cpp
** Author: Lisa Young
** Date: 11/19/2022
** Description: Implementation file for Room class
** Input: N/A
** Output: Returns Event, sets Event, removes Event, checks if Room has Event
********************************************************************/

#include "room.h"
#include "event.h"
#include <iostream>

using namespace std;

/********************************************************************
** Function: Room class constructor
** Description: Default constructor for Room class
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Class is constructed
********************************************************************/
Room::Room()
{
    this->event = nullptr;
}

/********************************************************************
** Function: getEvent
** Description: Return Event pointer at Room
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type Event*
********************************************************************/
Event* Room::getEvent()
{
    return this->event;
}

/********************************************************************
** Function: setEvent
** Description: Give Room a new Event
** Parameters: Event* newEvent
** Pre-Conditions: newEvent must be of type Event*
** Post-Conditions: Does not return a value
********************************************************************/
void Room::setEvent(Event* newEvent)
{
    // if room has an event, remove event
    if (this->hasEvent())
        this->removeEvent();

    // event is equal to passed event
    this->event = newEvent;
}

/********************************************************************
** Function: removeEvent
** Description: Remove event from room
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Does not return a value
********************************************************************/
void Room::removeEvent()
{
    // delete event and set equal to NULL
    delete this->event;
    this->event = nullptr;
}

/********************************************************************
** Function: hasEvent
** Description: Check if Room has Event
** Parameters: N/A
** Pre-Conditions: Function must be called with no parameters
** Post-Conditions: Function returns value of type bool
********************************************************************/
bool Room::hasEvent()
{
    // return true if event is not NULL, return false if event is NULL
    return (this->event != nullptr);
}