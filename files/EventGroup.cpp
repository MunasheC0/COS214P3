#include "EventGroup.h"
#include <iostream>
#include <algorithm>

EventGroup::EventGroup(std::string name, int capacity)
    : EventComponent(name, capacity) {} 

/*
 * Ownership handover point: add() is where a group TAKES ownership of a
 * component. Together with remove() below, this is what makes moving a
 * unit between two parents safe:
 *
 *     oldParent->remove(unit);   // releases ownership, does NOT delete
 *     newParent->add(unit);      // new parent takes ownership
 *
 * At every moment exactly one group considers itself the owner, so when
 * the destructors eventually run, the unit is deleted exactly once — by
 * whichever group holds it at that time. If remove() deleted the unit,
 * the transfer idiom above would hand add() a dangling pointer; if add()
 * copied instead of adopting, nobody would be clearly responsible for
 * the original.
 */
void EventGroup::add(EventComponent* component) {
    if (component) {
        children.push_back(component);
    }
}

/*
 * remove() only erases the pointer from the children vector — it
 * deliberately does NOT delete the component. The caller gets ownership
 * back and decides what happens next: delete it, keep it standalone, or
 * add() it to another group (see the transfer note above add()). Deleting
 * here would make the transfer use case impossible without copying, and
 * would double-delete any unit the caller still holds a pointer to.
 */
void EventGroup::remove(EventComponent* component) {
    auto it = std::find(children.begin(), children.end(), component);
    if (it != children.end()) {
        children.erase(it);
    }
}

EventComponent* EventGroup::getChild(int index) {
    if (index >= 0 && index < static_cast<int>(children.size())) {
        return children[index]; 
    }
    return nullptr;
}

void EventGroup::open() {
    isOpen = true; 
    std::cout << "\n[Group Opening] " << name << "\n";
    for (EventComponent* child : children) {
        child->open(); 
    }
}

void EventGroup::close() {
    isOpen = false; 
    std::cout << "\n[Group Closing] " << name << "\n";
    for (EventComponent* child : children) {
        child->close(); 
    }
}

void EventGroup::reportStatus() {
    std::cout << "\n=== Group Status: " << name 
              << " | State: " << (isOpen ? "OPEN" : "CLOSED") 
              << " | Total Capacity: " << getCapacity() << " ===\n";
    for (EventComponent* child : children) {
        child->reportStatus(); 
    }
}

int EventGroup::getCapacity() {
    int totalCapacity = capacity;
    for (EventComponent* child : children) {
        totalCapacity += child->getCapacity(); 
    }
    return totalCapacity;
}

/*
 * The destructor deletes children and ONLY children. The composite tree
 * is the single owner of every component in it: whatever was add()'ed
 * here (and not remove()'d since) dies with the group, recursively, so
 * deleting the root of a tree tears down the whole festival structure.
 *
 * Observer registrations are a different relationship entirely. Subjects
 * (EventControl, EventSubject) hold observers as non-owning raw pointers:
 * an observer like a Stage or RelayGroup is already owned by exactly one
 * place — its parent group in this tree. If subjects also deleted their
 * observer pointers, every attached unit would be deleted twice (once by
 * its owning group, once by the subject). Keeping observer lists strictly
 * non-owning means there is one owner per object and one delete per
 * object, here.
 */
EventGroup::~EventGroup() {
    for (EventComponent* child : children) {
        delete child;
    }
    children.clear();
}