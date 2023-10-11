#include "InputManager.h"
#include "ConsoleControl.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
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

    _listenerThread = new std::thread(&InputManager::ReadLoop, this);
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

        _listenersMapMutex->lock();

        KeyBindingMapList::iterator pair = _listenersMap->find(keyCode);
        if (pair != _listenersMap->end())
        {
            std::list<KeyBinding*>* keyBindings = pair->second;
            
            for (KeyBinding* keyBinding : *keyBindings)
            {
                keyBinding->onKeyPress(keyCode);
            }
        }

        _listenersMapMutex->unlock();

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

void InputManager::SaveListener(KeyBinding* keyBinding)
{
    _listenersMapMutex->lock();

    KeyBindingMapList::iterator pair = _listenersMap->find(keyBinding->keyCode);
    std::list<KeyBinding*>* keyBindings = nullptr;

    if (pair == _listenersMap->end())
    {
        keyBindings = new std::list<KeyBinding*>();
        _listenersMap->emplace(keyBinding->keyCode, keyBindings);
    }
    else
    {
        keyBindings = pair->second;
    }

    keyBindings->push_back(keyBinding);

    _listenersMapMutex->unlock();
}

unsigned int InputManager::AddListener(int keyCode, unsigned long milisecondsTriggerDelay,KeyBinding::OnKeyPress onKeyPress)
{
    KeyBinding* keyBinding = new KeyBinding(keyCode, milisecondsTriggerDelay, onKeyPress);

    SaveListener(keyBinding);
    
    return keyBinding->GetSubscriptionId();
}

unsigned int InputManager::AddListenerAsync(int keyCode, unsigned long milisecondsTriggerDelay,KeyBinding::OnKeyPress onKeyPress)
{
    KeyBinding* binding = new KeyBinding(keyCode, milisecondsTriggerDelay, onKeyPress);

    std::thread* safeListenerThread = new std::thread(&InputManager::SaveListener, this, binding);

    safeListenerThread->detach();

    return binding->GetSubscriptionId();
}

void InputManager::RemoveListener(unsigned int subscriptionId)
{
    _listenersMapMutex->lock();

    for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap) 
    {
        std::list<KeyBinding*>* keyBindings = pair.second;
        for (KeyBinding* binding : *keyBindings)
        {
            if (binding->GetSubscriptionId() == subscriptionId)
            {
                keyBindings->remove(binding);
                _listenersMapMutex->unlock();
                delete(binding);
                return;
            }
        }
    }

    _listenersMapMutex->unlock();
}

void InputManager::RemoveListenerAsync(unsigned int subscriptionId)
{
    std::thread* safeListenerThread = new std::thread(&InputManager::RemoveListener, this, subscriptionId);

    safeListenerThread->detach();
}


InputManager::KeyBinding::KeyBinding(int keyCode, unsigned long milisecondsTriggerDelay, OnKeyPress onKeyPress)
{
    static std::mutex currentIdMutex;
    currentIdMutex.lock();
    static unsigned int currentId = 0;

    _subscriptionId = currentId;
    currentId++;
    currentIdMutex.unlock();

    this->keyCode = keyCode;
    this->onKeyPress = onKeyPress;
}

InputManager::KeyBinding::~KeyBinding()
{

}

unsigned int InputManager::KeyBinding::GetSubscriptionId()
{
    return _subscriptionId;
}
