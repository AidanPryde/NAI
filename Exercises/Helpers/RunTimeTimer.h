#ifndef _RUN_TIME_TIMER_H_
#define _RUN_TIME_TIMER_H_

#include <time.h>

class RunTimeTimer
{
public:
	RunTimeTimer();
	~RunTimeTimer();

	void addStartTime(clock_t started);
	void addEndTime(clock_t ended);

	double getRunTimeInMS();

private:
	clock_t Stared;
	clock_t Ended;
};

#endif