#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "EventObserver.h"

class EventUnit : public EventComponent, public EventObserver {
public:
    EventUnit(std::string name, int capacity);
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() override;
    virtual int getCapacity() override;
    virtual void update(Notice& notice) = 0 override;
    virtual ~EventUnit() = default;
};

#endif