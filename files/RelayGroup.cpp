#include "RelayGroup.h"
#include <iostream>

RelayGroup::RelayGroup(std::string name, int capacity)
    : EventGroup(name, capacity) {}

/*
 * This is the whole reason RelayGroup exists as a subclass instead of
 * EventGroup implementing EventObserver itself: only the nodes that sit
 * inside an actual notification cascade pay for (and expose) the Observer
 * role. Plain EventGroups can't be attached to a subject at all — the
 * type system rejects them — so one attach() of a RelayGroup at the top
 * of a subtree is all the wiring a cascade needs.
 *
 * The relay walks the composite's own children rather than a separate
 * observer list, reusing the tree as the delivery route. dynamic_cast
 * filters who actually receives the notice: leaves (EventUnit derives
 * from EventObserver) and nested RelayGroups pass the cast and get
 * update()'d — which recurses the cascade further down — while a plain
 * EventGroup child fails the cast and is skipped, exactly because it
 * opted out of the Observer role.
 */
void RelayGroup::update(const Notice& notice) {
    std::cout << "[RelayGroup " << name << "] Relaying notice: " << notice.message << "\n";

    for (EventComponent* child : children) {
        EventObserver* obs = dynamic_cast<EventObserver*>(child);
        if (obs) {
            obs->update(notice);
        }
    }
}