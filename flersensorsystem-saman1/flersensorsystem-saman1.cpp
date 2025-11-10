#include <iostream>
#include "sensor.h"
#include "measurement.h"
#include "storage.h"
#include "utils.h"

int main() {
    Sensor temp("Temperature", "°C", 18.0, 30.0);
    Sensor hum("Humidity", "%", 30.0, 70.0);
    MeasurementStorage storage;

    int choice;
    do {
        std::cout << "\n=== SENSOR SYSTEM MENU ===\n";
        std::cout << "1. Read new measurements\n";
        std::cout << "2. Show statistics per sensor\n";
        std::cout << "3. Show all measurements\n";
        std::cout << "4. Save measurements to file\n";
        std::cout << "5. Load measurements from file\n";
        std::cout << "6. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input!\n";
            continue;
        }

        if (choice == 1) {
            Measurement m1{ temp.getName(), temp.getUnit(), temp.read(), getCurrentTime() };
            Measurement m2{ hum.getName(), hum.getUnit(), hum.read(), getCurrentTime() };
            storage.addMeasurement(m1);
            storage.addMeasurement(m2);
            std::cout << "Measurements added!\n";
        }
        else if (choice == 2) {
            std::string name;
            std::cout << "Enter sensor name: ";
            std::cin >> name;
            storage.printStatsPerSensor(name);
        }
        else if (choice == 3) storage.printAll();
        else if (choice == 4) storage.saveToFile("measurements.csv");
        else if (choice == 5) storage.loadFromFile("measurements.csv");
        else if (choice == 6) std::cout << "Exiting...\n";
        else std::cout << "Invalid choice!\n";
    } while (choice != 6);

    return 0;
}
