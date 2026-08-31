#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include "EventSubject.h"
#include <vector>

class EventGroup : public EventComponent, public EventSubject {
protected:
    std::vector<EventComponent*> children;
    std::vector<EventObserver*> observers;

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

    // EventSubject Overrides (Stubs for Task 3 integration)
    virtual void attach(EventObserver* observer) override;
    virtual void detach(EventObserver* observer) override; 
    virtual void notify(Notice& notice) override; 

    virtual ~EventGroup(); 
};

#endif