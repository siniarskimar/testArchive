#ifndef IEVENTCALLBACK_H
#define IEVENTCALLBACK_H
#include "Event.h"


class IEventCallback {
public:
    virtual void call(Event& e) = 0;
    virtual void setId(uint8_t id) = 0;
    virtual uint8_t getId() = 0;
};

#endif