#include "EventComponent.h"

EventComponent::EventComponent(std::string name, int capacity)
    : name(name), capacity(capacity), isOpen(false) {}

std::string EventComponent::getName() {
    return name;
}