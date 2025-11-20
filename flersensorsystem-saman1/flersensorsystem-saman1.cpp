#include <iostream>
#include "system_controller.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"
#include "pressure_sensor.h"

int main() {
    SystemController controller;

    controller.addSensor(std::make_unique<TemperatureSensor>("Temperature", 18, 30));
    controller.addSensor(std::make_unique<HumiditySensor>("Humidity", 30, 70));
    controller.addSensor(std::make_unique<PressureSensor>("Pressure", 950, 1050));

    int choice;
    do {
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
        std::cin >> choice;

        if (choice == 1) controller.sampleAllOnce();
        else if (choice == 2) {
            std::string n;
            std::cout << "Sensor name: ";
            std::cin >> n;
            controller.showStatsFor(n);
        }
        else if (choice == 3) controller.saveToFile("data.csv");
        else if (choice == 4) controller.configureThreshold();
        else if (choice == 5) controller.showAlerts();
        else if (choice == 6) controller.saveToFile("data.csv");
        else if (choice == 7) controller.loadFromFile("data.csv");

    } while (choice != 8);

    return 0;
}
