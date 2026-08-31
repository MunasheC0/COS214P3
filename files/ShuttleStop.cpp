#include "ShuttleStop.h"
#include <iostream>

ShuttleStop::ShuttleStop(std::string name, int capacity)
    : EventUnit(name, capacity), currentRoute("Main Loop Express") {}

void ShuttleStop::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> Active Transit Route: " << currentRoute << "\n";
}

void ShuttleStop::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::SCHEDULE_CHANGE:
            std::cout << "[ShuttleStop " << name << "] Route update: " << notice.message << "\n";
            break;
        case NoticeType::EVACUATE:
        case NoticeType::WEATHER_ALERT:
            currentRoute = "SUSPENDED";
            std::cout << "[ShuttleStop " << name << "] Transit halted due to alert: " << notice.message << "\n";
            this->close();
            break;
        default:
            break;
    }
}