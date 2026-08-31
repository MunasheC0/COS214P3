#include "ShuttleStop.h"
#include <iostream>

ShuttleStop::ShuttleStop(std::string name, int capacity)
    : EventUnit(name, capacity), currentRoute("Main Loop Express") {}

void ShuttleStop::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> Active Transit Route: " << currentRoute << "\n";
}

void ShuttleStop::update(Notice& notice) {
    // Task 3 implementation stub
}