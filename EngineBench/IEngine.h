#pragma once

class IEngine {
 public:
    void virtual setAmbientTemperature(const double) = 0;
    double virtual getTemperature() = 0;
    double virtual getOverheatTemperature() = 0;
    void virtual workForOneSecond() = 0;
};