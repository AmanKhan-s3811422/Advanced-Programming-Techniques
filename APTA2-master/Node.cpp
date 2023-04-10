#include "Node.h"
#include <string>
#include <iostream>

Node::Node(Tile* tile, Node* next) {
	this->tile = tile;
	this->next = next;
}

Node::~Node() {
#ifdef debug
	std::cout << "Deleting node " << this << std::endl;
#endif
	if (tile != nullptr)
		delete (tile);
}