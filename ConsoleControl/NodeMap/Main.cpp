#include "Vector2.h"
#include"Node.h"
#include"INodeContent.h"
#include "ConsoleControl.h"
#include <iostream>
#include "Map.h"

class Tree : public INodeContent
{
public:
	Tree();
	~Tree();

	void Draw(Vector2 offset) override
	{
		Vector2 pos = offset; 
		ConsoleControl::LockMutex(); 
		ConsoleControl::SetPosition(pos.x, pos.y); 
		ConsoleControl::SetColor(ConsoleControl::GREEN); 
		std::cout << "A"; 
		ConsoleControl::SetColor(); 
		ConsoleControl::UnlockMutex(); 
	}

};

Tree::Tree()
{
}

Tree::~Tree()
{
}

class Coin : public INodeContent
{
public:
	Coin();
	~Coin();

	void Draw(Vector2 offset) override
	{
		Vector2 pos = offset;
		ConsoleControl::LockMutex();
		ConsoleControl::SetPosition(pos.x, pos.y);
		ConsoleControl::SetColor(ConsoleControl::YELLOW);
		std::cout << "C";
		ConsoleControl::SetColor();
		ConsoleControl::UnlockMutex();
	}

};

Coin::Coin()
{
}

Coin::~Coin()
{
}

int main()
{

    /*Node* node = new Node(Vector2()); 

    INodeContent* iContent = node->GetContent(); 
	Tree* tree = node->GetContent<Tree>(); 

	Tree* tree2; 

	if (node->TryGetContent<Tree>(tree))
	{

	}*/

	Map* map = new Map(Vector2(10, 10), Vector2(2, 2)); 

	map->SafePickNode(Vector2(3, 3), [](Node* node)
	{
		node->SetContent(new Tree()); 
	});
	
	map->SafePickNode(Vector2(4, 4), [](Node* node)
	{
		node->SetContent(new Tree()); 
	});
	
	map->SafePickNode(Vector2(7, 7), [](Node* node)
	{
		node->SetContent(new Coin()); 
	});

	map->UnSafeDraw(); 
}
