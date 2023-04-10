#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

#include <string>
#include <memory>

#define debug 1

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	int numNodes = 0;

	/**
	* Add a node at the back of the list
	*/
	void addToBack(Node* ptrNode);


	/**
	* Remove a node from the front of the list
	*/
	Node* removeFromFront();


	/**
	* Get the node of a given tilecode
	*/
	Node* getNode(std::string tileCode);


	/**
	* Replace node in the linked list with another node
	*/
	Node* replaceNode(std::string nodeToReplace, Node* ptrNodeReplacing);


	/**
	* Remove a node (tile) from the linked list
	* Returns the node (tile)
	*/
	Node* removeNode(std::string nodeToRemove);


	/**
	* Returns true if the tile exists in the linked list
	*/
	bool containsTile(const std::string tileCode);


	/**
	* Returns all elements in the linked list as a comma seperated string
	* If shouldPrint == true, elements are printed
	*/
	std::string getOrderedList(bool shouldPrint);


	/**
	* Returns the number of nodes in the linked list
	*/
	int getListSize() const;


private:
	Node* head;
	Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H