#include "sensor.h"
#include <random>

Sensor::Sensor(const std::string& n, const std::string& u, double minV, double maxV)
    : name(n), unit(u), minValue(minV), maxValue(maxV) {
}

double Sensor::read() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minValue, maxValue);
    return dist(gen);
}

std::string Sensor::getName() const { return name; }
std::string Sensor::getUnit() const { return unit; }
