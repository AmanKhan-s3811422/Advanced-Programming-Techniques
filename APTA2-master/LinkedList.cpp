#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
	head = nullptr;
}

LinkedList::~LinkedList()
{
	//delete all nodes within the list
	if (head == nullptr) {
		return;
	}

	if (head == tail && head != nullptr) {
		delete head;
		return;
	}

	Node* currentNode = head;
	while (currentNode != nullptr) {
		Node* nextNode = currentNode->next;
		delete(currentNode);
		currentNode = nextNode;
	}
}

void LinkedList::addToBack (Node* ptrNode) {
	if (head == nullptr) {
		head = ptrNode;
		tail = head;
		head->next = tail;
		tail->next = nullptr;
	}
	else
	{
		Node* ptrCurrentNode = tail;
		ptrCurrentNode->next = ptrNode;
		tail = ptrNode;
		tail->next = nullptr;
	}

	numNodes++;
}

Node* LinkedList::removeFromFront() {
	Node* ptrTemp = nullptr;
	Node* curHead = nullptr;

	// If the linked list is empty
	if (head == nullptr) {
		ptrTemp = nullptr;
	}

	// If the linked list contains one element only
	else if (head == tail) {
		curHead = head;
		head = nullptr;
		tail = nullptr;
		numNodes--;
		ptrTemp = curHead;
	}

	// If there are multiple elements in the linked list
	else {
		numNodes--;
		curHead = head;
		head = head->next;
		ptrTemp = curHead;
	}

	return ptrTemp;
}


Node* LinkedList::replaceNode(std::string nodeToReplace, Node* ptrNodeReplacing) {
	Node* ptrReturn = nullptr;
	std::string code;

	// If the linked list is empty
	if (head == nullptr) {
		ptrReturn = nullptr;
	}

	// If there is one node in the linked list
	else if (head == tail) {
		code = head->tile->getTileCode();

		if (code.compare(nodeToReplace) == 0) {
			ptrReturn = head;
			head = ptrNodeReplacing;
			tail = head;
			head->next = nullptr;
		}
	}

	// If there are multiple elements in the linked list
	else {
		// Head is replaced
		code = head->tile->getTileCode();
		if (code.compare(nodeToReplace) == 0) {
			ptrReturn = head;
			head = ptrNodeReplacing;
			ptrNodeReplacing->next = head->next;
		}

		// Replace a given node
		else {
			Node* ptrCurrent = head;
			while (ptrCurrent->next != nullptr && ptrReturn == nullptr) {
				Node* ptrTemp = ptrCurrent->next;
				std::string code = ptrTemp->tile->getTileCode();
				if (code.compare(nodeToReplace) == 0) {
					if (ptrCurrent->next == tail) {
						tail = ptrNodeReplacing;
						tail->next = nullptr;
					}
					else {
						ptrCurrent->next = ptrNodeReplacing;
						ptrNodeReplacing->next = ptrTemp->next;
					}

					ptrReturn = ptrTemp;
				}

				ptrCurrent = ptrCurrent->next;
			}
		}
	}

	return ptrReturn;
}


Node* LinkedList::removeNode(std::string nodeToRemove) {
	Node* removedNode = nullptr;
	std::string code;

	//  If the list is empty
	if (head == nullptr) {
		removedNode = nullptr;
	}

	// If there is only one elemet in the list
	else if (head == tail) {
		code = head->tile->getTileCode();
		if (code.compare(nodeToRemove) == 0) {
			removedNode = head;
			head = nullptr;
			tail = nullptr;
			numNodes--;
		}
	}

	// If there are multiple nodes
	else {
		// Removing the head node
		code = head->tile->getTileCode();
		if (code.compare(nodeToRemove) == 0) {
			removedNode = head;
			head = head->next;
			numNodes--;
		}

		// A given node is removed (not the head node)
		else {
			Node* ptrCurrent = head;
			while (ptrCurrent->next != nullptr && removedNode == nullptr) {
				std::string code = ptrCurrent->next->tile->getTileCode();
				if (code.compare(nodeToRemove) == 0) {

					// Node to be removed is found in tail and removed
					Node* ptrRemovingNode = nullptr;
					if (ptrCurrent->next == tail) {
						ptrRemovingNode = tail;
						tail = ptrCurrent;
						tail->next = nullptr;
					}
					else {
						// Node to be removed is found in the middle of the list and removed
						ptrRemovingNode = ptrCurrent->next;
						ptrCurrent->next = ptrCurrent->next->next;
					}
					numNodes--;

					removedNode = ptrRemovingNode;
				}
				else {
					ptrCurrent = ptrCurrent->next;
				}
			}
		}
	}

	// The node removed is returned
	return removedNode;
}


bool LinkedList::containsTile(const std::string tileCode)
{
	bool retval = false;

	if (head == nullptr) {
		retval = false;
	}

	else if (head == tail) {
		std::string code = head->tile->getTileCode();
		if (code.compare(tileCode) == 0) {
			retval = true;
		}
		else {
			retval = false;
		}
	}

	// Search list for the nodes for a given tilecode
	else {
		Node* curNode = head;
		while (curNode != nullptr && retval == false) {
			std::string code = curNode->tile->getTileCode();
			curNode = curNode->next;

			if (code.compare(tileCode) == 0) {
				retval = true;
			}
		}
	}

	return retval;
}


Node* LinkedList::getNode(std::string tileCode)
{
	Node* returnNode = nullptr;

	if (head == nullptr) {
		returnNode = head;
	}

	else if (head == tail) {
		std::string code = head->tile->getTileCode();
		if (code.compare(tileCode) == 0) {
			returnNode = head;
		}
		else {
			returnNode = nullptr;
		}
	}

	// Search list for the nodes for a given tilecode
	else {
		Node* curNode = head;
		while (curNode != nullptr && returnNode == nullptr) {
			std::string code = curNode->tile->getTileCode();

			if (code.compare(tileCode) == 0) {
				returnNode = curNode;
			}
			else {
				curNode = curNode->next;
			}
		}
	}

	return returnNode;
}


std::string LinkedList::getOrderedList(bool shouldPrint)
{
	std::stringstream str;
	std::string retVal = "";

	std::string orderedList = "";
	Node* ptrCurrent = head;


	//traverse the list and builda string
	if (head == nullptr) {
		retVal = "";
	}

	else {
		while (ptrCurrent != nullptr) {
			orderedList += ptrCurrent->tile->getTileCode() + ",";
			ptrCurrent = ptrCurrent->next;
		}

		//remove the last comma of the string
		orderedList = orderedList.substr(0, orderedList.length() - 1);

		if (shouldPrint) {
			std::cout << orderedList << std::endl;
		}
	}

	return orderedList;
}

int LinkedList::getListSize() const {
	return numNodes;
}

