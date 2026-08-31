#include "EventSubject.h"
#include <algorithm> // Required for std::find

void EventSubject::attach(EventObserver* observer) {
    if (observer == nullptr) return; // Safety check
    
    // Policy: Ignore Duplicates
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it == observers.end()) {
        observers.push_back(observer);
    }
}

void EventSubject::detach(EventObserver* observer) {
    if (observer == nullptr) return;

    // Policy: Safe Detach
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void EventSubject::notify(const Notice& notice) {
    for (EventObserver* obs : observers) {
        if (obs != nullptr) {
            obs->update(notice);
        }
    }
}