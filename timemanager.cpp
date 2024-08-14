#include "timemanager.h"

float TimeManager::start_time;
float TimeManager::current_time;

TimeManager::TimeManager()
{

}

void TimeManager::Init()
{
    start_time = current_time = 0;
}

float TimeManager::GetCurrentSecond()
{
    return current_time - start_time;
}

void TimeManager::UpdateTime()
{
    current_time += DELTA_TIME;
}
