#pragma once
#include <mutex>
#include <thread>
#include <functional>
#include <map>
#include <list>

class InputManager
{
    class KeyBinding
    {
    public:
        typedef std::function<void(int keyCode)> OnKeyPress;

        int keyCode;
        // No poner punteros en las funciones lamda, porque retienen memoria, y al usarla como punteros al pasarla a un sitio a otro para no ocasionar problemas.
        OnKeyPress onKeyPress; // Guardar la funcion lamda 

        KeyBinding(int keyCode, unsigned long milisecondsTriggerDelay, OnKeyPress onKeyPress);
        ~KeyBinding();
        unsigned int GetSubscriptionId();
        void TryTrigger();

    private:
        unsigned int _subscriptionId = 0;
    };

private:
    std::mutex* _isStartedMutex = new std::mutex();
    bool _isStarted = false;

    typedef std::map<int, std::list<KeyBinding*>*> KeyBindingMapList;
    
    std::mutex* _listenersMapMutex = new std::mutex();
    KeyBindingMapList* _listenersMap = new KeyBindingMapList();

    std::thread* _listenerThread;
    void ReadLoop();

public:
    InputManager();
    ~InputManager();

    void StartListener();
    void StopListener();
    
    void SaveListener(KeyBinding* keyBinding);

    unsigned int AddListener(int keyCode, unsigned long milisecondsTriggerDelay, KeyBinding::OnKeyPress onKeyPress);
    unsigned int AddListenerAsync(int keyCode, unsigned long milisecondsTriggerDelay, KeyBinding::OnKeyPress onKeyPress);
    void RemoveListener(unsigned int listenerId);
    void RemoveListenerAsync(unsigned int listenerId);
};