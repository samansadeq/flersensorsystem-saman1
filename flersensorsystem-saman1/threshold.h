#pragma once
#include <string>

struct Threshold {
    std::string sensorName;
    double limit;
    bool over; // true = alert if value > limit, false = alert if value < limit
};
