#include "InputManager.h"
#include "ConsoleControl.h"


void InputManager::ReadLoop()
{
	_isStartedMutex->lock();
	bool isStarted = _isStarted;
	_isStartedMutex->unlock();


	while (isStarted) {
		int keyCode = ConsoleControl::WaithForReadNextKey();
		_listenersMapMutex->lock();
		KeyBindingListMap::iterator pair = _listenersMap->find(keyCode);
		if (pair != _listenersMap->end()) {
			std::list<KeyBinding*>* keyBindings = pair->second;
			for (KeyBinding* keyBinding : *keyBindings) {
				keyBinding->onKeyPress(keyCode);
			}
		}
		_listenersMapMutex->unlock();
		_isStartedMutex->lock();
		isStarted = _isStarted;
		_isStartedMutex->unlock();
	}
}

void InputManager::SaveListener(KeyBinding* keyBinding)
{
	_listenersMapMutex->lock();

	KeyBindingListMap::iterator pair = _listenersMap->find(keyBinding->keyCode);
	std::list<KeyBinding*>* keyBindings = nullptr;

	if (pair == _listenersMap->end()) {
		keyBindings = new std::list<KeyBinding*>();
		_listenersMap->emplace(keyBinding, keyBindings);
	}
	else {
		keyBindings = pair->second;
	}

	keyBindings->push_back(keyBinding);
	_listenersMapMutex->unlock();
}

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
}

void InputManager::StartListener()
{
	_isStartedMutex->lock();
	if (_isStarted) {
		_isStartedMutex->unlock();
		return;
	}

	_isStarted = true;
	_isStartedMutex->unlock();

	_listenerThread = new std::thread(&InputManager::ReadLoop, this);
	_listenerThread->detach();
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

	KeyBindingListMap::iterator pair = _listenersMap->find(keyCode);
	std::list<KeyBinding*>* keyBindings = nullptr;

	if (pair == _listenersMap->end()) {
		keyBindings = new std::list<KeyBinding*>();
		_listenersMap->emplace(keyCode, keyBindings);
	}
	else {
		keyBindings = pair->second;
	}

	keyBindings->push_back(binding);
	_listenersMapMutex->unlock();
	return binding->GetSubscriptionId();
}

void InputManager::RemoveListener(unsigned int subscriptionId)
{
	_listenersMapMutex->lock();
	for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap) {
		std::list<KeyBinding*>* keyBindings = pair.second;
		for (KeyBinding* binding : *keyBindings) {
			if (binding->GetSubscriptionId() == subscriptionId) {
				keyBindings->remove(binding);
				_listenersMapMutex->unlock();
				return;
			}
		}
	}
	_listenersMapMutex->unlock();
}

unsigned int InputManager::AddListenerAsync(int keyCode, unsigned long milisecondsTriggerDelay, KeyBinding::OnKeyPress onKeyPressed)
{
	KeyBinding* binding = new KeyBinding(keyCode, milisecondsTriggerDelay, onKeyPressed);

	std::thread* safeListenerThread = new std::thread(&InputManager::)
}



InputManager::KeyBinding::KeyBinding(int keyCode, OnKeyPress onKeyPress)
{
	static std::mutex currentIdMutex;
	currentIdMutex.lock();
	static unsigned int currentId = 0;
	// Al ser static, se mantiene entre funciones el currentId, haciendo que cada vez sea 1 mas.
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

