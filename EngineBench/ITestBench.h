#pragma once
#include "IEngine.h"

class ITestBench {
 protected:
    IEngine* engine;

 public:
    int virtual getTestResult(const double) = 0;
    void virtual setEngine(IEngine*) = 0;
};
