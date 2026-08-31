#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"

class Vendor : public EventUnit {
private:
    bool isServing;

public:
    Vendor(std::string name, int capacity);
    virtual void reportStatus() override;
    virtual void update(Notice& notice) override;
    virtual ~Vendor() = default;
};

#endif