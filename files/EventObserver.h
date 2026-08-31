#pragma once
#include "Notice.h"

class EventObserver {
public:
    // Required by the rubric: virtual destructor on every polymorphic base
    virtual ~EventObserver() = default;

    // Pure virtual function acting as the contract
    virtual void update(const Notice& notice) = 0;
};