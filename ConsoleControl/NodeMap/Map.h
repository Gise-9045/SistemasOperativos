#pragma once
#include <vector>
#include "Node.h"
#include "Vector2.h" // para tener el size para el map
#include<mutex>
#include<functional>

class Map
{
public: 

	typedef std::vector<Node*> NodeColumn; 
	typedef std::vector<NodeColumn*> NodeGrid; 

	typedef std::function<void(Node* node)> SafePick; 

private:

	Vector2 _offset = Vector2(); 
	Vector2 _size; 
	NodeGrid* _grid = nullptr; 

	std::mutex* _gridMutex = new std::mutex(); 

	Node* UnSafeGetNode(Vector2 position); 

public:
	Map(Vector2 size , Vector2 offset = Vector2 ()); 
	void UnSafeDraw(Vector2 offset = Vector2());
	void SafePickNode(Vector2 position, SafePick safePickAction); 

};

