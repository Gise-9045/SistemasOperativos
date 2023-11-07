#pragma once
#include <mutex>
#include <thread>
#include <functional>
#include <map>
#include <list>


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
		unsigned int GetSubscriptionId();
	private:
		unsigned int _subscriptionId = 0;
	};
private:
	std::mutex* _isStartedMutex = new std::mutex();
	bool _isStarted = false;

	typedef  std::map<int, std::list<KeyBinding*>*> keyBindingListsMap;


	std::mutex* _listenersMapMutex = new std::mutex();
	
	keyBindingListsMap* _listenersMap = new keyBindingListsMap();

	std::thread* _listenerThread;
	void ReadLoop();
	void SaveListener(KeyBinding* keyBinding);


public:
	InputManager();
	~InputManager();

	void StartListener();
	void StopListener();
	unsigned int AddListenerAsync(int keycode, KeyBinding::OnKeyPress onKeyPress);
	unsigned int AddListener(int keyCode, KeyBinding::OnKeyPress onKeyPress);
	void RemoveListener(unsigned int listenerId);
	void RemoveListenerAsync(unsigned int listenerId);
};

