#pragma once
#include <mutex>
#include <functional>
#include <map>
#include <list>
class InputManager
{
public:
	class KeyBinding {
	public:
		typedef std::function<void(int keyCode)> OnKeyPress;
		//^funcion lambda, algo que actua como funcion sin nombre, 
		// entre <> el tipo de funcion y entre () los parametros
		//^con typedef la funcion lamda de este tipo se llamara OnKeyPress 
		// y escribiendo OnKeyPress es como si escribieramos lo de std::function....


		int keyCode;
		OnKeyPress onKeyPress;

		KeyBinding(int keyCode, std::function<void(int keyCode)> onKeyPress);
		~KeyBinding();
		unsigned int GetSubscriptionId();
	private:
		unsigned int subscriptionId = 0;
	};

private:
	std::mutex* _isStartedMutex = new std::mutex();
	typedef std::map<int, std::list<KeyBinding*>*> KeyBindingListsMap;
	KeyBindingListsMap* _listenersMap = new KeyBindingListsMap();
	std::mutex* _listenersMapMutex = new std::mutex();
	bool _isStarted = false;
	std::thread* _listenerThread;
	void ReadLoop();
	void SaveListener(KeyBinding* keybinding);
public:
	InputManager();
	~InputManager();
	void StartListener();
	void StopListener();
	unsigned int AddListener(int keyCode, KeyBinding::OnKeyPress);
	unsigned int AddListenerAsync(int keyCode, unsigned long miliseconsTriggerDelay, KeyBinding::OnKeyPress onKeyPress);
	void RemoveListener(unsigned int subscriptionId);
	void RemoveListenerAsync(unsigned int subscriptionId);

};

