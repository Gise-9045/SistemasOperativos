
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

	_listenerThread = new std::thread(&RealLoop, this); 
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

		//Search in KeyBindings Map, if pressed key code exist; 
		//If exist,call all lamda functions ( funcion si nombre )

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

	// el lock y el unlock tiene que estar separados lo minimo necesario para que no se pare el juego/codigo mucho tiempo
}





