#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include <vector>

/**
 * @brief A group node in the festival tree that holds and manages child
 * components, forwarding every operation to them recursively.
 *
 * Composite (GoF Composite). EventGroup owns its children: pointers passed
 * to add() are deleted in the destructor.
 *
 * Note that EventGroup deliberately plays no Observer-pattern role — it is
 * not an EventObserver and cannot be attached to a subject. Grouping and
 * notification are kept as separate concerns: only RelayGroup, the subclass
 * that adds the Observer role, participates in notification cascades. A
 * plain EventGroup is purely structural.
 */
class EventGroup : public EventComponent {
protected:
    std::vector<EventComponent*> children;  ///< Owning list of child EventComponent pointers; ~EventGroup() deletes each one.

public:
    /**
     * @brief Constructs an empty group with a display name and base
     * capacity.
     *
     * @param name Human-readable name of the group.
     * @param capacity Base capacity of the group itself, excluding
     *        children; defaults to 0 so a group normally contributes only
     *        its children's capacity.
     */
    EventGroup(std::string name, int capacity = 0);

    // Composite Management

    /**
     * @brief Adds a child component to this group.
     *
     * The group TAKES OWNERSHIP of the pointed-to component: it will be
     * deleted in ~EventGroup(). The caller must not delete it afterwards,
     * and the same pointer must not be added to (or remain in) another
     * owning group at the same time, or it would be deleted twice.
     *
     * @param component Heap-allocated child to adopt. A nullptr argument
     *        is ignored.
     */
    void add(EventComponent* component);

    /**
     * @brief Removes a child component from this group WITHOUT deleting it.
     *
     * Ownership transfers back to the caller, who becomes responsible for
     * either deleting the component or handing it to a new owning group
     * via add(). Removing a pointer that is not a child is a silent no-op.
     *
     * @param component Child to release from this group.
     */
    void remove(EventComponent* component);

    /**
     * @brief Returns the child at the given position.
     *
     * The group RETAINS OWNERSHIP of the returned component; the caller
     * must not delete it and must not use the pointer after this group is
     * destroyed.
     *
     * @param index Zero-based position of the child.
     * @return Non-owning pointer to the child, or nullptr if index is out
     *         of range.
     */
    EventComponent* getChild(int index);

    // Recursive EventComponent Overrides

    /**
     * @brief Opens this group and then every child, recursively.
     */
    virtual void open() override;

    /**
     * @brief Closes this group and then every child, recursively.
     */
    virtual void close() override;

    /**
     * @brief Prints the group's status followed by every child's status,
     * recursively, to standard output.
     */
    virtual void reportStatus() override;

    /**
     * @brief Computes the total capacity of this subtree.
     *
     * @return The group's own base capacity plus the capacities of all
     *         children, aggregated recursively.
     */
    virtual int getCapacity() override;

    /**
     * @brief Virtual destructor; deletes every remaining child.
     *
     * Declared virtual so subclasses (RelayGroup) destruct correctly when
     * deleted through an EventComponent* or EventGroup* pointer. Only the
     * owned children are deleted — see the implementation for why nothing
     * else is.
     */
    virtual ~EventGroup();
};

#endif
