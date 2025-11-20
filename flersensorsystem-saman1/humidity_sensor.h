#pragma once
#include "sensor.h"
#include <string>
#include <random>

class HumiditySensor : public Sensor {
public:
    HumiditySensor(std::string id, double minV, double maxV);
    double read() override;
    std::string name() const override;
    std::string unit() const override;

private:
    std::string id_;
    double minV_;
    double maxV_;
};

