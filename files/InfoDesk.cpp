#include "InfoDesk.h"
#include <iostream>

// This is the specific block of code the linker is looking for!
InfoDesk::InfoDesk(std::string name, int capacity) : EventUnit(name, capacity) {
    currentSignage = "General Information"; // Initialize your private variable if you want
}

// Ensure your update method is also implemented here so you don't get another error!
void InfoDesk::update(const Notice& notice) {
    std::cout << "[InfoDesk " << name << "] Received Notice: " << notice.message << "\n";
    // Add any specific logic you need based on the NoticeType
}