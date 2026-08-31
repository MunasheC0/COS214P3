#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <vector>
#include "EventObserver.h"
#include "Notice.h"

/**
 * @brief Top-level festival coordinator that issues notices to its
 * registered observers.
 *
 * ConcreteSubject (GoF Observer). EventControl is deliberately NOT part of
 * the Composite tree — it is not an EventComponent and has no capacity or
 * open/closed state; it only originates notifications. It holds its
 * observers through non-owning pointers and never deletes them.
 */
class EventControl {
private:
    std::vector<EventObserver*> observers;  ///< Non-owning list of registered EventObserver pointers; EventControl never deletes these.

public:
    /**
     * @brief Constructs a controller with no registered observers.
     */
    EventControl();

    /**
     * @brief Registers an observer for future event notifications.
     *
     * EventControl stores a non-owning pointer. The observer must remain
     * alive while registered and must be detached before destruction. A
     * pointer that is already registered is ignored, so an observer is
     * never notified twice for one notice.
     *
     * @param observer EventObserver to register. Must not be nullptr
     *        (a nullptr argument is ignored).
     */
    void attach(EventObserver* observer);

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
    void detach(EventObserver* observer);

    /**
     * @brief Delivers a notice to every currently attached observer.
     *
     * Observers are called in the order they were attached, via
     * EventObserver::update(). Attached RelayGroups forward the notice
     * further down their subtrees.
     *
     * @param notice The notice to broadcast. Not modified or stored by
     *        EventControl itself.
     */
    void notify(Notice& notice);

    /**
     * @brief Builds a Notice from the given details and broadcasts it.
     *
     * Convenience entry point for callers: constructs the Notice, logs it,
     * and delivers it to all observers via notify().
     *
     * @param type Category of the notice (see NoticeType).
     * @param message Human-readable description of the situation.
     * @param severity Urgency level; higher values indicate greater
     *        urgency.
     */
    void issueNotice(NoticeType type, std::string message, int severity);

    /**
     * @brief Virtual destructor.
     *
     * Declared virtual so any future subclass deletes correctly through an
     * EventControl* pointer. Observer pointers are non-owning, so none of
     * the registered observers are deleted here.
     */
    virtual ~EventControl();
};

#endif
