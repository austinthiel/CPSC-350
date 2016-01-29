#ifndef QUEUE_H
#define QUEUE_H

#include "QIF.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

template <typename T>

class Queue: public QIF<T>{
private:
	List<T> queue;
public:
	Queue();
	virtual ~Queue();
	
	void add(T m_node);
	T remove();
	void print();
	void addFile(int m_argc, char *m_argv[]);
	int getSize();

};

template <typename T>
Queue<T>::Queue(){

}

template <typename T>
Queue<T>::~Queue(){

}

template <typename T>
void Queue<T>::add(T m_node){
		queue.addToBack(m_node);
}

template <typename T>
T Queue<T>::remove(){
	queue.popFromFront();
}

template <typename T>
void Queue<T>::print(){
	queue.printList();
}

template <typename T>
void Queue<T>::addFile(int m_argc, char *m_argv[]){
	
}

template<typename T>
int Queue<T>::getSize(){
	queue.getSize();
}


#endif
