#ifndef RELAYGROUP_H
#define RELAYGROUP_H

#include "EventGroup.h"
#include "EventObserver.h"

class RelayGroup : public EventGroup, public EventObserver {
public:
    RelayGroup(std::string name, int capacity);
    void update(const Notice& notice) override;
    virtual ~RelayGroup() = default;
};

#endif