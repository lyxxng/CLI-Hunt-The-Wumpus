#ifndef ROOM_H
#define ROOM_H

class Event;

class Room
{
private:
    Event* event;

public:
    Room();

    Event* getEvent();
    void setEvent(Event*);
    void removeEvent();
    bool hasEvent();
};

#endif