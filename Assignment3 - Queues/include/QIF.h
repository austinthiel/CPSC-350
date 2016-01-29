#ifndef QIF_H
#define QIF_H

template <typename T> // generic, any type can be stored in the queue

class QIF{ // interface for Queue header
public:

private:
	virtual void add(T d) = 0; // virtual methods, MUST BE DEFINED IN QUEUE TO RUN
	virtual T remove() = 0;
	virtual void print() = 0;
	virtual void addFile(int m_argc, char* m_argv[]) = 0;
	virtual int getSize() = 0;
};

#endif
