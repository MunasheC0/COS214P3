#ifndef EVENTUNIT_H
#define EVENTUNIT_H

#include "EventComponent.h"
#include "EventObserver.h"

/**
 * @brief Abstract base for all single (non-group) festival units, providing
 * the shared default behaviour for opening, closing and reporting.
 *
 * Leaf base (GoF Composite) and Observer (GoF Observer). These are two
 * separate collaborations, not a duplicated pattern: as an EventComponent
 * it is a childless node in the Composite tree, while as an EventObserver
 * it can be attached to a subject and receive notices. update() stays pure
 * virtual so each concrete leaf defines its own reaction.
 */
class EventUnit : public EventComponent, public EventObserver {
public:
    /**
     * @brief Constructs a unit with a display name and fixed capacity.
     *
     * The unit starts in the closed state.
     *
     * @param name Human-readable name of the unit.
     * @param capacity Capacity of this single unit.
     */
    EventUnit(std::string name, int capacity);

    /**
     * @brief Marks the unit as open.
     */
    virtual void open() override;

    /**
     * @brief Marks the unit as closed.
     */
    virtual void close() override;

    /**
     * @brief Prints the unit's name, open/closed state and capacity to
     * standard output.
     */
    virtual void reportStatus() override;

    /**
     * @brief Returns the unit's capacity.
     *
     * A leaf has no children, so this is simply the capacity given at
     * construction.
     *
     * @return Capacity of this single unit.
     */
    virtual int getCapacity() override;

    /**
     * @brief Reacts to a notice; each concrete leaf supplies its own
     * behaviour.
     *
     * Left pure virtual on purpose: opening/closing/reporting are uniform
     * across leaves, but how a unit responds to a notice is exactly what
     * distinguishes one leaf type from another.
     *
     * @param notice The notice being delivered.
     */
    virtual void update(const Notice& notice) = 0;

    /**
     * @brief Virtual destructor.
     *
     * Declared virtual so concrete leaves can be deleted through an
     * EventComponent* or EventObserver* base pointer (EventGroup deletes
     * its children through EventComponent*).
     */
    virtual ~EventUnit() = default;
};

#endif
