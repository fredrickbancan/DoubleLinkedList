#pragma once

struct Node
{
	Node* prev = nullptr;
	Node* next = nullptr;
	int data = 0;
};

/*A class for the abstraction of a double linked list (of ints, not templated).*/
class DoubleLinkedList
{
private:
	int count;
	bool isEmpty = true;
	Node* head = new Node{};
	Node* tail = new Node{};

	/*returns true if a node with key value is found, and outputs that node ptr
	  If no node is found, output node will be assigned nullptr*/
	bool find(int key, Node*& foundNode);

	/*Used for sorting, swaps the values of a and b*/
	void swapValues(Node* a, Node* b);
public:

	/*initializes this list with the count provided, initializes all values to the startValue (defaults to 0)*/
	DoubleLinkedList(int count = 0, int startValue = 0);

	/*deallocates list*/
	~DoubleLinkedList();

	/*adds the provided value to the front of the list*/
	void pushFront(int value);

	/*adds the provided value at the node with the value of the provided key. If such a node is not found, adds value to back or front of list depending on before flag.
	Inserts before or after the found node based on the before flag. Returns true or false depending on whether the key was found.*/
	bool insertAt(int key, int value, bool before);

	/*adds the provided value to the back of the list*/
	void pushBack(int value);

	/*returns and removes the value at the front of the list. If the list is empty, returns -1 instead*/
	int popFront();

	/*returns and removes the value at the back of the list, If the list is empty, returns -1 instead*/
	int popBack();

	/*returns the value at the front of the list*/
	int getFront() const;

	/*returns the value at the back of the list*/
	int getBack() const;

	/*returns the number of elements in this list*/
	int getCount() const;

	/*sorts the list by numerical value using bubble sort*/
	void sort();

	/*returns all values as a single array of integers*/
	int* toIntArray() const;

	/*prints the whole array to console */
	void printList() const;

	/*returns true if list contains node with provided key value*/
	bool contains(int key) const;

	/*returns pointer to head node of list, useful for itterating*/
	Node* getHead() const { return head; }

	/*returns pointer to tail node of list, useful for ittterating*/
	Node* getTail() const { return tail; }

	/*returns true if list does not contain any elements*/
	bool getIsEmpty() const;
};