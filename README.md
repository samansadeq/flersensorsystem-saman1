# flersensorsystem-saman1
GitHub repo link: https://github.com/samansadeq/flersensorsystem-saman1
--------------------------------------------

Flersensorsystem – Arv, Polymorfism och Tröskellarm
Introduktion

Detta projekt är en utökning av Inlämningsuppgift 1 och 2. Systemet simulerar flera sensorer, lagrar mätdata, utför statistik och hanterar filinläsning. I INL2 har projektet vidareutvecklats för att använda arv, polymorfism, abstrakta klasser samt ett tröskelbaserat larmsystem.

Översikt av funktionalitet

Abstrakt basklass för Sensor med rena virtuella funktioner

Tre konkreta sensorer: TemperatureSensor, HumiditySensor, PressureSensor

Polymorf lagring av sensorer via std::vector<std::unique_ptr<Sensor>>

Simulering av mätvärden med slumpgenerator

Lagring av mätdata i MeasurementStorage

Statistik per sensor (medelvärde, min, max, antal, standardavvikelse)

Sparning och läsning av mätdata i CSV-format

Konfigurerbara tröskelregler (över/under ett värde)

Larm som registreras när en tröskel bryts

Meny för att hantera hela systemet

Teknisk design

Systemarkitekturen består av:

Sensor (abstrakt klass): read(), name(), unit()

TemperatureSensor, HumiditySensor, PressureSensor: konkreta implementationer

Measurement: struktur för mätvärden

MeasurementStorage: lagring, utskrift och statistik

Threshold och Alert: enkla datastrukturer för larmhantering

SystemController: kopplar samman sensorer, lagring, larm och filhantering

main.cpp: meny och programflöde

UML-klassdiagram (textformat)
                 <<abstract>>
                    Sensor
   ------------------------------------
    + read() : double
    + name() : string
    + unit() : string
   ------------------------------------
        ^           ^            ^
        |           |            |
Temperature   Humidity     Pressure
Sensor         Sensor        Sensor
-----------------------------------------
- id_ : string
- minV_ : double
- maxV_ : double
-----------------------------------------
+ read() : double
+ name() : string
+ unit() : string

SystemController
-----------------------------------------
- sensors_ : vector<unique_ptr<Sensor>>
- thresholds_ : vector<Threshold>
- alerts_ : vector<Alert>
- storage_ : MeasurementStorage
-----------------------------------------
+ addSensor()
+ sampleAllOnce()
+ configureThreshold()
+ showAlerts()
+ showStatsFor()
+ saveToFile()
+ loadFromFile()

Projektstruktur (förenklad)
sensor.h                     (abstrakt basklass)
temperature_sensor.h/.cpp
humidity_sensor.h/.cpp
pressure_sensor.h/.cpp
system_controller.h/.cpp     (styr logiken)
measurement.h
storage.h/.cpp               (lagring och statistik)
threshold.h
alert.h
utils.h/.cpp                 (timestamp)
main.cpp
README.md
