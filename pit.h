#ifndef PIT_H
#define PIT_H

#include "event.h"

class Pit : public Event
{
public:
    Pit();

    string eventChar() const;
    void percept() const;
    void encounter(Game&);
};

#endif