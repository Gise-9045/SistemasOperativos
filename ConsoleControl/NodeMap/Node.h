#pragma once
#include"Vector2.h"
#include"INodeContent.h"
#include<mutex>

class Node
{
private:
	Vector2 _position; 
	INodeContent* _content = nullptr; 
	std::mutex* _classMutex = new std::mutex(); 

public: 

	Node(Vector2 position);
	INodeContent* GetContent(); 

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent,T>::value>::type>
	//se define SOLO SI cumple la condición de que tiene que estar basado en un INodeContent 
	T* GetContent()
	{
		T* contentCasted = dynamic_cast<T*>(_content); 
		return contentCasted; 
	}

	template<typename T, typename = typename std::enable_if<std::is_base_of<INodeContent, T>::value>::type>
	bool TryGetContent(T*& outContent) // dice que quiere el mismo puntero de memoria para cambiar el puntero no la info
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

