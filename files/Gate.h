#ifndef GATE_H
#define GATE_H

#include "EventUnit.h"

/**
 * @brief An entry gate that admits visitors and locks down when told to.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it stops admitting on CLOSE/EVACUATE and
 * reopens on OPEN/RESUME. While not admitting, it reports a capacity of 0.
 */
class Gate : public EventUnit {
private:
    bool isAdmitting;  ///< Whether this gate is currently admitting attendees.

public:
    /**
     * @brief Constructs a gate with a display name and throughput capacity.
     *
     * The gate starts closed but in the admitting state.
     *
     * @param name Human-readable name of the gate.
     * @param capacity Visitor capacity of the gate when admitting.
     */
    Gate(std::string name, int capacity);

    /**
     * @brief Prints the base unit status plus whether the gate is
     * currently admitting visitors.
     */
    virtual void reportStatus() override;

    /**
     * @brief Returns the gate's effective capacity.
     *
     * @return The configured capacity while admitting; 0 while locked
     *         down, so a locked gate contributes nothing to group totals.
     */
    virtual int getCapacity() override;

    /**
     * @brief Reacts to a notice by locking down or reopening the gate.
     *
     * CLOSE and EVACUATE stop admissions and close the gate; OPEN and
     * RESUME restore admissions and open it. All other notice types are
     * ignored.
     *
     * @param notice The notice being delivered.
     */
    virtual void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~Gate() = default;
};

#endif
