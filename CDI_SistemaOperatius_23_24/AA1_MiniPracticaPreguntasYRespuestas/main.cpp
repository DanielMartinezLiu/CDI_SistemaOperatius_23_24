#include "InputManager.h"
#include "ConsoleControl.h"
#include "Timer.h"
#include "QuestionManager.h"

int main()
{
	// Lambda Function [variables que captura](parametros){Cuerpo de la funcion}
	Timer::StartTimer(7000, []() {
		std::cout << "7s" << std::endl;
		});
	Timer::StartTimer(9000, []() {
		std::cout << "9s" << std::endl;
		});

	while (true)
	{

	}
}