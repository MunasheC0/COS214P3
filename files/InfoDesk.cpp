#include "InfoDesk.h"
#include <iostream>

InfoDesk::InfoDesk(std::string name, int capacity) : EventUnit(name, capacity) {
    currentSignage = "General Information"; // Initialize your private variable if you want
}

void InfoDesk::update(const Notice& notice) {
    std::cout << "[InfoDesk " << name << "] Received Notice: " << notice.message << "\n";
}