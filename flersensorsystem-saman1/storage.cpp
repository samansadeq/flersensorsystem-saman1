#include "storage.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

void MeasurementStorage::addMeasurement(const Measurement& m) {
    data.push_back(m);
}

void MeasurementStorage::printAll() const {
    std::cout << "\n--- All Measurements ---\n";
    for (const auto& m : data) {
        std::cout << m.timestamp << ", " << m.sensorName << ", "
            << std::fixed << std::setprecision(2)
            << m.value << " " << m.unit << "\n";
    }
}

void MeasurementStorage::printStatsPerSensor(const std::string& sensorName) const {
    std::vector<double> values;
    for (const auto& m : data)
        if (m.sensorName == sensorName)
            values.push_back(m.value);

    if (values.empty()) {
        std::cout << "No data for sensor: " << sensorName << "\n";
        return;
    }

    double sum = 0;
    for (double v : values) sum += v;
    double mean = sum / values.size();

    double minV = values[0], maxV = values[0];
    for (double v : values) {
        if (v < minV) minV = v;
        if (v > maxV) maxV = v;
    }

    double variance = 0;
    for (double v : values)
        variance += (v - mean) * (v - mean);
    variance /= values.size();
    double stdDev = std::sqrt(variance);

    std::cout << "\n--- Stats for " << sensorName << " ---\n";
    std::cout << "Count: " << values.size() << "\n";
    std::cout << "Mean: " << mean << "\n";
    std::cout << "Min: " << minV << "\n";
    std::cout << "Max: " << maxV << "\n";
    std::cout << "Std Dev: " << stdDev << "\n";
}

void MeasurementStorage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file for writing!\n";
        return;
    }
    for (const auto& m : data)
        file << m.timestamp << "," << m.sensorName << "," << m.value << "," << m.unit << "\n";

    std::cout << "Data saved to " << filename << "\n";
}

void MeasurementStorage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for reading!\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        Measurement m;
        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        size_t p3 = line.find(',', p2 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
            continue;

        m.timestamp = line.substr(0, p1);
        m.sensorName = line.substr(p1 + 1, p2 - p1 - 1);
        m.value = std::stod(line.substr(p2 + 1, p3 - p2 - 1));
        m.unit = line.substr(p3 + 1);
        data.push_back(m);
    }

    std::cout << "Data loaded from " << filename << "\n";
}
