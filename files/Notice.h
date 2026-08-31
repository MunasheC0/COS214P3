#pragma once
#include <string>


enum class NoticeType {
    // Ordinary operational changes
    OPEN,
    CLOSE,
    SCHEDULE_CHANGE, 
    PAUSE,           
    RESUME,          

    // Capacity-related change
    CAPACITY_ALERT,  

    // Safety-related changes
    WEATHER_ALERT,   
    EVACUATE         
};


struct Notice {
    NoticeType type;
    std::string message;
    int severity; 
    Notice(NoticeType t, std::string m, int s = 1) 
        : type(t), message(m), severity(s) {}
};