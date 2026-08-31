#include "EventControl.h"
#include <iostream>
#include <algorithm>

EventControl::EventControl() {}

void EventControl::attach(EventObserver* observer) {
    if (observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it == observers.end()) {
            observers.push_back(observer);
        }
    }
}

void EventControl::detach(EventObserver* observer) {
    if (observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }
}

void EventControl::notify(Notice& notice) {
    for (EventObserver* observer : observers) {
        if (observer) {
            observer->update(notice);
        }
    }
}

void EventControl::issueNotice(NoticeType type, std::string message, int severity) {
    Notice notice{type, message, severity};
    std::cout << "\n[EventControl] Issuing Notice -> " << message << " (Severity: " << severity << ")\n";
    notify(notice);
}

EventControl::~EventControl() {
    observers.clear();
}