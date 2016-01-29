#include <iostream>
#include <fstream>
#include "graphnotes.h"
#include "Controller.h"

using namespace std;

int main(int argc, char* argv[]){
 
	string file = "facebook_combined.txt";

	Controller* c = new Controller();
	Graph<int>* g = new Graph<int>(c->getGraphSize(file) + 1);
	
	c->addAllEdges(file, g);
	
	//cout << g->DFS(3000) << endl;
	//cout << g->BFS(3000) << endl;
	//g->primsMSTAlgorithm(3000);
	

}
