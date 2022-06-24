#include "EngineBench.h"

#include "EngineData.h"

int main() {
    EngineData data;
    double ambientTemperature = readTemperature();
    try {
        InternalCombustionEngine engine(data);
        OverheatTestBench bench(&engine);
        ITestBench& benchInterface = bench;
        int seconds = benchInterface.getTestResult(ambientTemperature);
        printTime(seconds);
    } catch (const std::invalid_argument& e) {
        cerr << e.what();
    } catch (const std::out_of_range& e) {
        cerr << e.what();
    }
}

double readTemperature() {
    double ambientTemperature;
    std::cout << "Enter the ambient temperature" << std::endl;
    std::string buffer;
    std::cin >> buffer;
    try {
        ambientTemperature = std::stod(buffer);
    } catch (std::invalid_argument& ignore) {
        ambientTemperature = readTemperature();
    }
    return ambientTemperature;
}

void printTime(const int time) {
    if (time == -1)
        cout << "At this ambient temperature, the engine does not overheat" << endl;
    else
        cout << "Time of engine overheating: " << time << " sec" << endl;
}