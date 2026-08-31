#ifndef STAGE_H
#define STAGE_H

#include "EventUnit.h"

class Stage : public EventUnit {
private:
    bool isPerformancePaused;

public:
    Stage(std::string name, int capacity);
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() override;
    virtual void update(Notice& notice) override;
    virtual ~Stage() = default;
};

#endif