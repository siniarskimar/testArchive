#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IEventCallback.h"

class EventManager {
public:
    EventManager();

    void Register(EventType type, IEventCallback& cb);

    // Unregister specific type from callback
    void Unregister(EventType type, IEventCallback& cb);

    // Unregister callback from all types
    void Unregister(IEventCallback& cb);

    void Dispatch(Event& e);

private:
    uint8_t m_idCount;
    std::vector<std::pair<EventType, IEventCallback*>> m_callbacks;
};

#endif // !EVENTMANAGER_H
