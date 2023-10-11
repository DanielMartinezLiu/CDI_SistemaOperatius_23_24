#pragma once
#include <mutex>
#include <functional>

class Timer 
{
public:
	typedef std::function<void()> OnTimeElapsed;
	typedef std::function<bool()> OnTimeElapsedWithLoop;

	static void StartTimer(unsigned long timerRequiredMiliseconds, OnTimeElapsed onTimeElapse);
	static void StartLoopTimer(unsigned long timerRequiredMiliseconds, OnTimeElapsedWithLoop onTimeElapse);
};