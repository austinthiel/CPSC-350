#include "QueensKnights.h"
#include <iostream>

using namespace std;

void QueensKnights::setBoard(){ // instantiates board according to user inputted size
	cout << "Enter a board size: ";
	cin >> N;
	board = new int*[N];
	for (i = 0; i < N; ++i){
		board[i] = new int[N];
	}
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; ++j){
			board [i][j] = false;
		}
	}
}

void QueensKnights::setNumQueensKnights(){ // take in number of queens and knights to place
	cout << "Enter number of queens/knights to be placed: ";
	cin >> numQueens;
	numKnights = numQueens; // queens and knights are equal
}

void QueensKnights::printBoard(int** board){ // prints current board, converts integers to a more readable board
	for (i = 0; i < N; ++i){
		for (j = 0; j < N; ++j){
			if (board [i][j] == 0){
				cout << "." << ' ';
			}
			else if (board [i][j] == 1){
				cout << "Q" << ' ';
			}
			else if (board [i][j] == 2){
				cout << "K" << ' ';
			}
		}
		cout << endl;
	}
}


bool QueensKnights::solveQueens(int** board, int col){ // places queens with backtracking
	if (numQueens == 0) return true; // base case
	
	for (int rowToTry = 0; rowToTry < N; rowToTry++){
		if (queenIsSafe(board, rowToTry, col)){
			placeQueen(board, rowToTry, col); // try queen here
			--numQueens;
			if (solveQueens(board, col + 1)) return true; // recur to place rest
			removeQueen(board, rowToTry, col);
			++numQueens;
		}
		
	}
	return false;
}

bool QueensKnights::solveKnights(int** board, int col){ // places knights with backtracking
	if (numKnights == 0) return true; // base case
	for(int rowToTry = 0; rowToTry < N; rowToTry++){
		if (knightIsSafe(board, rowToTry, col)){
			placeKnight(board, rowToTry, col);
			--numKnights;
			if (solveKnights(board, col + 1)) return true; // recur
			removeKnight(board, rowToTry, col);
			++numKnights;
		}
	}
	return false;
}


void QueensKnights::placeQueen(int** board, int row, int col){
	board[row][col] = true; // queens stored as integer 1
}

void QueensKnights::removeQueen(int** board, int row, int col){
	board[row][col] = false; // empty spot stored as integer 0
}

void QueensKnights::placeKnight(int** board, int row, int col){
	board[row][col] = 2; // knights stores as integer 2
}

void QueensKnights::removeKnight(int** board, int row, int col){
	board[row][col] = false; // empty spot 0
}

bool QueensKnights::queenIsSafe(int** board, int row, int col){ // check if diagnal movement and row movement don't interfere with other pieces
	return (lowerDiagIsClear(board, row, col) &&
		rowIsClear(board, row, col) &&
		upperDiagIsClear(board, row, col));
}

bool QueensKnights::knightIsSafe(int** board, int row, int col){ // check if all queen movement and knight movement don't interfere with other pieces
	return (lowerDiagIsClear(board, row, col) &&
		rowIsClear(board, row, col) &&
		upperDiagIsClear(board, row, col)/* &&
		colIsClear(board, row, col) &&
		knightMovementIsClear(board, row, col)*/);
}

bool QueensKnights::rowIsClear(int** board, int queenRow, int queenCol){ // row has no other pieces
	for (int col = 0; col < queenCol; col++){
		if (board[queenRow][col] == 1){
			return false;
		}
	}
	return true;
}

bool QueensKnights::colIsClear(int** board, int knightRow, int knightCol){ // column has no other pieces
	for (int i = 0; i < knightRow; i++){
		if(board[i][knightCol] == 1){
			return false;
		}
	}
	return true;
}

bool QueensKnights::upperDiagIsClear(int** board, int queenRow, int queenCol){ // self explanatory
	int row, col;
	for (row = queenRow, col = queenCol; col >= 0 && row < N; row++, col--) {
		if (board[row][col] == 1)
			return false;
	}
	return true;
}

bool QueensKnights::lowerDiagIsClear(int** board, int queenRow, int queenCol){ // self explanatory
	int row, col;
	for (row = queenRow, col = queenCol; row >= 0 && col >= 0; row--, col--){
		if (board[row][col] == 1){
			return false;
		}
	}
	return true;
}

bool QueensKnights::knightMovementIsClear(int** board, int knightRow, int knightCol){ // hard coded to test each possible knight move, accounts for out of bounds exceptions
	int row = knightRow;
	int col = knightCol;
	
	int t1 = -1; // all moves are invalid until proven valid
	int t2 = -1;
	int t3 = -1;
	int t4 = -1;
	int t5 = -1;
	int t6 = -1;
	int t7 = -1;
	int t8 = -1;
	
	if (row+2 > N-1 || col-1 < 0){ // if out of bounds
		t1 = 0; // its neutral, placement still valid 
	}else if (row+2 <= N-1 && col-1 >= 0 && board[row+2][col-1] == 0){ // if IN bounds and not attacking
		t1 = 1; // valid move
	}
	
	if (row+2 > N-1 || col+1 > N-1){
		t2 = 0;
	}else if (row+2 <= N-1 && col+1 <= N-1 && board[row+2][col+1] == 0){
		t2 = 1;
	}
	
	if (row-2 < 0 || col-1 < 0){
		t3 = 0;
	}else if (row-2 >= 0 && col-1 >= 0 && board[row-2][col-1] == 0){
		t3 = 1;
	}
	
	if (row-2 < 0 || col+1 > N-1){
		t4 = 0;
	}else if (row-2 >= 0 && col+1 <= N-1 && board[row-2][col+1] == 0){
		t4 = 1;
	}
	
	if (row-1 < 0 || col+2 > N-1){ // if out of bounds
		t5 = 0;
	}else if (row-1 >= 0 && col+2 <= N-1 && board[row-1][col+2] == 0){
		t5 = 1;
	}
	
	if (row+1 > N-1 || col+2 > N-1){
		t6 = 0;
	}else if (row+1 <= N-1 && col+2 <= N-1 && board[row+1][col+2] == 0){
		t6 = 1;
	}
	
	if (row-1 < 0 || col-2 < 0){
		t7 = 0;
	}else if (row-1 >= 0 && col-2 >= 0 && board[row-1][col-2] == 0){
		t7 = 1;
	}
	
	if (row+1 > N-1 && col+2 > N-1){
		t8 = 0;
	}else if (row+1 <= N-1 && col+2 <= N-1 && board[row+1][col+2] == 0){
		t8 = 1;
	}
	
	return t1 >= 0 && t2 >= 0 && t3 >= 0 &&
		t4 >= 0 && t5 >= 0 && t6 >= 0 &&
		t7 >= 0 && t8 >= 0;		
}

void QueensKnights::clearBoard(int** board){ // wipe the board back to all 0's
	for (int row = 0; row < N; row++){
		for (int col = 0; col < N; col++){
			board[row][col] = false;
		}
	}
}
