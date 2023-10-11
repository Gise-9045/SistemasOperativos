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
	if (_isStarted) {
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
	while (_isStarted)
	{
		int keyCode = ConsoleControl::WaithForReadNextKey();
		//^Search in KeyBindings Map if pressed keycode exists
		//if it does, call all lamda functions (functions with no name)
		_listenersMapMutex->lock();
		KeyBindingListsMap::iterator pair = _listenersMap->find(keyCode);
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
void InputManager::RemoveListener(unsigned int subscriptionId)
{
	_listenersMapMutex->lock();

	for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap)
	{
		std::list<KeyBinding*>* keyBindigns = pair.second;  // optimización na más

		for (KeyBinding* binding : *keyBindigns)
		{
			if (binding->GetSubscriptionId() == subscriptionId)
			{
				keyBindigns->remove(binding);
				_listenersMapMutex->unlock();
				return; //Early Exit
			}
		}
	}
	_listenersMapMutex->unlock();

}

// name space -> espacios para utilizar los nombres de cosas que sean propias de una libreria pero no queremos que detecte la funcion de las variables de esa libreria
void InputManager::RemoveListenerAsync(unsigned int subscriptionId)
{
	std::thread* safeListenerThread = new std::thread(&InputManager::RemoveListener, this, subscriptionId);

	safeListenerThread->detach();
}
void InputManager::SaveListener(KeyBinding* keybinding)
{
	_listenersMapMutex->lock();

	KeyBindingListsMap::iterator pair = _listenersMap->find(keybinding->keyCode);
	std::list<KeyBinding*>* keyBindings = nullptr;


	if (pair == _listenersMap->end()) // si lo busca y no lo encuentra
	{
		keyBindings = new std::list<KeyBinding*>();
		_listenersMap->emplace(keybinding->keyCode, keyBindings); // .insert(make_pair(keyCode, keyBindings)); 
	}
	else
	{
		keyBindings = pair->second; //valor de la derecha del mapa 
	}

	keyBindings->push_back(keybinding);

	_listenersMapMutex->unlock();
}
void InputManager::StopListener()
{
	_isStartedMutex->lock();
	_isStarted = false;
	_isStartedMutex->unlock();
	//lock y unlock deben estar separados lo minimo necesario 
// para que no se pare el codigo del juego MUCHO RATO
}
unsigned int InputManager::AddListener(int keyCode, KeyBinding::OnKeyPress onKeyPress)
{
	KeyBinding* binding = new KeyBinding(keyCode, onKeyPress);
	_listenersMapMutex->lock();



	_listenersMapMutex->unlock();
	return binding->GetSubscriptionId();
}
unsigned int InputManager::AddListenerAsync(int keyCode, unsigned long miliseconsTriggerDelay, KeyBinding::OnKeyPress onKeyPress) {
	KeyBinding* binding = new KeyBinding(keyCode, onKeyPress);
	std::thread* safeListenerThread = new std::thread(&InputManager::SaveListener, this, binding);
	return 0;
}



InputManager::KeyBinding::KeyBinding(int keyCode, OnKeyPress onKeyPress)
{
	static std::mutex currentIdMutex;
	currentIdMutex.lock();
	static unsigned int currentId = 0;
	//^gracias a static currentId sera asignado a 0 la primera vez, 
	// la siguiente vez que llame al constructor currentId 
	// no se le asignara el valor 0 sino el que le quedo la ultima vez que se la llamo
	subscriptionId = currentId;
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
	return subscriptionId;
}
