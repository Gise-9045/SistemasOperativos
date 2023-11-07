#pragma once
#include<vector>
#include "Node.h"
#include "Vector2.h"
#include <functional>
#include <list>
class Map
{
public:
	typedef std::vector<Node*> NodeColumn; 
	typedef std::vector<NodeColumn*> NodeGrid;

	typedef std::function<void(Node* node)> SafePick;
	typedef std::function<void(std::list<Node*>* node)> SafeMultiPick;
private:
	Vector2 _size;
	Vector2 _offset = Vector2();

	std::mutex* _sizeMutex = new std::mutex();
	std::mutex* _gridMutex = new std::mutex();
	std::mutex* _offsetMutex = new std::mutex();
	std::mutex* _safeMultiPickMutex = new std::mutex();

	Node* UnSafeGetNode(Vector2 position);

	NodeGrid* _grid = nullptr;
public:
	Vector2 GetOffSet();
	Map(Vector2 size, Vector2 offset = Vector2());

	void UnSafeDraw(Vector2 offset = Vector2());

	void SafePickNode(Vector2 position, SafePick safePickAction);
	/// <summary>
	/// No puede recibir duplicados
	///
	/// </summary>
	
	void SafePickNodes(std::list<Vector2> position, SafeMultiPick safeMultiPickAction);
};

