#ifndef QUEENSKNIGHTS_H
#define QUEENSKNIGHTS_H

class QueensKnights{

	public:
		void setBoard();
		void setNumQueensKnights();
		void printBoard(int** board);
		bool solveQueens(int** board, int col);
		bool solveKnights(int** board, int col);
		void placeQueen(int** board, int row, int col);
		void removeQueen(int** board, int row, int col);
		void placeKnight(int** board, int row, int col);
		void removeKnight(int** board, int row, int col);
		bool queenIsSafe(int** board, int row, int col);
		bool knightIsSafe(int** board, int row, int col);
		bool rowIsClear(int** board, int queenRow, int queenCol);
		bool colIsClear(int** board, int knightRow, int knightCol);
		bool upperDiagIsClear(int** board, int queenRow, int queenCol);
		bool lowerDiagIsClear(int** board, int queenRow, int queenCol);
		bool knightMovementIsClear(int** board, int knightRow, int knightCol);
		void clearBoard(int** board);
		
		int numQueens;
		int numKnights;
		int N;
		int** board; // segfaults if private, not sure why

	private:
		int i;
		int j;
};

#endif

