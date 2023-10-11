#pragma once
#include <mutex>
#include <thread>
#include <functional>
#include <map>
#include <list>

class InputManager {
public:
	class KeyBinding {
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

	typedef std::map<int, std::list<KeyBinding*>*> KeyBindingListMap;
	std::mutex* _listenersMapMutex = new std::mutex();
	KeyBindingListMap* _listenersMap = new KeyBindingListMap();
	std::thread* _listenerThread;

	void ReadLoop();
	void SaveListener(KeyBinding* keyBinding);


public:
	InputManager();
	~InputManager();

	void StartListener();
	void StopListener();

	unsigned int AddListener(int keyCode, KeyBinding::OnKeyPress onKeyPress);
	void RemoveListener(unsigned int subscriptionId);
	unsigned int AddListenerAsync(int keyCode, unsigned long milisecondsTriggerDelay, KeyBinding::OnKeyPress onKeyPressed);
};
