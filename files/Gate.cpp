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

void Gate::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::CLOSE:
        case NoticeType::EVACUATE:
            isAdmitting = false;
            this->close();
            std::cout << "[Gate " << name << "] Locked down: " << notice.message << "\n";
            break;
        case NoticeType::OPEN:
        case NoticeType::RESUME:
            isAdmitting = true;
            this->open();
            std::cout << "[Gate " << name << "] Open for entry.\n";
            break;
        default:
            break;
    }
}