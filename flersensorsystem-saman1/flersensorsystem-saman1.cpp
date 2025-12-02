#include <iostream>
#include <string>
#include "system_controller.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"
#include "pressure_sensor.h"

int main() {
    SystemController controller;

    // Lägg till sensorer polymorft
    controller.addSensor(std::make_unique<TemperatureSensor>("Temperature", 18.0, 30.0));
    controller.addSensor(std::make_unique<HumiditySensor>("Humidity", 30.0, 70.0));
    controller.addSensor(std::make_unique<PressureSensor>("Pressure", 950.0, 1050.0));

    while (true) {
        std::cout << "\n=== SENSOR SYSTEM MENU ===\n";
        std::cout << "1. Sample all sensors\n";
        std::cout << "2. Show statistics\n";
        std::cout << "3. Show all measurements\n";
        std::cout << "4. Configure threshold rule\n";
        std::cout << "5. Show alerts\n";
        std::cout << "6. Save data\n";
        std::cout << "7. Load data\n";
        std::cout << "8. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10'000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 8) {
            std::cout << "Exiting...\n";
            break;
        }

        switch (choice) {
        case 1:
            controller.sampleAllOnce();
            break;

        case 2: {
            std::string name;
            std::cout << "Enter sensor name (Temperature / Humidity / Pressure): ";
            std::cin >> name;
            controller.showStatsFor(name);
            break;
        }

        case 3:
            // Visa alla mätvärden
            controller.printAllMeasurements();
            break;

        case 4:
            controller.configureThreshold();
            break;

        case 5:
            controller.showAlerts();
            break;

        case 6:
            controller.saveToFile("data.csv");
            break;

        case 7:
            controller.loadFromFile("data.csv");
            break;

        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
