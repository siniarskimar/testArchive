#ifndef EVENT_H
#define EVENT_H

enum EventType {
    eKeyPressedType,
    eKeyReleasedType,
    eWindowMovedType,
    eWindowResizedType,
    eWindowClosedType
};

enum EventCategory {
    eKeyEventCategory,
    eWindowEventCategory
};


class Event {
public:
    virtual EventType GetType() = 0;
    virtual EventCategory GetCategory() = 0;
};

#endif