#ifndef SHUTTLESTOP_H
#define SHUTTLESTOP_H

#include "EventUnit.h"
#include <string>

class ShuttleStop : public EventUnit {
private:
    std::string currentRoute;

public:
    ShuttleStop(std::string name, int capacity);
    virtual void reportStatus() override;
    virtual void update(Notice& notice) override;
    virtual ~ShuttleStop() = default;
};

#endif