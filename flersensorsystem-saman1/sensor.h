#pragma once
#include <string>

class Sensor {
public:
    virtual ~Sensor() = default; // destructor
    virtual double read() = 0;                   // pure virtual -> must override
    virtual std::string name() const = 0;        // pure virtual
    virtual std::string unit() const = 0;        // pure virtual
};

