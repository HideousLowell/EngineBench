#pragma once

#include <vector>

#include "EngineData.h"
#include "IEngine.h"

class InternalCombustionEngine : public IEngine {
 private:
    double momentOfInertsia;
    double overheatTemperature;
    double Hm;
    double Hv;
    double C;

    double curSpeed;
    double curTorque;

    double engineTemperature = 0;
    double ambientTemperature = 0;

    std::vector<double> torque;
    std::vector<double> crankshaftSpeed;

    double heatingRate();
    double coolingRate();
    double getCurrentTorque();

 public:
    InternalCombustionEngine(const EngineData& data);
    double getTemperature();
    double getOverheatTemperature();
    void setAmbientTemperature(const double temperature);
    void workForOneSecond();
};