// LinkedList.h

// Note: This implementation of LinkedList is based on
// Chapter 4 of Bruno R. Preiss's Textbook:
// "Data Structures and Algorithms with Object-Oriented Design Patterns
//    in C++"

#ifndef __toyshell__LinkList__
#define __toyshell__LinkList__

#include <iostream>
#include "Alias.h"

using namespace std;

class Alias;
class LinkedList;
// needed for friend line below

class ListElement {
private:
	Alias *datum;
	ListElement* next;

public:
	ListElement(Alias*, ListElement*);
	~ListElement();

	Alias* getDatum() const;
	ListElement const* getNext() const;

	friend class LinkedList;
	// gives LinkedList access to datum and next
};

class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void add(Alias*);
	void deleteItem(Alias*);

	void deleteAllItems();

	Alias* find(string aliasName);

	Alias* at(unsigned long i);

	unsigned long getLength();

	void printList();

private:
	ListElement* head;
	unsigned long length;
};

#endif
