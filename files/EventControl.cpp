#include "EventControl.h"
#include <iostream>
#include <algorithm>

EventControl::EventControl() {}

void EventControl::attach(EventObserver* observer) {
    if (observer) {
        /*
         * Duplicate attaches are ignored on purpose: if the same pointer
         * were stored twice, every notify() would call that observer's
         * update() twice per notice — a Gate would lock down twice, logs
         * would double up. Checking with std::find makes attach()
         * idempotent, so callers don't have to track whether they already
         * registered an observer.
         */
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it == observers.end()) {
            observers.push_back(observer);
        }
    }
}

void EventControl::detach(EventObserver* observer) {
    if (observer) {
        /*
         * Detaching an observer that isn't registered is a silent no-op
         * rather than an error: the caller's goal ("this observer must no
         * longer receive notices") is already satisfied, so detach() is
         * safe to call defensively — e.g. from teardown paths that don't
         * know whether the attach ever happened.
         */
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

/*
 * Only the pointers are dropped — no observer is ever deleted here.
 * EventControl's observer list is strictly NON-OWNING: every registered
 * observer (a Stage, a RelayGroup, ...) is owned by the Composite tree,
 * whose EventGroup parent deletes it. If EventControl also deleted them,
 * each attached unit would be destroyed twice. Clearing the vector is
 * all the cleanup a non-owning reference list needs.
 */
EventControl::~EventControl() {
    observers.clear();
}