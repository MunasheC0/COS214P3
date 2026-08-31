#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

/**
 * @brief Abstract base for every node in the festival's event tree; defines
 * the uniform interface shared by single units and whole groups.
 *
 * Component (GoF Composite). Both leaves (EventUnit and its subclasses) and
 * composites (EventGroup) derive from this class, so clients can treat an
 * individual stall and an entire festival zone identically through
 * open(), close(), reportStatus() and getCapacity().
 */
class EventComponent {
protected:
    std::string name;  ///< The display name of this event component.
    int capacity;      ///< This component's maximum capacity.
    bool isOpen;       ///< Whether this component is currently open.

public:
    /**
     * @brief Constructs a component with a display name and base capacity.
     *
     * The component starts in the closed state.
     *
     * @param name Human-readable name of this component (e.g. "Main Stage").
     * @param capacity Base capacity of this component itself, excluding any
     *        children a derived composite may later hold.
     */
    EventComponent(std::string name, int capacity);

    /**
     * @brief Opens this component to the public.
     *
     * Composites are expected to open themselves and then all children
     * recursively; leaves simply mark themselves open.
     */
    virtual void open() = 0;

    /**
     * @brief Closes this component to the public.
     *
     * Composites are expected to close themselves and then all children
     * recursively; leaves simply mark themselves closed.
     */
    virtual void close() = 0;

    /**
     * @brief Prints this component's current status to standard output.
     *
     * Composites report their own status followed by every child's,
     * producing a full status listing of the subtree.
     */
    virtual void reportStatus() = 0;

    /**
     * @brief Computes the capacity of this component.
     *
     * For leaves this is the base capacity; composites aggregate their own
     * base capacity plus the capacities of all children recursively.
     *
     * @return Total capacity of this component (including any subtree).
     */
    virtual int getCapacity() = 0;

    /**
     * @brief Returns the component's display name.
     *
     * @return Copy of the name given at construction.
     */
    std::string getName();

    /**
     * @brief Virtual destructor.
     *
     * Declared virtual so that deleting a derived object through an
     * EventComponent* (as EventGroup's destructor does for its children)
     * runs the correct derived destructor instead of slicing cleanup.
     */
    virtual ~EventComponent() = default;
};

#endif
