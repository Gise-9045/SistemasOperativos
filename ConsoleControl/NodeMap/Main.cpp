#include "Vector2.h"
#include"Node.h"
#include"INodeContent.h"
#include <iostream>

class Tree : INodeContent
{
public:
	Tree();
	~Tree();

private:

};

Tree::Tree()
{
}

Tree::~Tree()
{
}

int main()
{

    Node* node = new Node(Vector2()); 

    INodeContent* iContent = node->GetContent(); 
	Tree* tree = node->GetContent<Tree>(); 

	Tree* tree2; 

	if (node->TryGetContent<Tree>(tree))
	{

	}
}
