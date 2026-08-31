#pragma once
#include <string>


/**
 * @brief Categories of notices that can flow through the festival's
 * notification system.
 *
 * Observers filter on this value to decide whether a notice concerns them
 * (e.g. a Vendor reacts to WEATHER_ALERT, an InfoDesk to SCHEDULE_CHANGE).
 */
enum class NoticeType {
    // Ordinary operational changes
    OPEN,
    CLOSE,
    SCHEDULE_CHANGE,
    PAUSE,
    RESUME,

    // Capacity-related change
    CAPACITY_ALERT,

    // Safety-related changes
    WEATHER_ALERT,
    EVACUATE
};


/**
 * @brief Plain data object describing a single event notification.
 *
 * Not a GoF pattern participant itself — it is the parameter object passed
 * from subjects into EventObserver::update() (and through
 * EventSubject/EventControl::notify()), bundling what happened (type),
 * a human-readable message, and how urgent it is (severity).
 */
struct Notice {
    NoticeType type;      /**< Category of the notice; observers filter on this. */
    std::string message;  /**< Human-readable description of the situation. */
    int severity;         /**< Urgency level; higher means more severe. */

    /**
     * @brief Constructs a notice from its category, message and severity.
     *
     * @param t Category of the notice (see NoticeType).
     * @param m Human-readable message describing the situation.
     * @param s Severity level, defaulting to 1 (routine); higher values
     *        indicate greater urgency.
     */
    Notice(NoticeType t, std::string m, int s = 1)
        : type(t), message(m), severity(s) {}
};
