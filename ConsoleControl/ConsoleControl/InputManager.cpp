
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

	_listenerThread = new std::thread(&InputManager::RealLoop, this); 
	_listenerThread->detach(); 
}

void InputManager::RealLoop()
{
	_isStartedMutex->lock();
	bool isStarted = _isStarted;
	_isStartedMutex->unlock();

	while (isStarted)
	{
		int keyCode = ConsoleControl::WaithForReadNextKey();

		_listenersMapMutex->lock(); 
		KeyBindingListMap::iterator pair = _listenersMap->find(keyCode);
		if (pair != _listenersMap->end())
		{
			std::list<KeyBinding*>* keyBindings = pair->second; 

			for (KeyBinding* keyBindings : *keyBindings)
			{
				keyBindings->onKeyPress(keyCode); 
			}
		}
		
		_listenersMapMutex->unlock(); 

		_isStartedMutex->lock();
		isStarted = _isStarted; 
		_isStartedMutex->unlock();
	}

}

void InputManager::SaveListener(KeyBinding* keybinding)
{
	_listenersMapMutex->lock();

	KeyBindingListMap::iterator pair = _listenersMap->find(keybinding->keyCode);
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

	// el lock y el unlock tiene que estar separados lo minimo necesario para que no se pare el juego/codigo mucho tiempo
}

unsigned int InputManager::AddListener(int keyCode , KeyBinding::OnKeyPress onKeyPress)
{
	KeyBinding* binding = new KeyBinding(keyCode, onKeyPress); 
	
	SaveListener(binding); 

	return binding->GetSubcriptionId();
}

unsigned int InputManager::AddListenerAsync(int keyCode, KeyBinding::OnKeyPress onKeyPress)
{
	KeyBinding* binding = new KeyBinding(keyCode, onKeyPress); 
	std::thread* safeListenerThread = new std::thread(&InputManager::SaveListener, this, binding); 
	return 0;
}

void InputManager::RemoveListener(unsigned int subscriptionId)
{
	_listenersMapMutex->lock(); 

	for (std::pair<int, std::list<KeyBinding*>*> pair : *_listenersMap)
	{
		std::list<KeyBinding*>* keyBindigns = pair.second;  // optimización na más
		
		for(KeyBinding* binding : *keyBindigns)
		{
			if (binding->GetSubcriptionId() == subscriptionId)
			{
				keyBindigns->remove(binding); 
				_listenersMapMutex->unlock();
				return; //Early Exit
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

// name space -> espacios para utilizar los nombres de cosas que sean propias de una libreria pero no queremos que detecte la funcion de las variables de esa libreria

InputManager::KeyBinding::KeyBinding(int keyCode, OnKeyPress onKeyPress)
{
	static std::mutex currentIdMutex;

	currentIdMutex.lock(); 
	static unsigned int currentId = 0;  // esta linea despues de la primera vez ya no funcionara más y se creara un espacio de memoria de currentId que se modificara siempre. 
	this->_subscriptionId = currentId; 
	currentId++; // en cada llamada se suma 1 al currentId ( 1,2,3,4...)
	currentIdMutex.unlock();

	this->keyCode = keyCode; 
	this->onKeyPress = onKeyPress; 

}

InputManager::KeyBinding::~KeyBinding()
{

}

unsigned int InputManager::KeyBinding::GetSubcriptionId()
{
	return _subscriptionId;
}

