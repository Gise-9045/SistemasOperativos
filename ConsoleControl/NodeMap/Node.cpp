#include "Node.h"
#include "ConsoleControl.h"

Node::Node(Vector2 position)
{
	this->_position = position; 
}

INodeContent* Node::GetContent()
{
	return _content;
}
void Node::SetContent(INodeContent* newContent)
{
	_content = newContent; 
}

void Node::DrawContent(Vector2 offset)
{
	if(_content == nullptr)
	{
		Vector2 pos = offset + _position; 
		ConsoleControl::LockMutex(); 
		ConsoleControl::SetPosition(pos.x, pos.y); 
		std::cout << " "; 
		ConsoleControl::UnlockMutex(); 
		return; 
	}

	_content->Draw(offset); 
}

void Node::Lock()
{
	_classMutex->lock(); 
}

void Node::Unlock()
{
	_classMutex->unlock(); 
}
