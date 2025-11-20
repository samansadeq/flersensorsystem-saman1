#include "temperature_sensor.h"

TemperatureSensor::TemperatureSensor(std::string id, double minV, double maxV)
    : id_(id), minV_(minV), maxV_(maxV) {
}

double TemperatureSensor::read() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minV_, maxV_);
    return dist(gen);
}

std::string TemperatureSensor::name() const { return id_; }
std::string TemperatureSensor::unit() const { return "°C"; }

