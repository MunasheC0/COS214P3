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

EventGroup::~EventGroup() {
    for (EventComponent* child : children) {
        delete child; 
    }
    children.clear();
}