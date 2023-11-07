#include "InputManager.h"
#include "ConsoleControl.h"


InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

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
	bool isStarted = _isStarted;
	_isStartedMutex->unlock();
	while (isStarted)
	{
		int keyCode = ConsoleControl::WaithForReadNextKey();

		_isStartedMutex->lock();
		keyBindingListsMap::iterator pair = _listenersMap->find(keyCode);

		if (pair != _listenersMap->end())
		{
			std::list<KeyBinding*>* keyBindings = pair->second;
			for (KeyBinding* keyBinding : *keyBindings)
			{
				keyBinding->onKeyPress(keyCode);
			}
		}
		_isStartedMutex->unlock();

		_isStartedMutex->lock();
		isStarted = _isStarted; // Se protege para que no crashe si hay otro thread tratando de tocarla
		_isStartedMutex->unlock();
	}
}

void InputManager::SaveListener(KeyBinding* keyBinding)
{
	_listenersMapMutex->lock();

	keyBindingListsMap::iterator pair = _listenersMap->find(keyBinding->keyCode);
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

void InputManager::StopListener()
{
	_isStartedMutex->lock(); // el lock y el unlock tienen que estar separados lo minimo necesario
	_isStarted = false;
	_isStartedMutex->unlock();
}

unsigned int InputManager::AddListenerAsync(int keycode, KeyBinding::OnKeyPress onKeyPress)
{
	KeyBinding* binding = new KeyBinding(keycode, onKeyPress);
	std::thread* safeListenerThread = new std::thread(&InputManager::SaveListener, this, binding);

	safeListenerThread->detach();

	return binding->GetSubscriptionId();
}

unsigned int InputManager:: AddListener(int keyCode, KeyBinding::OnKeyPress onKeyPress)
{
	KeyBinding* binding = new KeyBinding(keyCode, onKeyPress);
	SaveListener(binding);
	return binding->GetSubscriptionId();
}

void InputManager::RemoveListener(unsigned int listenerId)
{
	_listenersMapMutex->lock();
	for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap)
	{
		std::list<KeyBinding*>* keyBindings = pair.second;
		for (KeyBinding* binding : *keyBindings)
		{
			if (binding->GetSubscriptionId() == listenerId)
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

void InputManager::RemoveListenerAsync(unsigned int listenerId)
{
	std::thread* safeListenerThread = new std::thread(&InputManager::RemoveListener, this, listenerId);
	safeListenerThread->detach();
}

InputManager::KeyBinding::KeyBinding(int keyCode,OnKeyPress onKeyPress)
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
