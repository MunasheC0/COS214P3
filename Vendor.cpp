#include "Vendor.h"
#include <iostream>

Vendor::Vendor(std::string name, int capacity)
    : EventUnit(name, capacity), isServing(true) {} 

void Vendor::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> POS Ready/Serving: " << (isServing ? "Yes" : "No") << "\n";
}

void Vendor::update(Notice& notice) {
}