#include "RunTimeTimer.h"

RunTimeTimer::RunTimeTimer()
{
}


RunTimeTimer::~RunTimeTimer()
{
}

void RunTimeTimer::addStartTime(clock_t started)
{
	Stared = started;
}

void RunTimeTimer::addEndTime(clock_t ended)
{
	Ended = ended;
}


double RunTimeTimer::getRunTimeInMS()
{
	return static_cast<double>(Ended - Stared) / CLOCKS_PER_SEC;
}