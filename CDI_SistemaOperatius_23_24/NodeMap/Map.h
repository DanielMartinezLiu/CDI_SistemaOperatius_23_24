#pragma once

#include <vector>
#include <functional>

#include "Node.h"
#include "Vector2.h"

class Map
{
public:
	typedef std::vector<Node*> NodeColumn;
	typedef std::vector<NodeColumn*> NodeGrid;

	typedef std::function<void(Node* node)> SafePick;

private:
	Vector2 _size;
	Vector2 _offset = Vector2();

	NodeGrid* _grid = nullptr;
	std::mutex* _gridMutex = new std::mutex();

	Node* UnSafeGetnode(Vector2 position);

public:
	Map(Vector2 size, Vector2 offset = Vector2());

	void UnSafeDraw(Vector2 offset = Vector2());
	//void SafeDraw(Vector2 offset = Vector2());
	
	void SafePicknode(Vector2 position, SafePick safePickAction);
};
