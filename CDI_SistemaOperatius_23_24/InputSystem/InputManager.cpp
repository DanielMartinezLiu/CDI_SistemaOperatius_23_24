#include "InputManager.h"
#include "ConsoleControl.h"

InputManager::InputManager()
{

}

InputManager::InputManager()
{

}

// El lock y el unlock tiene que estar separado lo minimo necesario. Para que el codigo se pare la menor cantidad de tiempo posible
void InputManager::StartListener()
{
    _isStartedMutex->lock();

    if (_isStarted)
    {
        _isStartedMutex->unlock();
        return;
    }

    _isStarted = true;

    _isStartedMutex->unlock();

    _listenerThread = new std::thread(&ReadLoop, this);
    _listenerThread->detach();
}

void InputManager::ReadLoop()
{
    _isStartedMutex->lock();
    bool isStarted = true;
    _isStartedMutex->unlock();

    while (isStarted)
    {
        int keyCode = ConsoleControl::WaitForReadNextKey();

        // Search in the Keybinding Map, if the pressed keycode exsists.
        // If exsists, call all lamda functions

        _isStartedMutex->lock();
        isStarted = _isStarted;
        _isStartedMutex->unlock();
    }
}

void InputManager::StopListener()
{
    _isStartedMutex->lock();
    _isStarted = false;
    _isStartedMutex->unlock();
}