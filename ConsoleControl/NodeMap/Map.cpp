#include "Map.h"

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

void Map::UnSafeDraw(Vector2 offset) // No es segura porque falta mutex
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

Node* Map::UnSafeGetNode(Vector2 position) //ENCAPSULAR CODIGO
{

	NodeColumn* column = (*_grid)[position.x];
	Node* node = (*column)[position.y];
	return node; 

	////ESTA FUNCION NO ES OPTIMA 

	// ESTO SI // return (*(*_grid)[position.x])[position.y]; 
}
