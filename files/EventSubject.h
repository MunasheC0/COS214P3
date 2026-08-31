#pragma once
#include <vector>
#include "EventObserver.h"
#include "Notice.h"

/**
 * @brief Reusable base class for anything that broadcasts notices to a set
 * of registered observers.
 *
 * Subject (GoF Observer). Provides a complete, ready-to-inherit
 * implementation of attach()/detach()/notify() over a list of non-owning
 * EventObserver pointers.
 *
 * @note No class in the current implementation inherits EventSubject:
 * EventControl implements the same Subject role with its own equivalent
 * attach()/detach()/notify() instead of deriving from this class, and
 * RelayGroup relays over its Composite children rather than a separate
 * observer list. This class therefore exists as a reusable Subject base
 * rather than an active participant in the running system.
 */
class EventSubject {
protected:
    std::vector<EventObserver*> observers;  ///< Non-owning list of registered EventObserver pointers; never deleted by this subject.

public:
    /**
     * @brief Virtual destructor.
     *
     * Declared virtual so a derived subject can be deleted through an
     * EventSubject* base pointer. Observer pointers are non-owning, so the
     * destructor deliberately deletes none of them.
     */
    virtual ~EventSubject() = default;

    /**
     * @brief Registers an observer for future event notifications.
     *
     * This EventSubject stores a non-owning pointer. The observer must
     * remain alive while registered and must be detached before destruction.
     * A pointer that is already registered is ignored, so an observer is
     * never notified twice for one notice.
     *
     * @param observer EventObserver to register. Must not be nullptr
     *        (a nullptr argument is ignored).
     */
    virtual void attach(EventObserver* observer);

    /**
     * @brief Unregisters a previously attached observer.
     *
     * Only the stored pointer is removed; the observer itself is never
     * deleted — the caller retains full ownership. Detaching an observer
     * that was never attached is a silent no-op.
     *
     * @param observer EventObserver to remove. May be a pointer that was
     *        never attached; nullptr is ignored.
     */
    virtual void detach(EventObserver* observer);

    /**
     * @brief Delivers a notice to every currently attached observer.
     *
     * Observers are called in the order they were attached, via
     * EventObserver::update().
     *
     * @param notice The notice to broadcast. Passed by const reference;
     *        the subject does not keep a copy after the call returns.
     */
    virtual void notify(const Notice& notice);
};
