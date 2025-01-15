#include "Header.h"
#include "Game.h"
#include "Auto.h"

bool CanMove(string direction, Board board) {
	if ((direction == "left" || direction == "right") && board.CanMoveHorizontally())
		return true;
	if ((direction == "up" || direction == "down") && board.CanMoveVertically())
		return true;
	return false;
}	

void DecideMove(Board& board, string direction) {
	if (direction == "right") {
		board.MoveRight();
	}
	else if (direction == "left") {
		board.MoveLeft();
	}
	else if (direction == "up") {
		board.MoveUp();
	}
	else if (direction == "down") {
		board.MoveDown();
	}
}

void AutoPlay(Board& board, Stack& prev, Stack& next, bool& isWon, bool& isLost, bool& isContinue, bool& quit, Top20List topPlayer) {
	while (!IsGameOver(board, isLost, isWon, isContinue, quit, topPlayer)) {
		if (_kbhit()) {
			char key = _getch();
			if (key == 'w' || key == 'a' || key == 's' || key == 'd' || key == 'h' || key == ' ' || key == 'e')
				break;
		}

		system("cls");
		
		string bestMove;
		Maximize(board, bestMove, 1);

		prev.Push(board);
		next.Release();
		DecideMove(board, bestMove);
		board.GenNum();
		board.Display();

		Sleep(100);
	}
}

//Minimax Algorithm 
int Maximize(Board board, string& bestMove, int depth) {
	if (IsLost(board)) return -1000000000;
	int maxDepth = board.size > 5 ? 2 : 3;
	if (depth == maxDepth) return Evaluate(board);

	string direction[4] = { "left", "right", "up" , "down" };
	int directionScore[4] = { 0, 0, 0 , 0 };
	int bestScoreIndex = 0;

	for (int i = 0; i < 4; i++) {
		if (CanMove(direction[i], board)) {
			Board evaBoard(board.a, board.size, board.score, board.ptime, board.name, board.canUndo, board.canRedo, board.canAuto);
			DecideMove(evaBoard, direction[i]);
			directionScore[i] = Minimize(evaBoard, bestMove, depth);
			bestScoreIndex = i;
			evaBoard.Release();
		}
		else {
			directionScore[i] = -1000000000;
		}
	}

	
	for (int i = 0; i < 4; i++)
		if (directionScore[i] > directionScore[bestScoreIndex] && CanMove(direction[i], board))
			bestScoreIndex = i;

	bestMove = direction[bestScoreIndex];
	return directionScore[bestScoreIndex];
}

int Minimize(Board board, string& bestMove, int depth) {
	if (IsLost(board)) return -1000000000;

	int tileScore = 1000000000;
	bool isZeroEmptyCell = true;

	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			if (board.a[i][j] == 0) {
				isZeroEmptyCell = false;

				board.a[i][j] = 2;
				tileScore = min(tileScore, Maximize(board, bestMove, depth + 1));

				board.a[i][j] = 4;
				tileScore = min(tileScore, Maximize(board, bestMove, depth + 1));
				
				board.a[i][j] = 0;
			}
		}
	}

	if (isZeroEmptyCell)
		return Maximize(board, bestMove, depth + 1);
	else
		return tileScore;
}

int Evaluate(Board board) {

	int** weight = new int* [board.size];
	for (int i = 0; i < board.size; i++)
		weight[i] = new int[board.size];

	int value = board.size * 2 - 1;

	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			weight[i][j] = (value - i - j) * 2;
		}
	}

	int boardScore = 0;
	//calculate the score of the board
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			boardScore += board.a[i][j] * weight[i][j];
		}
	}

	for (int i = 0; i < board.size; i++)
		delete[] weight[i];
	delete[] weight;

	return boardScore;
}
