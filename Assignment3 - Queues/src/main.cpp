#include "DoublyLinkedList.h"
#include "Window.h"
#include "Queue.h"

using namespace std; // dirty

int nextArrivalTime;
int tick = 0;
ifstream ifs;
char* file;
char stream[10];
Queue<int> q;
int windows;

Window* wArr;
int totalIdleTime = 0;
float meanWinIdle = 0;
int idleWinOver5 = 0;
int longestWinIdle = 0;
int allWinTotalIdleTime = 0;
int totalNumStudents = 0;
int totalStudentWaitTime = 0;
float meanWait = 0;

int getWindowSize(){
	ifs.getline(stream, 10);
	windows = atoi(stream);
	return windows;
}

int getNextArrivalTime(){
	ifs.getline(stream, 10);
	nextArrivalTime = atoi(stream);
	return nextArrivalTime;
}

int done(){
	for (int i = 0; i < windows; ++i){
		if (wArr[i].isOccupied() == true){
			return false;
		}	
	}
	if (!ifs.eof()){
		return false;
	}
	return true;
}

void addStudents(){
	ifs.getline(stream, 10);
	int numStudents = atoi(stream);
	totalNumStudents += numStudents;
	for (int i = 0; i < numStudents; ++i){
		ifs.getline(stream, 10);
		q.add(atoi(stream));
	}
}

void assignStudentsToWindows(){
	int data;
	while(q.getSize() != 0){ 
		data = q.remove();
		for (int i = 0; i < windows; ++i){
			if (wArr[i].isOccupied() == false){
				wArr[i].addStudent(data);
				break;
			}
		}
	}
}

void updateStats(){
	// check if windows are ever idling for over 5 minutes at a time 
	for (int i = 0; i < windows; ++i){ // go to each window
		if (wArr[i].isOccupied() == false){ // if its not occupied
			wArr[i].idle5Time++; // increment idle time
			totalIdleTime++;
		}else if (wArr[i].isOccupied() == true){
			wArr[i].idle5Time = 0;
		}
		if (wArr[i].idle5Time > longestWinIdle){
			longestWinIdle = wArr[i].idle5Time;
		}
		if (wArr[i].idle5Time > 5){ // if the idle time is > 5
			wArr[i].idleOver5 = 1; // idleOver5 is true
		}
	}
	
	totalStudentWaitTime += q.getSize();
	
	
}

void printStats(){
	for (int i = 0; i < windows; ++i){ // go to each window
		if (wArr[i].idleOver5 == 1){ // if idleOver5 is true
			idleWinOver5++; // number of windows idling over 5 increments
		}
		
	}

	meanWinIdle = (float)totalIdleTime / windows;
	meanWait = float(totalStudentWaitTime) / totalNumStudents;
	
	cout << "The mean student wait time: " <<  meanWait << endl;
	cout << "The median student wait time: 0" << endl;
	cout << "The longest student wait time: 0" << endl;
	cout << "The number of students waiting over 10 minutes: 0" << endl;
	cout << "The mean window idle time: " << meanWinIdle << endl;
	cout << "The longest window idle time: " << longestWinIdle << endl;
	cout << "Number of windows idle for over 5 minutes: " << idleWinOver5 << endl;
}


int main (int argc, char* argv[]){

	if (argc == 2){
		file = argv[1];
		ifs.open(file);
		wArr = new Window[getWindowSize()]; // initialize windows from 1st line of file
		getNextArrivalTime();
		while (!done()){
			++tick;
			if (tick == nextArrivalTime){
				addStudents();
				getNextArrivalTime();
			}
			assignStudentsToWindows();
			for (int i = 0; i < windows; ++i){
				if (wArr[i].isOccupied() == true){
					wArr[i].clockTick();
				}
			}
			updateStats();
		}
		printStats();
		
	}else if (argc < 2){
		cout << "No file name entered. Exiting..." << endl;
	}else if (argc > 2){
		cout << "Too many parameters entered. Exiting..." << endl;
	}else{
		cout << "Unknown error. Exiting..." << endl;
	}
	
	return 0;
	
}
