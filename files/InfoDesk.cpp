#ifndef INFODESK_H
#define INFODESK_H

#include "EventUnit.h"
#include <string>

class InfoDesk : public EventUnit {
private:
    std::string currentSignage;

public:
    InfoDesk(std::string name, int capacity);
    void update( const Notice& notice) override;
    virtual ~InfoDesk() = default;
};

#endif