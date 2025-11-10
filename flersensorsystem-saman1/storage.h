#pragma once
#include <vector>
#include <string>
#include "measurement.h"

class MeasurementStorage {
private:
    std::vector<Measurement> data;

public:
    void addMeasurement(const Measurement& m);
    void printAll() const;
    void printStatsPerSensor(const std::string& sensorName) const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

