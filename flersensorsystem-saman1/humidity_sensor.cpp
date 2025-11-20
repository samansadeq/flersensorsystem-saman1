#include "humidity_sensor.h"

HumiditySensor::HumiditySensor(std::string id, double minV, double maxV)
    : id_(id), minV_(minV), maxV_(maxV) {
}

double HumiditySensor::read() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minV_, maxV_);
    return dist(gen);
}

std::string HumiditySensor::name() const { return id_; }
std::string HumiditySensor::unit() const { return "%"; }
