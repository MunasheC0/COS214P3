#ifndef SHUTTLESTOP_H
#define SHUTTLESTOP_H

#include "EventUnit.h"
#include <string>

/**
 * @brief A shuttle stop whose transit route reacts to schedule changes
 * and safety alerts.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it announces SCHEDULE_CHANGE updates and
 * suspends its route entirely on EVACUATE/WEATHER_ALERT.
 */
class ShuttleStop : public EventUnit {
private:
    std::string currentRoute;  ///< The route this shuttle stop is currently serving.

public:
    /**
     * @brief Constructs a shuttle stop with a display name and waiting
     * capacity.
     *
     * The stop starts closed on the default "Main Loop Express" route.
     *
     * @param name Human-readable name of the stop.
     * @param capacity Passenger capacity of the stop.
     */
    ShuttleStop(std::string name, int capacity);

    /**
     * @brief Prints the base unit status plus the currently active
     * transit route.
     */
    virtual void reportStatus() override;

    /**
     * @brief Reacts to a notice by updating or suspending the route.
     *
     * SCHEDULE_CHANGE announces the route update; EVACUATE and
     * WEATHER_ALERT mark the route SUSPENDED and close the stop. All
     * other notice types are ignored.
     *
     * @param notice The notice being delivered.
     */
    virtual void update( const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~ShuttleStop() = default;
};

#endif
