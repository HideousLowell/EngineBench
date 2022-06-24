#include "InternalCombustionEngine.h"

#include <stdexcept>

using std::vector;

double InternalCombustionEngine::coolingRate() { return C * (ambientTemperature - engineTemperature); }
double InternalCombustionEngine::heatingRate() { return curTorque * Hm + curSpeed * curSpeed * Hv; }
double InternalCombustionEngine::getTemperature() { return engineTemperature; }
double InternalCombustionEngine::getOverheatTemperature() { return overheatTemperature; }

void InternalCombustionEngine::setAmbientTemperature(const double temperature) {
    engineTemperature = ambientTemperature = temperature;
}

void InternalCombustionEngine::workForOneSecond() {
    curTorque = getCurrentTorque();
    double acceleration = curTorque / momentOfInertsia;
    curSpeed += acceleration;
    engineTemperature += heatingRate() + coolingRate();
}

inline double linearInterpolation(double x, double x1, double x2, double y1, double y2) {
    return y2 + ((y1 - y2) / (x1 - x2)) * (x - x2);
}

double InternalCombustionEngine::getCurrentTorque() {
    std::size_t index = -1;
    for (std::size_t i = 0; i < crankshaftSpeed.size(); i++)
        if (curSpeed < crankshaftSpeed[i]) {
            index = i;
            break;
        }
    if (index == -1) throw std::out_of_range("Out of array");
    double x1 = crankshaftSpeed[index - 1];
    double x2 = crankshaftSpeed[index];
    double y1 = torque[index - 1];
    double y2 = torque[index];
    return linearInterpolation(curSpeed, x1, x2, y1, y2);
}

InternalCombustionEngine::InternalCombustionEngine(const EngineData& data) {
    if (data.torque.size() < 2 || data.crankshaftSpeed.size() < 2 ||
        data.torque.size() != data.crankshaftSpeed.size())
        throw std::invalid_argument("Number of values of torque/crankshaftspeed must equal and > 1");
    momentOfInertsia = data.momentOfInertsia;
    overheatTemperature = data.overheatTemperature;
    Hm = data.Hm;
    Hv = data.Hv;
    C = data.C;
    torque = data.torque;
    crankshaftSpeed = data.crankshaftSpeed;
    curTorque = torque[0];
    curSpeed = crankshaftSpeed[0];
}
