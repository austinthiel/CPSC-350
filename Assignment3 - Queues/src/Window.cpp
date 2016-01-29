#include "Window.h"
//#include <iostream>
//#include <string.h>
//#include <stdlib.h>

using namespace std;

Window::Window(){ // default window
	idleOver5 = false;
	occupied = false; // not occupied
	time = -1; // time hasnt begun
}

Window::Window(int m_time){ // window with a student added
	occupied = true; // becomes occupied
	time = m_time; // time begins
}

int Window::getTime(){ // grab time left for a student at the window
	return time;
}

bool Window::isOccupied(){ // check if student is at the window
	return occupied;
}

void Window::addStudent(int m_time){ // adds student with time to the window
	occupied = true; // becomes occupied
	time = m_time; // time begins
}

bool Window::clockTick(){ // modify time, clear window if empty
	time--;
	if (time == 0){ // if the student is done
		occupied = false; // make the student leave
		return true; // window is now free
	}else{
		return false; // window is still being used
	}
}
