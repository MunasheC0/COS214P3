#pragma once
#include "Notice.h"

/**
 * @brief Abstract interface for anything that reacts to festival notices.
 *
 * Observer (GoF Observer). Concrete leaves (Stage, Gate, Vendor,
 * MedicalTeam, ShuttleStop, InfoDesk) and RelayGroup implement update()
 * with their own reaction. Subjects (EventControl, EventSubject) hold
 * observers only through this interface and never own them.
 */
class EventObserver {
public:
    /**
     * @brief Virtual destructor.
     *
     * Declared virtual so a concrete observer can be deleted safely through
     * an EventObserver* base pointer (required on every polymorphic base).
     */
    // Required by the rubric: virtual destructor on every polymorphic base
    virtual ~EventObserver() = default;

    /**
     * @brief Receives a notice broadcast by a subject and reacts to it.
     *
     * Each concrete observer decides for itself which NoticeType values it
     * cares about and how its internal state changes in response.
     *
     * @param notice The notice being delivered. Read-only; observers must
     *        not assume it outlives the call.
     */
    // Pure virtual function acting as the contract
    virtual void update(const Notice& notice) = 0;
};
