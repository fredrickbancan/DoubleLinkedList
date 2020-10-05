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

void DoubleLinkedList::swapValues(Node* a, Node* b)
{
	int tempValue = a->data;
	a->data = b->data;
	b->data = tempValue;
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
		before ? pushFront(value) : pushBack(value);
		return false;
	}

	if (count == 1)
	{
		int originalData = head->data;
		before ? pushFront(value) : pushBack(value);
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
					newNode->next = head;
					head = newNode;
				}
				else
				{
					itterator->prev->next = newNode;
					newNode->prev = itterator->prev;
					newNode->next = itterator;
					itterator->prev = newNode;
				}
			}
			else//if before is false, meaning insert after
			{
				if (itterator == tail)
				{
					tail->next = newNode;
					newNode->prev = tail;
					tail = newNode;
				}
				else
				{
					itterator->next->prev = newNode;
					newNode->next = itterator->next;
					newNode->prev = itterator;
					itterator->next = newNode;
				}
			}
			count++;
			return true;
		}
		itterator = itterator->next;//itterate if not found
	}

	before ? pushFront(value) : pushBack(value);//default to pushing front or back depending on before flag
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

int DoubleLinkedList::popFront()
{
	if (isEmpty)
	{
		return -1;
	}

	int result = head->data;

	if (count == 1)
	{
		count = 0;
		head->next = tail;
		tail->prev = head;
		isEmpty = true;
		return result;
	}

	if (count == 2)
	{
		count = 1;
		head->data = tail->data;
		return result;
	}
	Node* newHead = head->next;
	head->next->prev = nullptr;
	delete head;
	head = newHead;
	count--;
	return result;
}

int DoubleLinkedList::popBack()
{
	if (isEmpty)
	{
		return -1;
	}

	int result = tail->data;

	if (count == 1)
	{
		count = 0;
		head->next = tail;
		tail->prev = head;
		isEmpty = true;
		return result;
	}
	if (count == 2)
	{
		count = 1;
		tail->data = head->data;
		return result;
	}
	Node* newTail = tail->prev;
	tail->prev->next = nullptr;
	delete tail;
	tail = newTail;
	count--;

	return result;
}

void DoubleLinkedList::remove(int value)
{
	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		if (itterator->data == value)
		{
			if (itterator == head)
			{
				std::cout << "pop front" << std::endl;
				popFront();
				return;
			}
			else if (itterator == tail)
			{
				std::cout << "pop back" << std::endl;
				popBack();
				return;
			}
			else
			{
				std::cout << "removing mid" << std::endl;
				itterator->prev->next = itterator->next;
				itterator->next->prev = itterator->prev;
				count--;
				delete itterator;
				return;
			}
		}
		itterator = itterator->next;
	}
}

int DoubleLinkedList::getFront() const
{
	if (isEmpty)
	{
		return 0;
	}
	return head->data;
}

int DoubleLinkedList::getBack() const
{
	if (isEmpty)
	{
		return 0;
	}
	return tail->data;
}

int DoubleLinkedList::getCount() const
{
	return count;
}

void DoubleLinkedList::sort()
{
	if (isEmpty || count < 2)//no need to sort if theres less than 2 elements
	{
		return;
	}

	bool moreSortingNeeded = true;
	bool passMadeChanges = false;

	//bubble sort
	
	Node* left;
	Node* right;

	do
	{
		passMadeChanges = false;
		Node* itterator = head;
		for (int i = 0; i < count - 1; i++)
		{
			left = itterator;
			right = itterator->next;

			if (left->data > right->data)
			{
				swapValues(left, right);
				passMadeChanges = true;
			}
			itterator = itterator->next;
		}
		moreSortingNeeded = passMadeChanges;
	} 
	while (moreSortingNeeded);
}

int* DoubleLinkedList::toIntArray() const
{
	if (isEmpty)
	{
		return nullptr;
	}

	int* result = new int[count];

	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		result[i] = itterator->data;
		itterator = itterator->next;
	}
	return result;
}

void DoubleLinkedList::printList() const
{
	std::cout << "List count: " + std::to_string(count) << std::endl;

	if (isEmpty || head == nullptr)
	{
		return;
	}

	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		std::cout << "Node value: " + std::to_string(itterator->data) << std::endl;
		itterator = itterator->next;
	}
}

bool DoubleLinkedList::contains(int key) const
{
	Node* itterator = head;
	for (int i = 0; i < count; i++)
	{
		if (itterator->data == key)
		{
			return true;
		}
		itterator = itterator->next;
	}
	return false;
}

bool DoubleLinkedList::getIsEmpty() const
{
	return isEmpty;
}
