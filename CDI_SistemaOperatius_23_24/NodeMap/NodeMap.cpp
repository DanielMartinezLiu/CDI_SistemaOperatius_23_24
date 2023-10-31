#include <iostream>
#include "Node.h"
#include "ConsoleControl.h"
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
	Map* map = new Map(Vector2(10, 10), Vector2(2, 2));

	map->SafePicknode(Vector2(3, 3), [](Node* node) {
		
		node->SetContent(new Tree());
		
		});

	map->SafePicknode(Vector2(7, 8), [](Node* node) {

		node->SetContent(new Tree());

		});

	map->SafePicknode(Vector2(5, 4), [](Node* node) {

		node->SetContent(new Coin());

		});

	map->UnSafeDraw();

	map->SafePicknode(Vector2(1, 7), [](Node* node) {

		node->SetContent(new Coin());
		node->DrawContent(node->GetPosition());

		});
}