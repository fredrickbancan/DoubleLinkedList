#include "DoubleLinkedList.h"
#include <iostream>
#include <string>

DoubleLinkedList::DoubleLinkedList(int count/*= 0*/, int startValue/*= 0*/)
{
	head->next = tail;
	tail->prev = head;
	if (count < 1)
	{
		isEmpty = true;
		this->count = 0;
	}
	else
	{
		for (int i = 0; i < count; i++)//loop through the count, and fill list with nodes with startValue as their value
		{
			pushBack(startValue);
		}
	}
}

DoubleLinkedList::~DoubleLinkedList()
{
	//delete only head and tail nodes if empty or count is 1
	if (isEmpty || count == 1)
	{
		if (head != nullptr)
		{
			delete head;
		}
		if (tail != nullptr)
		{
			delete tail;
		}
		return;
	}
	//loop through each node and delete its previous ptr, and then delete the tail. if there is only 2 nodes, this will delete both.
	Node* itterator = head;
	for (int i = 0; i < count - 1; i++)
	{
	    itterator = itterator->next;

		if (itterator != tail)
		{
			delete itterator->prev;
		}
		else
		{
			delete itterator->prev;
			delete itterator;
		}
	}
}

bool DoubleLinkedList::find(int key, Node*& foundNode)
{
	if (isEmpty)
	{
		foundNode = nullptr;
		return false;
	}
	if (count == 1)
	{
		if (head->data == key)
		{
			foundNode = head;
			return true;
		}
		foundNode = nullptr;
		return false;
	}

	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		if (itterator->data == key)
		{
			foundNode = itterator;
			return true;
		}
		itterator = itterator->next;
	}

	foundNode = nullptr;
	return false;
}

void DoubleLinkedList::pushFront(int value)
{
	if (isEmpty)
	{
		head->data = value;
		tail->data = value;
		isEmpty = false;
		count++;
		return;
	}

	if (count == 1)
	{
		head->data = value;
		count++;
		return;
	}

	Node* newNode = new Node{nullptr, head, value };
	head->prev = newNode;
	head = newNode;
	count++;
}

bool DoubleLinkedList::insertAt(int key, int value, bool before)
{
	if (isEmpty)
	{
		before ? pushBack(value) : pushFront(value);
		return false;
	}

	if (count == 1)
	{
		int originalData = head->data;
		before ? pushBack(value) : pushFront(value);
		return originalData == key;
	}
	Node* newNode = new Node{ nullptr, nullptr, value };
	//loop through all nodes and check if their data matches key, if so, insert new node with value before/after.
	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		//if there is a match, insert and return.
		if (itterator->data == key)
		{
			if (before)
			{
				if (itterator == head)
				{
					head->prev = newNode;
					head = newNode;
				}
				else
				{
					itterator->prev->next = newNode;
					itterator->prev = newNode;
				}
			}
			else//if before is false, meaning insert after
			{
				if (itterator == tail)
				{
					tail->next = newNode;
					tail = newNode;
				}
				else
				{
					itterator->next->prev = newNode;
					itterator->next = newNode;
				}
			}
			count++;
			return true;
		}
		itterator = itterator->next;
	}

	before ? pushBack(value) : pushFront(value);
	return false;
}

void DoubleLinkedList::pushBack(int value)
{
	if (isEmpty)
	{
		head->data = value;
		tail->data = value;
		isEmpty = false;
		count++;
		return;
	}

	if (count == 1)
	{
		tail->data = value;
		count++;
		return;
	}

	Node* newNode = new Node{tail, nullptr, value};
	tail->next = newNode;
	tail = newNode;
	count++;
}

void DoubleLinkedList::printList() const
{
	std::cout << "List count: " + std::to_string(count) << std::endl;

	if (isEmpty || head == nullptr)
	{
		return;
	}

	Node* itterator = head;
	for (int i = 0; i < count; i++)//TODO: doesnt work, index out of bounds
	{
		std::cout << "Node value: " + std::to_string(itterator->data) << std::endl;
		itterator = itterator->next;
	}
}
