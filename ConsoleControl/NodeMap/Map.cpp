#include "Map.h"

Node* Map::UnSafeGetNode(Vector2 position)
{
	NodeColumn* column = (*_grid)[position.x];
	Node* node = (*column)[position.y];
	return node;
}

Vector2 Map::GetOffSet()
{
	_offsetMutex->lock();
	Vector2 offset = _offset;
	_offsetMutex->unlock();
	return Vector2();
}

Map::Map(Vector2 size, Vector2 offset)
{
	_size = size;
	_offset = offset;
	_grid = new NodeGrid();

	for (int x = 0; x < _size.x; x++)
	{
		NodeColumn* column = new NodeColumn();
		for (int y = 0; y < _size.y; y++)
		{
			column->push_back(new Node(Vector2(x, y)));
		}

		_grid->push_back(column);
	}
}

void Map::UnSafeDraw(Vector2 offset)
{
	Vector2 totalOffset = _offset + offset;
	for (NodeColumn* column : *_grid)
	{
		for (Node* node : *column)
		{
			node->DrawContent(totalOffset);
		}
	}
}

void Map::SafePickNode(Vector2 position, SafePick safePickAction)
{
	_sizeMutex->lock();
	Vector2 size = _size;
	_sizeMutex->unlock();

	if (position.x >= _size.x || position.y >= _size.y)
	{
		safePickAction(nullptr);
		return;
	}
	_gridMutex->lock();	
	Node* node = UnSafeGetNode(position);	
	_gridMutex->unlock();
	node->Lock();
	safePickAction(node);
	node->Unlock();
}

void Map::SafePickNodes(std::list<Vector2> position, SafeMultiPick safeMultiPickAction)
{
	std::list<Node*>* nodes = new std::list<Node*>();
	_sizeMutex->lock();
	Vector2 size = _size;
	_sizeMutex->unlock();

	for (Vector2 pos : position)
	{
		if (pos.x >= size.x || pos.y >= size.y || pos.x<0 || pos.y < 0)
		{
			nodes->push_back(nullptr);
			continue;
		}
		_gridMutex->lock();
		Node* node = UnSafeGetNode(pos);
		_gridMutex->unlock();
		nodes->push_back(node);
	}
	_safeMultiPickMutex->lock();
	for (Node* node : *nodes)
	{
		node->Lock();
	}
	_safeMultiPickMutex->unlock();

	safeMultiPickAction(nodes);

	for (Node* node : *nodes)
	{
		if(node != nullptr)
		node->Unlock();
	}
}



