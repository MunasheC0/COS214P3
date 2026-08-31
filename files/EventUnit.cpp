#include "EventUnit.h"
#include <iostream>

EventUnit::EventUnit(std::string name, int capacity)
    : EventComponent(name, capacity) {}

void EventUnit::open() {
    isOpen = true;
}

void EventUnit::close() {
    isOpen = false;
}

void EventUnit::reportStatus() {
    std::cout << "Unit: " << name << " | Status: " << (isOpen ? "Open" : "Closed") 
              << " | Capacity: " << capacity << "\n";
}

int EventUnit::getCapacity() {
    return capacity;
}