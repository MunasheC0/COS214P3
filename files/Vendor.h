#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"

/**
 * @brief A food/merchandise vendor whose point-of-sale service can be
 * suspended and restored by notices.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it locks its POS terminals on
 * CLOSE/EVACUATE and reactivates them on OPEN/RESUME.
 */
class Vendor : public EventUnit {
private:
    bool isServing;  ///< Whether this vendor is currently serving customers.

public:
    /**
     * @brief Constructs a vendor with a display name and queue capacity.
     *
     * The vendor starts closed but in the serving state.
     *
     * @param name Human-readable name of the vendor.
     * @param capacity Customer capacity of the vendor.
     */
    Vendor(std::string name, int capacity);

    /**
     * @brief Prints the base unit status plus whether the vendor is
     * currently serving.
     */
    virtual void reportStatus() override;

    /**
     * @brief Reacts to a notice by suspending or restoring service.
     *
     * CLOSE and EVACUATE lock the POS terminals and close the vendor;
     * OPEN and RESUME reactivate the terminals and open it. All other
     * notice types are ignored.
     *
     * @param notice The notice being delivered.
     */
    virtual void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~Vendor() = default;
};

#endif
