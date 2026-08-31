#ifndef GATE_H
#define GATE_H

#include "EventUnit.h"

class Gate : public EventUnit {
private:
    bool isAdmitting;

public:
    Gate(std::string name, int capacity);
    virtual void reportStatus() override;
    virtual int getCapacity() override;
    virtual void update(Notice& notice) override;
    virtual ~Gate() = default;
};

#endif