#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include <string>

class EventComponent {
protected:
    std::string name;
    int capacity;
    bool isOpen;

public:
    EventComponent(std::string name, int capacity);
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void reportStatus() = 0;
    virtual int getCapacity() = 0;
    std::string getName();
    virtual ~EventComponent() = default;
};

#endif