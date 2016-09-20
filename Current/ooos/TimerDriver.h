#pragma once

class TimerDriver
{
public:
	TimerDriver(void);
	~TimerDriver(void);


	static void TimerISR();
	static void RawISR();

	static volatile unsigned long Ticks;

};
