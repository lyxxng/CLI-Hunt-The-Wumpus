#ifndef EVENT_H
#define EVENT_H

#include "game.h"

#include <string>

using namespace std;

class Event
{
public:
    Event();

    virtual string eventChar() const = 0;
    virtual void percept() const = 0;
    virtual void encounter(Game&) = 0;
};

#endif