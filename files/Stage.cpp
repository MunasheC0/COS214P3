#include "Stage.h"
#include <iostream>

Stage::Stage(std::string name, int capacity)
    : EventUnit(name, capacity), isPerformancePaused(false) {}

void Stage::open() {
    EventUnit::open();
    isPerformancePaused = false;
}

void Stage::close() {
    EventUnit::close();
    isPerformancePaused = true;
}

void Stage::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> Performance Paused: " << (isPerformancePaused ? "Yes" : "No") << "\n";
}

void Stage::update(const Notice& notice) {
    switch (notice.type) {
        case NoticeType::WEATHER_ALERT:
        case NoticeType::CLOSE:
            isPerformancePaused = true;
            std::cout << "[Stage " << name << "] Performance paused due to notice: " << notice.message << "\n";
            break;
        case NoticeType::RESUME:
        case NoticeType::OPEN:
            isPerformancePaused = false;
            std::cout << "[Stage " << name << "] Performance resumed.\n";
            break;
        default:
            break;
    }
}