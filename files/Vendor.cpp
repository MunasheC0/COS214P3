#include "Vendor.h"
#include <iostream>

Vendor::Vendor(std::string name, int capacity)
    : EventUnit(name, capacity), isServing(true) {} 

void Vendor::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> POS Ready/Serving: " << (isServing ? "Yes" : "No") << "\n";
}

void Vendor::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::CLOSE:
        case NoticeType::EVACUATE:
            isServing = false;
            std::cout << "[Vendor " << name << "] POS Terminals locked down: " << notice.message << "\n";
            this->close();
            break;
        case NoticeType::OPEN:
        case NoticeType::RESUME:
            isServing = true;
            std::cout << "[Vendor " << name << "] POS Terminals active.\n";
            this->open();
            break;
        default:
            break;
    }
}