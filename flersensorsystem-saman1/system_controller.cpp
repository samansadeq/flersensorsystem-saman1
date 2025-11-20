#include "system_controller.h"
#include "utils.h"   // for timestamp
#include <iostream>
#include <iomanip>

// --------------------------------------------
// Add a new sensor (polymorphic storage)
// --------------------------------------------
void SystemController::addSensor(std::unique_ptr<Sensor> s) {
    sensors_.push_back(std::move(s));
}

// --------------------------------------------
// Read all sensors once, store measurement,
// check thresholds and register alerts
// --------------------------------------------
void SystemController::sampleAllOnce() {
    for (auto& sensor : sensors_) {
        double value = sensor->read();
        std::string now = getCurrentTime();

        // Store measurement
        Measurement m{
            sensor->name(),
            sensor->unit(),
            value,
            now
        };
        storage_.addMeasurement(m);

        // Check all thresholds
        for (const auto& t : thresholds_) {
            if (t.sensorName == sensor->name()) {

                bool triggered = false;

                if (t.over && value > t.limit)
                    triggered = true;
                else if (!t.over && value < t.limit)
                    triggered = true;

                if (triggered) {
                    Alert alert;
                    alert.timestamp = now;
                    alert.sensorName = sensor->name();
                    alert.measuredValue = value;

                    if (t.over)
                        alert.rule = "Value > " + std::to_string(t.limit);
                    else
                        alert.rule = "Value < " + std::to_string(t.limit);

                    alerts_.push_back(alert);

                    std::cout << "\n*** LARM UTLÖST ***\n"
                        << "Sensor: " << alert.sensorName << "\n"
                        << "Värde: " << alert.measuredValue << " " << sensor->unit() << "\n"
                        << "Regel: " << alert.rule << "\n"
                        << "Tid: " << alert.timestamp << "\n";
                }
            }
        }
    }

    std::cout << "\nAlla sensorer avlästa!\n";
}

// --------------------------------------------
// Configure a threshold rule
// --------------------------------------------
void SystemController::configureThreshold() {
    Threshold t;

    std::cout << "\n--- Konfigurera tröskelregel ---\n";

    std::cout << "Ange sensorns namn (t.ex. Temperature, Humidity, Pressure): ";
    std::cin >> t.sensorName;

    std::cout << "Ange tröskelvärde: ";
    std::cin >> t.limit;

    int direction;
    std::cout << "1 = larma om värde > tröskeln\n";
    std::cout << "2 = larma om värde < tröskeln\n";
    std::cout << "Val: ";
    std::cin >> direction;

    t.over = (direction == 1);

    thresholds_.push_back(t);

    std::cout << "\nTröskelregel tillagd!\n";
}

// --------------------------------------------
// Show all alerts
// --------------------------------------------
void SystemController::showAlerts() const {
    std::cout << "\n--- Aktiva larm ---\n";

    if (alerts_.empty()) {
        std::cout << "Inga larm registrerade.\n";
        return;
    }

    for (const auto& a : alerts_) {
        std::cout << "[" << a.timestamp << "] "
            << a.sensorName << ": "
            << a.measuredValue << "  "
            << "(" << a.rule << ")\n";
    }
}

// --------------------------------------------
// Show statistics for a specific sensor
// --------------------------------------------
void SystemController::showStatsFor(const std::string& name) const {
    storage_.printStatsPerSensor(name);
}

// --------------------------------------------
// Save to CSV file
// --------------------------------------------
void SystemController::saveToFile(const std::string& path) const {
    storage_.saveToFile(path);
}

// --------------------------------------------
// Load from CSV file
// --------------------------------------------
void SystemController::loadFromFile(const std::string& path) {
    storage_.loadFromFile(path);
}
