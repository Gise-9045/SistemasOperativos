#include "Vector2.h"
#include"Node.h"
#include"INodeContent.h"
#include "ConsoleControl.h"
#include <iostream>
#include "Map.h"

class Tree : public INodeContent
{
private : 
	bool onFire = false; 
public:
	Tree();
	~Tree();

	void Draw(Vector2 offset) override
	{
		Vector2 pos = offset; 
		ConsoleControl::LockMutex(); 
		ConsoleControl::SetPosition(pos.x, pos.y); 
		ConsoleControl::SetColor(onFire ? ConsoleControl::RED : ConsoleControl::GREEN); 
		std::cout << "A"; 
		ConsoleControl::SetColor(); 
		ConsoleControl::UnlockMutex(); 
	}

	void PrenderEnLlamas()
	{
		onFire = !onFire; 
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

	/*map->SafePickNode(Vector2(3, 3), [](Node* node)
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

	map->UnSafeDraw();*/ 

	std::list<Vector2> treePositions = std::list<Vector2>();
	treePositions.push_back(Vector2(2, 2));
	treePositions.push_back(Vector2(3, 3));
	treePositions.push_back(Vector2(4, 4));
	treePositions.push_back(Vector2(5, 5));

	map->SafePickNodes(treePositions, [map](std::list<Node*>* nodes) {
		for (Node* node : *nodes)
		{
			if (node != nullptr)
			{
				node->SetContent(new Tree());
				node->DrawContent(map->GetOffset());
			}
		}
		});


	std::list<Vector2> fuegoPositions = std::list<Vector2>(); 
	//fuegoPositions.push_back(Vector2(2, 2));
	fuegoPositions.push_back(Vector2(3, 3));
	fuegoPositions.push_back(Vector2(4, 4));
	//fuegoPositions.push_back(Vector2(5, 5));

	map->SafePickNodes(fuegoPositions, [map](std::list<Node*>* nodes) {
		for (Node* node : *nodes)
		{
			Tree* tree = nullptr; 
			if (node != nullptr && node->TryGetContent<Tree>(tree))
			{
				tree->PrenderEnLlamas(); 
				node->DrawContent(map->GetOffset());
			}
		}
	});
	
	while (true)
	{

	}
}
