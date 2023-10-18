#ifndef BATS_H
#define BATS_H

#include "event.h"

class Bats : public Event
{
public:
    Bats();

    string eventChar() const;
    void percept() const;
    void encounter(Game&);
};

#endif