#pragma once
#include <vector>
#include <memory>
#include <string>

#include "sensor.h"
#include "measurement.h"
#include "storage.h"
#include "threshold.h"
#include "alert.h"

class SystemController {
public:
    void addSensor(std::unique_ptr<Sensor> s);
    void sampleAllOnce();
    void configureThreshold();
    void showAlerts() const;
    void showStatsFor(const std::string& name) const;
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);
    void printAllMeasurements() const;

private:
    std::vector<std::unique_ptr<Sensor>> sensors_;
    std::vector<Threshold> thresholds_;
    std::vector<Alert> alerts_;
    MeasurementStorage storage_;
};
