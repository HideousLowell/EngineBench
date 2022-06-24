#include "OverheatTestBench.h"

OverheatTestBench::OverheatTestBench(IEngine* engine) { this->engine = engine; }

int OverheatTestBench::getTestResult(const double ambientTemperature) {
    engine->setAmbientTemperature(ambientTemperature);
    double overheatTemp = engine->getOverheatTemperature();
    double engineTemp = engine->getTemperature();
    int seconds = 0;
    double prevEps, eps;
    while (true) {
        prevEps = overheatTemp - engineTemp;
        engine->workForOneSecond();
        engineTemp = engine->getTemperature();
        eps = overheatTemp - engineTemp;
        if (prevEps - eps < kError) {
            seconds = -1;
            break;
        } else if (eps < 0) {
            break;
        }
        seconds++;
    }
    return seconds;
}

void OverheatTestBench::setEngine(IEngine* engine) { this->engine = engine; }

void OverheatTestBench::setError(const double error) { this->kError = error; }
