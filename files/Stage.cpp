<<<<<<< Updated upstream
=======
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

void Stage::update(Notice& notice) {
    // Task 3 implementation stub
}
>>>>>>> Stashed changes
