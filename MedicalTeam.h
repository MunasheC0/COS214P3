#ifndef MEDICALTEAM_H
#define MEDICALTEAM_H

#include "EventUnit.h"

class MedicalTeam : public EventUnit {
private:
    int readinessLevel;

public:
    MedicalTeam(std::string name, int capacity);
    virtual void open() override;
    virtual void close() override;
    virtual void reportStatus() override;
    virtual void update(Notice& notice) override;
    virtual ~MedicalTeam() = default;
};

#endif