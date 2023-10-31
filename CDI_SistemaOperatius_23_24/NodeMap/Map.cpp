#include "Map.h"

Map::Map(Vector2 size, Vector2 offset)
{
	_size = size;
	_offset = offset;
	_grid = new NodeGrid();

	for (int x = 0; x < _size.x; x++) 
	{
		NodeColumn* column = new NodeColumn();
		for(int y = 0; y < _size.y; y++)
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

/// Este metodo es ineficiente para el trabajo que vamos a hacer, ya que no
/// vamos a llegar a acceder al mapa completo, y como solo accederemos en el
/// momento de crear el mapa, nos es mas ineficiente
/*
void Map::SafeDraw(Vector2 offset)
{
	Vector2 totalOffset = _offset + offset;

	_gridMutex->lock();

	for (NodeColumn* column : *_grid)
	{
		for (Node* node : *column)
		{
			node->Lock();
			node->DrawContent(totalOffset);
			node->Unlock();
		}
	}

	_gridMutex->unlock();
}
*/

Node* Map::UnSafeGetnode(Vector2 position)
{
	NodeColumn* column = (*_grid)[position.x];
	Node* node = (*column)[position.y];
	return node;

	//return (*(*_grid)[position.x])[position.y];
}

void Map::SafePicknode(Vector2 position, SafePick safePickAction)
{
	if (position.x >= _size.x || position.y >= _size.y)
	{
		safePickAction(nullptr);
		return;
	}

	_gridMutex->lock();
	Node* node =  UnSafeGetnode(position);
	_gridMutex->unlock();

	node->Lock();
	safePickAction(node);
	node->Unlock();
}