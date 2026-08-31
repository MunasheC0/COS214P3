#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include <vector>
#include "EventObserver.h"
#include "Notice.h"

class EventControl {
private:
    std::vector<EventObserver*> observers;

public:
    EventControl();
    void attach(EventObserver* observer);
    void detach(EventObserver* observer);
    void notify(Notice& notice);
    void issueNotice(NoticeType type, std::string message, int severity);
    virtual ~EventControl();
};

#endif