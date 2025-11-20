#include "pressure_sensor.h"

PressureSensor::PressureSensor(std::string id, double minV, double maxV)
    : id_(id), minV_(minV), maxV_(maxV) {
}

double PressureSensor::read() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minV_, maxV_);
    return dist(gen);
}

std::string PressureSensor::name() const { return id_; }
std::string PressureSensor::unit() const { return "hPa"; }
