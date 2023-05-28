#ifndef SDIZOPROJEKT2_TIMER_H
#define SDIZOPROJEKT2_TIMER_H
#include <windows.h>
#include <iostream>
#include <iomanip>

class Timer {
private:
    int _frequency;
    double _startTime;
    bool _isRunning;
    double read_QPC();
public:
    void start();
    double getElapsedTime_ms();
    void stop();
};


#endif //SDIZOPROJEKT2_TIMER_H
