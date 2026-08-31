#pragma once
#include <vector>
#include "EventObserver.h"
#include "Notice.h"

class EventSubject {
protected:
    std::vector<EventObserver*> observers;

public:
    virtual ~EventSubject() = default;

    virtual void attach(EventObserver* observer);
    virtual void detach(EventObserver* observer);
    virtual void notify(const Notice& notice);
};