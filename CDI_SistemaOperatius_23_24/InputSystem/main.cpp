#include <iostream>
#include "ConsoleControl.h"
#include "InputManager.h"


int main()
{
	std::cout << "Hello world" << std::endl;

	int keyCode = ConsoleControl::WaitForReadNextKey();
	std::cout << "The keycode is: " << keyCode;

	InputManager* iManager = new InputManager();

	//Aqui añado cosas
	iManager->StartListener();

	while (true)
	{

	}
}