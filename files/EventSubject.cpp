#include "EventSubject.h"
#include <algorithm> // Required for std::find

void EventSubject::attach(EventObserver* observer) {
    if (observer == nullptr) return; // Safety check

    /*
     * Policy: Ignore Duplicates. Storing the same pointer twice would
     * mean the observer's update() runs twice for every single notify()
     * — duplicated reactions and log lines. The std::find check makes
     * attach() idempotent, so callers never need to remember whether an
     * observer is already registered. The stored pointer is non-owning:
     * attaching transfers no ownership whatsoever.
     */
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it == observers.end()) {
        observers.push_back(observer);
    }
}

void EventSubject::detach(EventObserver* observer) {
    if (observer == nullptr) return;

    /*
     * Policy: Safe Detach. If the observer isn't in the list, detach()
     * silently does nothing instead of failing: the caller's intent —
     * "stop notifying this observer" — already holds, so the call is
     * safe from teardown code that can't know whether the matching
     * attach() ever ran. The observer itself is never deleted here;
     * ownership stays entirely with the caller.
     */
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