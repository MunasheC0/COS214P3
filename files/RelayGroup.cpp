#include "RelayGroup.h"
#include <iostream>

RelayGroup::RelayGroup(std::string name, int capacity)
    : EventGroup(name, capacity) {}

void RelayGroup::update(const Notice& notice) {
    std::cout << "[RelayGroup " << name << "] Relaying notice: " << notice.message << "\n";
    
    for (EventComponent* child : children) {
        EventObserver* obs = dynamic_cast<EventObserver*>(child);
        if (obs) {
            obs->update(notice);
        }
    }

    notify(notice);
}