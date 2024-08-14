#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H
#include <QObject>

class TimeManager
{


public:
    TimeManager();
    static void Init();
    static float GetCurrentSecond();
    static void UpdateTime();

private:
    static constexpr double DELTA_TIME = 0.05;
    static float start_time;
    static float current_time;


};

#endif // TIMEMANAGER_H
