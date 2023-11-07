#pragma once
#include "Vector2.h"
#include "INodeContent.h"
#include <mutex>
class Node
{
private:
	Vector2 _position;
	INodeContent* _content = nullptr;
	std::mutex* _classMutex = new std::mutex();

public:
	Node(Vector2 position);
	INodeContent* GetContent();
	Vector2 GetPosition();

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	T* GetContent()
	{
		T* contentCasted = dynamic_cast<T*>(_content);
		return contentCasted;
	}

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	bool TryGetContent(T*& outContent)
	{
		T* contentCasted = dynamic_cast<T*>(_content);

		if (contentCasted != nullptr)
		{
			outContent = contentCasted;
			return true;
		}
		return false;
	}

	void SetContent(INodeContent* newContent);
	void DrawContent(Vector2 offset);

	void Lock();
	void Unlock();
};

