#pragma once
#include <vector>
#include "Node.h"
#include "Vector2.h" // para tener el size para el map
#include<mutex>
#include<functional>
#include<list>

class Map
{
public: 

	typedef std::vector<Node*> NodeColumn; 
	typedef std::vector<NodeColumn*> NodeGrid; 
	
	typedef std::function<void(Node* node)> SafePick; 
	typedef std::function<void(std::list<Node*>* nodes)> SafeMultiPick ; 

private:

	Vector2 _offset = Vector2(); 
	std::mutex* _offsetMutex = new std::mutex; 
	
	Vector2 _size; 
	std::mutex* _sizeMutex = new std::mutex;

	NodeGrid* _grid = nullptr; 
	std::mutex* _gridMutex = new std::mutex();

	std::mutex* _safeMultiPickMutex = new std::mutex;

	Node* UnSafeGetNode(Vector2 position); 

public:

	Map(Vector2 size , Vector2 offset = Vector2 ()); 
	void UnSafeDraw(Vector2 offset = Vector2());
	void SafePickNode(Vector2 position, SafePick safePickAction); 

	/// <summary>
	/// This funciton can't be recived duplicated positions 
	/// </summary>

	void SafePickNodes(std::list<Vector2> positions, SafeMultiPick safeMultiPickAction); 

	Vector2 GetOffset(); 
};

