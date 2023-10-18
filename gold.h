#ifndef GOLD_H
#define GOLD_H

#include "event.h"

class Gold : public Event
{
public:
    Gold();

    string eventChar() const;
    void percept() const;
    void encounter(Game&);
};

#endif