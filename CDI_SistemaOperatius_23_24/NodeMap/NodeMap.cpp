#include <iostream>
#include "Node.h"


class Tree : INodeContent
{
public:
	Tree();
	~Tree();

private:
	void Draw(Vector2 offset) override
	{

	}
};

Tree::Tree()
{

}

Tree::~Tree()
{

}

int main()
{
	std::cout << "Hello World!\n" << std::endl;

	Node* node = new Node(Vector2());

	INodeContent* iContent = node->GetContent();
	Tree* tree = node->GetContent<Tree>();

	Tree* tree2;

	if (node->TryGetContent<Tree>(tree))
	{
				
	}
}