#pragma once
#include <mutex>
#include <thread>

class InputManager
{
    // Las variables privadas poner una barra baja "_" al principio de la nomenclatura
private:
    std::mutex* _isStartedMutex = new std::mutex();
    bool _isStarted = false;

    std::thread* _listenerThread;
    void ReadLoop();

public:
    InputManager();
    ~InputManager(); // Destructor

    void StartListener();
    void StopListener();

    unsigned int AddListener(int keyCode);
    void RemoveListener(unsigned int listenerId);
}