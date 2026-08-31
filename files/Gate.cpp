#include "Gate.h"
#include <iostream>

Gate::Gate(std::string name, int capacity)
    : EventUnit(name, capacity), isAdmitting(true) {}

void Gate::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> Admitting Visitors: " << (isAdmitting ? "Yes" : "No") << "\n";
}

int Gate::getCapacity() {
    return isAdmitting ? capacity : 0;
}

void Gate::update(Notice& notice) {
    // Task 3 implementation stub
}