#include <iostream>
#include <iomanip>
#include <functional>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include "EventCallback.h"

class KeyEvent : public Event {
public:
    virtual EventCategory GetCategory() { return eKeyEventCategory; }
};

class KeyPressedEvent : public KeyEvent {
public:
    static EventType StaticGetType() { return eKeyPressedType; }
    virtual EventType GetType() { return StaticGetType(); }
};
class KeyReleasedEvent : public KeyEvent {
public:
    static EventType StaticGetType() { return eKeyReleasedType; }
    virtual EventType GetType() { return StaticGetType(); }
};

int main(int argc, char** argv) {
    {
        EventManager eManager;
        auto generalCallback = [](Event& e) {
            std::cout << "Event type: ";
            switch(e.GetType()) {
            case eKeyPressedType:
                std::cout << "KeyPressedEvent" << std::endl;
                break;
            case eKeyReleasedType:
                std::cout << "KeyReleasedEvent" << std::endl;
                break;
            default:
                std::cout << "Unknown" << std::endl;
            }
        };
        auto keyPressedCallback = [](KeyPressedEvent& e) {
            std::cout << "Key pressed" << std::endl;
        };
        auto keyReleasedCallback = [](KeyPressedEvent& e) {
            std::cout << "Key released" << std::endl;
        };

        EventCallback<KeyPressedEvent> generalCb(generalCallback);
        EventCallback<KeyPressedEvent> keyPressedCb(keyPressedCallback);
        EventCallback<KeyPressedEvent> keyReleasedCb(keyReleasedCallback);

        //eManager.Register(eKeyPressedType, generalCb);
        //eManager.Register(eKeyReleasedType, generalCb);
        //eManager.Register(eKeyPressedType, keyPressedCb);
        //eManager.Register(eKeyReleasedType, keyReleasedCb);
        //
        // OR
        //
        generalCb.SetManager(eManager);
        keyPressedCb.SetManager(eManager);
        keyReleasedCb.SetManager(eManager);

        generalCb.Attach(eKeyPressedType);
        generalCb.Attach(eKeyReleasedType);
        keyReleasedCb.Attach(eKeyReleasedType);
        keyPressedCb.Attach(eKeyPressedType);

        KeyPressedEvent ekp;
        KeyReleasedEvent ekr;
        eManager.Dispatch(ekp);
        eManager.Dispatch(ekr);

        //eManager.Unregister(eKeyReleasedType, generalCb);
        //
        //OR
        //
        generalCb.Detach();

        std::cout << "\nSecond run" << std::endl;

        eManager.Dispatch(ekp);
        eManager.Dispatch(ekr);
    }
    std::cin.get();
    return 0;
}

EventManager::EventManager()
    : m_idCount(0) {}

void EventManager::Register(EventType type, IEventCallback& cb) {
    if(cb.getId() == 0)
        cb.setId(++m_idCount);

    m_callbacks.emplace_back(type, &cb);
}

// Unregister specific type from callback
void EventManager::Unregister(EventType type, IEventCallback& cb) {
    if(m_callbacks.empty())
        return;

    m_callbacks.erase(
        std::remove_if(m_callbacks.begin(), m_callbacks.end(), [&cb, &type](std::pair<EventType, IEventCallback*> pair) {
            return (pair.second->getId() == cb.getId()) && (pair.first == type);
        }),
        m_callbacks.end());
}

// Unregister callback from all types
void EventManager::Unregister(IEventCallback& cb) {
    if(m_callbacks.empty())
        return;

    m_callbacks.erase(
        std::remove_if(m_callbacks.begin(), m_callbacks.end(), [&cb](std::pair<EventType, IEventCallback*> pair) {
            return pair.second->getId() == cb.getId();
        }),
        m_callbacks.end());
}

void EventManager::Dispatch(Event& e) {
    for(auto pair : m_callbacks) {
        if(pair.first == e.GetType()) {
            pair.second->call(e);
        }
    }
}