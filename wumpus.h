#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"

class Wumpus : public Event
{
public:
    Wumpus();

    string eventChar() const;
    void percept() const;
    void encounter(Game&);
    void arrowLogic(Game&);
};

#endif