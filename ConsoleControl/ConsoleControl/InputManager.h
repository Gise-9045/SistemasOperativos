#pragma once
#include<mutex>
#include<thread>

class InputManager
{
private:

	std::mutex* _isStartedMutex = new std::mutex(); 
	bool _isStarted = false; 

	std::thread* _listenerThread; 

	void RealLoop(); 

public:
	InputManager();
	~InputManager();

	void StartListener();
	void StopListener();
	unsigned int AddListener(int keycode /*, KeyBiding::OneKeyPress onKeyPress*/); 
	void RemovedListener(unsigned int listenerId); 
};


