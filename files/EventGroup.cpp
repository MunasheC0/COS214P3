#include "EventGroup.h"
#include <iostream>
#include <algorithm>

EventGroup::EventGroup(std::string name, int capacity)
    : EventComponent(name, capacity) {} 

void EventGroup::add(EventComponent* component) {
    if (component) {
        children.push_back(component);
    }
}

void EventGroup::remove(EventComponent* component) {
    auto it = std::find(children.begin(), children.end(), component);
    if (it != children.end()) {
        children.erase(it); 
    }
}

EventComponent* EventGroup::getChild(int index) {
    if (index >= 0 && index < static_cast<int>(children.size())) {
        return children[index]; 
    }
    return nullptr;
}

void EventGroup::open() {
    isOpen = true; 
    std::cout << "\n[Group Opening] " << name << "\n";
    for (EventComponent* child : children) {
        child->open(); 
    }
}

void EventGroup::close() {
    isOpen = false; 
    std::cout << "\n[Group Closing] " << name << "\n";
    for (EventComponent* child : children) {
        child->close(); 
    }
}

void EventGroup::reportStatus() {
    std::cout << "\n=== Group Status: " << name 
              << " | State: " << (isOpen ? "OPEN" : "CLOSED") 
              << " | Total Capacity: " << getCapacity() << " ===\n";
    for (EventComponent* child : children) {
        child->reportStatus(); 
    }
}

int EventGroup::getCapacity() {
    int totalCapacity = capacity;
    for (EventComponent* child : children) {
        totalCapacity += child->getCapacity(); 
    }
    return totalCapacity;
}

void EventGroup::update(const Notice& notice) {
    // 1. React locally if needed
    std::cout << "[EventGroup " << name << "] Processing notice: " << notice.message << "\n";
    
    // 2. Cascade down to all child components (Composite pattern propagation)
    for (EventComponent* child : children) {
        EventObserver* obs = dynamic_cast<EventObserver*>(child);
        if (obs) {
            obs->update(notice);
        }
    }

    // 3. Trigger base class notification for any attached observers
    notify(notice);
}

EventGroup::~EventGroup() {
    for (EventComponent* child : children) {
        delete child; 
    }
    children.clear();
}