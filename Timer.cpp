#include "Timer.h"

double Timer::read_QPC() {
    LARGE_INTEGER count;
    DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldmask);
    return((double)count.QuadPart);
}

void Timer::start(){
    _isRunning = true;
    QueryPerformanceFrequency((LARGE_INTEGER *)&_frequency);
    _startTime = read_QPC();
}

double Timer::getElapsedTime_ms(){
    if(!_isRunning)
        return 0;

    double elapsed = read_QPC() - _startTime;

    return (1000.0 * elapsed) / _frequency;
}
void Timer::stop(){
    _isRunning = false;
}