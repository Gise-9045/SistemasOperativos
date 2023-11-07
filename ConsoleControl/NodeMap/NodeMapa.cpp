// NodeMapa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Vector2.h"
#include "Node.h"
#include "INodeContent.h"
#include "ConsoleControl.h"
#include "Map.h"

class Tree : public INodeContent
{
private:
    bool OnFire = false;
public:
    Tree(){}
    ~Tree(){}
    void Draw(Vector2 offset) override
    {
        Vector2 pos = offset;
        ConsoleControl::LockMutex();
        ConsoleControl::SetPosition(pos.x, pos.y);
        ConsoleControl::SetColor(OnFire ? ConsoleControl::RED : ConsoleControl::GREEN);
        std::cout << "#";
        ConsoleControl::SetColor();
        ConsoleControl::UnlockMutex();
    }

    void MePrendo()
    {
        OnFire = true;
    }
};


class Coin : public INodeContent
{
public:
    Coin(){}
    ~Coin(){}
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


int main()
{
    std::cout << "Hello World!\n";
    
    Map* map = new Map(Vector2(10, 10), Vector2(2, 2));
   /* map->SafePickNode(Vector2(3, 3), [](Node* node) {
        node->SetContent(new Tree());

     });

    map->SafePickNode(Vector2(4, 4), [](Node* node) {
        node->SetContent(new Coin());

        });
    map->UnSafeDraw();*/

    std::list<Vector2> treesPositions = std::list<Vector2>();

    for (int y = 2; y < 10; y++)
    {
        for (int x = 2; x < 10; x++)
        {
            if (x == 2 || y == 2 || x == 9 || y == 9 )
            {
                
                treesPositions.push_back(Vector2(y, x));
            }
            
        }
    }

    map->SafePickNodes(treesPositions, [map](std::list<Node*>* nodes) {
        for (Node* node : *nodes)
        {
            Tree* tree = nullptr;
            if (node != nullptr )
            {
                node->SetContent(new Tree());
                node->DrawContent(map->GetOffSet());
            }
        }

    });

    while (true)
    {

    }
}
