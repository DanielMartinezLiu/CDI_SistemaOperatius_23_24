#include "Timer.h"
#include "ConsoleControl.h"

void Timer::StartTimer(unsigned long timerRequiredMiliseconds, OnTimeElapsed onTimeElapse)
{
	std::thread* thread = new std::thread([timerRequiredMiliseconds, onTimeElapse]() {
			ConsoleControl::Wait(timerRequiredMiliseconds);
			onTimeElapse();
		});
	thread->detach();
}

void Timer::StartLoopTimer(unsigned long timerRequiredMiliseconds, OnTimeElapsedWithLoop onTimeElapse)
{
	std::thread* thread = new std::thread([timerRequiredMiliseconds, onTimeElapse]() {
		bool continueLoop = true;
		while (continueLoop)
		{
			ConsoleControl::Wait(timerRequiredMiliseconds);
			continueLoop = onTimeElapse();
		}

		});
	thread->detach();
}