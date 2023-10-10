#pragma once
#include<mutex>
#include<thread>
#include<functional>
#include<map>
#include<list>

class InputManager
{

public:
	class KeyBinding 
	{
	public:

		typedef std::function<void(int keyCode)> OnKeyPress; 

		
		int keyCode; 
		OnKeyPress onKeyPress;

		KeyBinding(int keyCode, OnKeyPress onKeyPress);
		~KeyBinding(); 
		unsigned int GetSubcriptionId(); 
	private: 
	
		unsigned int _subscriptionId = 0;
	}; 


private:

	std::mutex* _isStartedMutex = new std::mutex(); 
	bool _isStarted = false; 

	typedef std::map<int, std::list<KeyBinding*>*> KeyBindingListMap; 

	std::mutex* _listenersMapMutex =  new std::mutex(); 
	KeyBindingListMap* _listenersMap = new KeyBindingListMap();

	std::thread* _listenerThread; 

	void RealLoop(); 
	void SaveListener(KeyBinding* keybinding);

public:
	InputManager();
	~InputManager(); // destruir todo el mapa 

	void StartListener();
	void StopListener();
	unsigned int AddListener(int keyCode , KeyBinding::OnKeyPress onKeyPress); 
	unsigned int AddListenerAsync(int keyCode, KeyBinding::OnKeyPress onKeyPress); 
	void RemoveListener(unsigned int subscriptionId);
	void RemoveListenerAsync(unsigned int subscriptionId);
};


