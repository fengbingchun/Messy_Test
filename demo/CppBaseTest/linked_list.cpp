#include "linked_list.hpp"
#include <iostream>

// Blog: http://blog.csdn.net/fengbingchun/article/details/52132610

///////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/linkedlist.php
typedef struct Element
{
	void *data;
	struct Element *next;
} Element;

bool push(Element **top, void *data)
{
	Element *elem = new Element;
	if (!elem) return false;

	elem->data = data;
	elem->next = *top;
	*top = elem;
	return true;
}

bool createStack(Element **top)
{
	*top = NULL;
	return true;
}

bool pop(Element **top, void **data)
{
	Element *elem;
	if (!(elem = *top)) return false;

	*data = elem->data;
	*top = elem->next;
	delete elem;
	return true;
}

bool deleteStack(Element **top)
{
	Element *elem;
	while (*top) {
		elem = (*top)->next;
		delete *top;
		*top = elem;
	}
	return true;
}

bool sortNode(Element **head)
{
	for (Element *temp1 = *head; temp1 != NULL; temp1 = temp1->next) {
		for (Element *temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next) {
			if (*(static_cast<int *>(temp1->data)) > *(static_cast<int *>(temp2->data))) {
				int temp = *(static_cast<int *>(temp1->data));
				*(static_cast<int *>(temp1->data)) = *(static_cast<int *>(temp2->data));
				*(static_cast<int *>(temp2->data)) = temp;
			}
		}
	}

	return true;
}

void printStack(Element *top)
{
	if (top == NULL) {
		std::cout << "Empty!" << std::endl;
	}
	Element *cur = top;
	while (cur) {
		std::cout << *(static_cast<int *>(cur->data)) << " ";
		cur = cur->next;
	}
	std::cout << std::endl << std::endl;
}

int test_linked_list1()
{
	Element *head;
	createStack(&head);
	int n1 = 30, n2 = -20, n3 = 300, n4 = -40, n5 = 50;
	push(&head, &n1);
	push(&head, &n2);
	push(&head, &n3);
	push(&head, &n4);
	push(&head, &n5);

	printStack(head);

	sortNode(&head);
	printStack(head);

	void * n;
	pop(&head, &n);
	std::cout << "popped " << *(static_cast<int*>(n)) << std::endl;
	pop(&head, &n);
	std::cout << "popped " << *(static_cast<int*>(n)) << std::endl;
	std::cout << std::endl;

	printStack(head);

	std::cout << "deleting stack..." << std::endl;
	deleteStack(&head);
	printStack(head);

	return 0;
}
////////////////////////////////////////////////////////
// reference: http://www.bogotobogo.com/cplusplus/linkedlist.php
struct Node {
	int data;
	Node* next;
};

// only for the 1st Node
void initNode(struct Node *head, int n){
	head->data = n;
	head->next = NULL;
}

// apending
void addNode(struct Node *head, int n) {
	Node *newNode = new Node;
	newNode->data = n;
	newNode->next = NULL;

	Node *cur = head;
	while (cur) {
		if (cur->next == NULL) {
			cur->next = newNode;
			return;
		}
		cur = cur->next;
	}
}

void insertFront(struct Node **head, int n) {
	Node *newNode = new Node;
	newNode->data = n;
	newNode->next = *head;
	*head = newNode;
}

struct Node *searchNode(struct Node *head, int n) {
	Node *cur = head;
	while (cur) {
		if (cur->data == n) return cur;
		cur = cur->next;
	}
	std::cout << "No Node " << n << " in list.\n";
}

bool deleteNode(struct Node **head, Node *ptrDel) {
	Node *cur = *head;
	if (ptrDel == *head) {
		*head = cur->next;
		delete ptrDel;
		return true;
	}

	while (cur) {
		if (cur->next == ptrDel) {
			cur->next = ptrDel->next;
			delete ptrDel;
			return true;
		}
		cur = cur->next;
	}
	return false;
}

// reverse the list
struct Node* reverse(struct Node** head)
{
	Node *parent = *head;
	Node *me = parent->next;
	Node *child = me->next;

	/* make parent as tail */
	parent->next = NULL;
	while (child) {
		me->next = parent;
		parent = me;
		me = child;
		child = child->next;
	}
	me->next = parent;
	*head = me;
	return *head;
}

// Creating a copy of a linked list
void copyLinkedList(struct Node *node, struct Node **pNew)
{
	if (node != NULL) {
		*pNew = new Node;
		(*pNew)->data = node->data;
		(*pNew)->next = NULL;
		copyLinkedList(node->next, &((*pNew)->next));
	}
}

// Compare two linked list. return value: same(1), different(0)
int compareLinkedList(struct Node *node1, struct Node *node2)
{
	static int flag;

	// both lists are NULL
	if (node1 == NULL && node2 == NULL) {
		flag = 1;
	} else {
		if (node1 == NULL || node2 == NULL)
			flag = 0;
		else if (node1->data != node2->data)
			flag = 0;
		else
			compareLinkedList(node1->next, node2->next);
	}

	return flag;
}

void deleteLinkedList(struct Node **node)
{
	struct Node *tmpNode;
	while (*node) {
		tmpNode = *node;
		*node = tmpNode->next;
		delete tmpNode;
	}
}

void display(struct Node *head) {
	Node *list = head;
	while (list) {
		std::cout << list->data << " ";
		list = list->next;
	}
	std::cout << std::endl;
}

int test_linked_list2()
{
	struct Node *newHead;
	struct Node *head = new Node;

	initNode(head, 10);
	display(head);

	addNode(head, 20);
	display(head);

	addNode(head, 30);
	display(head);

	addNode(head, 35);
	display(head);

	addNode(head, 40);
	display(head);

	insertFront(&head, 5);
	display(head);

	int numDel = 5;
	Node *ptrDelete = searchNode(head, numDel);
	if (deleteNode(&head, ptrDelete))
		std::cout << "Node " << numDel << " deleted!\n";
	display(head);

	std::cout << "The list is reversed\n";
	reverse(&head);
	display(head);

	std::cout << "The list is copied\n";
	copyLinkedList(head, &newHead);
	display(newHead);

	std::cout << "Comparing the two lists...\n";
	std::cout << "Are the two lists same?\n";
	if (compareLinkedList(head, newHead))
		std::cout << "Yes, they are same!\n";
	else
		std::cout << "No, they are different!\n";
	std::cout << std::endl;

	numDel = 35;
	ptrDelete = searchNode(newHead, numDel);
	if (deleteNode(&newHead, ptrDelete)) {
		std::cout << "Node " << numDel << " deleted!\n";
		std::cout << "The new list after the delete is\n";
		display(newHead);
	}
	std::cout << "Comparing the two lists again...\n";
	std::cout << "Are the two lists same?\n";
	if (compareLinkedList(head, newHead))
		std::cout << "Yes, they are same!\n";
	else
		std::cout << "No, they are different!\n";

	std::cout << std::endl;
	std::cout << "Deleting the copied list\n";
	deleteLinkedList(&newHead);
	display(newHead);
	return 0;
}

