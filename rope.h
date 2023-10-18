#ifndef ROPE_H
#define ROPE_H

#include "event.h"

class Rope : public Event
{
public:
    Rope();

    string eventChar() const;
    void percept() const;
    void encounter(Game&);
};

#endif