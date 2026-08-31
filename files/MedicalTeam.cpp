#include "MedicalTeam.h"
#include <iostream>

MedicalTeam::MedicalTeam(std::string name, int capacity)
    : EventUnit(name, capacity), readinessLevel(0) {}

void MedicalTeam::open() {
    EventUnit::open();
    readinessLevel = 10;
}

void MedicalTeam::close() {
    EventUnit::close();
    readinessLevel = 0;
}

void MedicalTeam::reportStatus() {
    EventUnit::reportStatus();
    std::cout << "  -> Triage Readiness Level: " << readinessLevel << "/10\n";
}

void MedicalTeam::update(Notice& notice) {
    // Task 3 implementation stub
}