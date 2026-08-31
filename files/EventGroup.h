#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include <vector>

class EventGroup : public EventComponent {
protected:
    std::vector<EventComponent*> children;

public:
    EventGroup(std::string name, int capacity = 0);
    
    // Composite Management
    void add(EventComponent* component);
    void remove(EventComponent* component);
    EventComponent* getChild(int index);

    // Recursive EventComponent Overrides
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() override;
    virtual int getCapacity() override;

    virtual ~EventGroup();
};

#endif
