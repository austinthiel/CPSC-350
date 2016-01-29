#include "QueensKnights.h"
#include <iostream>

using namespace std; 

int main (int argc, char *argv[]){
	QueensKnights qk; // create a QueensKnights object

	// do all the things
	qk.setBoard();
	qk.setNumQueensKnights();
	qk.solveQueens(qk.board, 0);
	qk.solveKnights(qk.board, 0);
	cout << "Knights board" << endl;
	qk.printBoard(qk.board);
	
	return 0;
}
