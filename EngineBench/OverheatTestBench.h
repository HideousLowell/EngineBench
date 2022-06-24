#pragma once
#include "IEngine.h"
#include "ITestBench.h"
#include "InternalCombustionEngine.h"

class OverheatTestBench : public ITestBench {
 private:
    double kError = 1e-6;

 public:
    OverheatTestBench(IEngine* engine);
    int virtual getTestResult(const double ambientTemperature);
    void virtual setEngine(IEngine* engine);
    void setError(double error);
};