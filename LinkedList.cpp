//LinkedList.cpp

// Note: This implementation of LinkedList is based on
// Chapter 4 of Bruno R. Preiss's Textbook:
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#include "LinkedList.h"
using namespace std;

//---------------------------------------------------
//List Element Members
//---------------------------------------------------
ListElement::ListElement(Alias *_datum, ListElement *_next) :
		datum(_datum), next(_next) {
}

ListElement::~ListElement() {
	delete this->datum;
}

Alias* ListElement::getDatum() const {
	return datum;
}

ListElement const* ListElement::getNext() const {
	return next;
}

//---------------------------------------------------
//LinkedList Members
//---------------------------------------------------
LinkedList::LinkedList() :
		head(0) {
	this->length = 0;
}

LinkedList::~LinkedList() {
	deleteAllItems();
}

void LinkedList::add(Alias *item) {

	if (!head) {
		ListElement *newNode = new ListElement(item, NULL);
		head = newNode;
	} else {

		ListElement *currPtr = head;
		while (currPtr->next != NULL)
			currPtr = currPtr->next;

		ListElement *newNode = new ListElement(item, NULL);
		currPtr->next = newNode;
	}

	this->length++;
}

void LinkedList::deleteAllItems() {
	ListElement *current = head;
	ListElement *prev;

	while (current) {
		prev = current;
		current = current->next;
		delete prev;
	}
	head = NULL;
}

void LinkedList::deleteItem(Alias *item) {

	ListElement *deletePtr = NULL;
	ListElement *currPtr;

	if (item->getAliasString() == head->datum->getAliasString()) {
		deletePtr = head;
		head = head->next;
	} else {
		currPtr = head;
		while (currPtr->next->datum->getAliasString() != item->getAliasString()) {

			currPtr = currPtr->next;

			if (currPtr->next == NULL) {
				cout << "doesn't exist\n";
				return;
			}
		}

		deletePtr = currPtr->next;
		currPtr->next = deletePtr->next;
	}

	if (deletePtr == NULL)
		return;

	delete deletePtr;
	deletePtr = NULL;

	this->length--;
}

void LinkedList::printList() {

	ListElement *currPtr = head;
	while (currPtr != NULL) {
		cout << currPtr->datum->getAliasString() << ": "
				<< currPtr->datum->getCommandString() << endl;
		currPtr = currPtr->next;
	}
	cout << endl;
}

Alias* LinkedList::find(string aliasName) {
	ListElement *currPtr = head;

	while (currPtr != NULL) {
		if (currPtr->datum->getAliasString() == aliasName)
			return currPtr->datum;
		else
			currPtr = currPtr->next;
	}

	return NULL;
}

Alias* LinkedList::at(unsigned long i) {
	unsigned long j = 0;
	ListElement *currPtr = head;

	if (i >= length)
		return NULL;

	while (++j <= i)
		currPtr = currPtr->next;

	return currPtr->datum;
}

unsigned long LinkedList::getLength() {
	return this->length;
}

