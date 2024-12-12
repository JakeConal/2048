#pragma once
#include "Board.h"
#include "Player.h"

bool CanMove(std::string direction, Board board);

int Maximize(Board board, std::string& bestMove, int depth);
int Minimize(Board board, std::string& bestMove, int depth);
int Evaluate(Board board);

void DecideMove(Board& board, std::string direction);
void AutoPlay(Board& board, Stack& prev, Stack& next, bool& isWon, bool& isLost, bool& isContinue, bool& quit, Top20List topPlayer);

