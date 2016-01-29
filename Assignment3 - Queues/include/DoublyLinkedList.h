#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>

using namespace std; // dirty

template <typename T>

class ListNode{ // defines what a node is, and its fuctions
public:
	ListNode(T m_node); // constructor with a node value
	virtual ~ListNode(); // destructor
	
	ListNode<T>* prev; // point to previous node
	ListNode<T>* next; // point to next node
	
	T data; // each node holds a piece of data of type T
};

template <typename T>
class List{ // define a list and its functions
private:
	ListNode<T>* head; // each list has a beginning
	ListNode<T>* tail; // and an end
	int size; // keep track of the size of the list
public:
	List(); // constructor
	virtual ~List(); // destructor
	
	void addToBack(T m_node); // declared methods
	T popFromFront();
	void printList();
	int getSize();
};

template <typename T>
ListNode<T>::ListNode(T m_node){ // begin adding new data to a node in the list
	prev = 0; // defaults
	next = 0;
	data = m_node; // node value will be the passed in data
}

template <typename T>
ListNode<T>::~ListNode(){ // nothing to destruct, no dynamic memory allocation

}

template <typename T>
List<T>::List(){ // fresh list
	head = 0;
	tail = 0;
	size = 0;
}
template <typename T>
List<T>::~List(){ // remove all nodes from the list and delete them
	struct ListNode<T>* next;
	while (head != 0){
		next = head->next;
		delete head;
		head = next;
	}
}

template <typename T>
void List<T>::addToBack(T m_node){ // add a node with data to the back of the list
	if(size == 0){
		head = new ListNode<T>(m_node);
		tail = head;
	}else{
		ListNode<T>* temp = tail;
		tail = new ListNode<T>(m_node);
		temp->next = tail;
		tail->prev = temp;
		tail->next = NULL;
	}
	size++;
}

template <typename T>
T List<T>::popFromFront(){ // grab a node and remove it from the front of the list

	if (getSize() == 0){
		return -1;
	}else{
		ListNode<T>* temp = head;
		if (head->next == 0){
			tail = 0;
		}else{
			head->next->prev = 0;
		}
		head = head->next;
		temp->next = 0;
		T ret = temp->data;
		delete temp;
		size--;
		return ret;
	}


/*
	T ret;
	if(head == NULL){ // cant grab a node from an empty list!
		std::cout << "\n\n***The list is empty***\n\n";
	}else{
		ret = head->data;
		ListNode<T>* temp = head;
		temp->next->prev = NULL;
		head = temp->next;
		temp->next = NULL;
		head->next = NULL;
		size--;
	}
	return ret; // return the data inside the node we just removed 
*/
}

template <typename T>
void List<T>::printList(){ // print all the data in the list from head to tail
	ListNode<T>* thisNode = head; // start at the head of the list
	while(thisNode != NULL){ // stop at the tail of the list
		cout << thisNode->data << "\n";
		thisNode = thisNode->next;
	}
	cout << "\n";
}

template<typename T>
int List<T>::getSize(){
	return size;
}

#endif
