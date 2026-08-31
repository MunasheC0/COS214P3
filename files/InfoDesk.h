#ifndef INFODESK_H
#define INFODESK_H

#include "EventUnit.h"
#include <string>

/**
 * @brief An information desk that relays incoming notices to festival
 * visitors.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it announces every notice it receives,
 * acting as the visitor-facing voice of the notification system.
 */
class InfoDesk : public EventUnit {
private:
    std::string currentSignage;  ///< The message currently displayed on this info desk's signage.

public:
    /**
     * @brief Constructs an info desk with a display name and service
     * capacity.
     *
     * The desk starts closed, showing the default "General Information"
     * signage.
     *
     * @param name Human-readable name of the desk.
     * @param capacity Visitor capacity of the desk.
     */
    InfoDesk(std::string name, int capacity);

    /**
     * @brief Reacts to a notice by announcing its message.
     *
     * Every notice, regardless of type, is echoed to standard output for
     * visitors at the desk.
     *
     * @param notice The notice being delivered.
     */
    void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~InfoDesk() = default;
};

#endif
