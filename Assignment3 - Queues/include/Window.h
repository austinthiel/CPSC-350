#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
using namespace std; // dirty

class Window{ // Window header, methods in here must be defined in window.cpp to function
private:
	//int time;
	//int occupied;
public:
	int time;
	int occupied;
	
	bool idleOver5;
	Window();
	Window(int m_time);
	int getTime();
	bool isOccupied();
	void addStudent(int m_time);
	bool clockTick();
	
	int idle5Time;
	int totalIdleTime;
	
};

#endif
