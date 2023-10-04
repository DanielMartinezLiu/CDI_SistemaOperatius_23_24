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

unsigned int InputManager::AddListener(int keyCode, KeyBinding::OnKeyPress onKeyPress)
{
    KeyBinding* binding = new KeyBinding(keyCode, onKeyPress);

    _listenersMapMutex->lock();

    KeyBindingMapList::iterator pair = _listenersMap->find(keyCode);
    std::list<KeyBinding*>* keyBindings = nullptr;

    if (pair == _listenersMap->end())
    {
        keyBindings = new std::list<KeyBinding*>();
        _listenersMap->emplace(keyCode, keyBindings);
    }
    else 
    {
        keyBindings = pair->second;
    }

    keyBindings->push_back(binding);

    _listenersMapMutex->unlock();
    
    return binding->GetSubscriptionId();
}

void InputManager::RemoveListener(unsigned int subscriptionId)
{
    _listenersMapMutex->lock();

    for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap) 
    {
        // Se hace asi en vez de llamarlo directamente para no sobrecargar el for con la funcion ".count", en este caso "pair.second"
        std::list<KeyBinding*>* keyBindings = pair.second;
        for (KeyBinding* binding : *keyBindings)
        {
            if (binding->GetSubscriptionId() == subscriptionId)
            {
                keyBindings->remove(binding);
                _listenersMapMutex->unlock();
                return;
            }
        }
    }

    _listenersMapMutex->unlock();
}

InputManager::KeyBinding::KeyBinding(int keyCode, OnKeyPress onKeyPress)
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
