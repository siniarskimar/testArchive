#ifndef EVENTCALLBACK_H
#define EVENTCALLBACK_H

#include "IEventCallback.h"
#include "EventManager.h"

template<typename T>
class EventCallback : public IEventCallback {
public:
    EventCallback(std::function<void(T&)> fn)
        : m_fn(fn), m_id(0) {}

    virtual void call(Event& e) override {
        if(m_fn != nullptr)
            m_fn(*(reinterpret_cast<T*>(&e)));
    }

    virtual void setId(uint8_t id) override {
        m_id = id;
    }
    virtual uint8_t getId() override {
        return m_id;
    }

    virtual void SetManager(EventManager& mgr) {
        m_manager = &mgr;
    }

    virtual EventManager* GetManager() const { return m_manager; }

    void Attach(EventType type) {
        GetManager()->Register(type, *this);
    }

	void Detach() {
        GetManager()->Unregister(*this);
	}

	void Detach(EventType type) {
        GetManager()->Unregister(type, *this);
	}


private:
    std::function<void(T&)> m_fn;
    uint8_t m_id;
    EventManager* m_manager;
};

#endif