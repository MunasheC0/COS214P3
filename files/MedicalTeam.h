#ifndef MEDICALTEAM_H
#define MEDICALTEAM_H

#include "EventUnit.h"

/**
 * @brief A medical team whose triage readiness escalates during
 * emergencies rather than shutting down.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it responds to EVACUATE/WEATHER_ALERT by
 * going to maximum readiness — unlike other leaves, it never suspends
 * itself in response to an alert.
 */
class MedicalTeam : public EventUnit {
private:
    int readinessLevel;  ///< This team's current readiness level (0-10), escalated to maximum on EVACUATE/WEATHER_ALERT.

public:
    /**
     * @brief Constructs a medical team with a display name and treatment
     * capacity.
     *
     * The team starts closed with readiness level 0.
     *
     * @param name Human-readable name of the team.
     * @param capacity Patient capacity of the team.
     */
    MedicalTeam(std::string name, int capacity);

    /**
     * @brief Opens the medical post and raises readiness to full (10).
     */
    virtual void open() override;

    /**
     * @brief Closes the medical post and drops readiness to 0.
     */
    virtual void close() override;

    /**
     * @brief Prints the base unit status plus the current triage
     * readiness level out of 10.
     */
    virtual void reportStatus() override;

    /**
     * @brief Reacts to a notice by escalating readiness.
     *
     * EVACUATE and WEATHER_ALERT raise readiness to maximum (high alert).
     * All other notice types are ignored — the team stays active through
     * emergencies instead of shutting down.
     *
     * @param notice The notice being delivered.
     */
    virtual void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~MedicalTeam() = default;
};

#endif
