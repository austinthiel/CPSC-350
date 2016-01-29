#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <iostream>

using namespace std;

class Controller{
private:

public:
	int x;
	int y;
	int currMax;
	
	Controller();
	int getGraphSize(string fileName);
	int addAllEdges(string fileName, Graph<int>* g);
};

Controller::Controller(){
	x = 0;
	y = 0;
	currMax = 0;
}

int Controller::getGraphSize(string fileName){
	string line;
	ifstream file(fileName.c_str());
	if(file.good()){
		while(!file.eof()){
			file >> x >> y;
			if(x > currMax) { currMax = x; }
			if(y > currMax) { currMax = y; }
		}
		file.close();
		return currMax;
	}else cout << "Unable to open file";
	return 0;
}

int Controller::addAllEdges(string fileName, Graph<int>* g){
	string line;
	ifstream file(fileName.c_str());
	if(file.good()){
		while(!file.eof()){
			file >> x >> y;
			g->addEdge(x, y, 1);
		}
		file.close();
	}else cout << "Unable to open file";
	return 0;
}

#endif
