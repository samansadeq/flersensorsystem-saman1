#pragma once
#include <string>

struct Alert {
    std::string timestamp;
    std::string sensorName;
    double measuredValue;
    std::string rule;
};