#ifndef STAGE_H
#define STAGE_H

#include "EventUnit.h"

/**
 * @brief A performance stage that can pause and resume its show in
 * response to notices.
 *
 * Leaf (GoF Composite) and ConcreteObserver (GoF Observer), via EventUnit.
 * The two roles serve separate collaborations: as a leaf it sits in the
 * festival tree; as an observer it reacts to notices by pausing on
 * WEATHER_ALERT/CLOSE and resuming on RESUME/OPEN.
 */
class Stage : public EventUnit {
private:
    bool isPerformancePaused;  ///< Whether the performance on this stage is currently paused.

public:
    /**
     * @brief Constructs a stage with a display name and audience capacity.
     *
     * The stage starts closed with no performance paused.
     *
     * @param name Human-readable name of the stage.
     * @param capacity Audience capacity of the stage.
     */
    Stage(std::string name, int capacity);

    /**
     * @brief Opens the stage and un-pauses the performance.
     */
    virtual void open() override;

    /**
     * @brief Closes the stage and pauses the performance.
     */
    virtual void close() override;

    /**
     * @brief Prints the base unit status plus whether the performance is
     * currently paused.
     */
    virtual void reportStatus() override;

    /**
     * @brief Reacts to a notice by pausing or resuming the performance.
     *
     * WEATHER_ALERT and CLOSE pause the performance; RESUME and OPEN
     * resume it. All other notice types are ignored.
     *
     * @param notice The notice being delivered.
     */
    virtual void update(const Notice& notice) override;

    /**
     * @brief Virtual destructor, for safe deletion through a base pointer
     * (EventComponent*, EventObserver* or EventUnit*).
     */
    virtual ~Stage() = default;
};

#endif
