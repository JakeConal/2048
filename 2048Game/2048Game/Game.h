#pragma once
#include "Board.h"
#include "Player.h"
#include <fstream>


bool IsWon(Board board);
bool IsLost(Board board);
bool IsGameOver(Board board, bool& isLose, bool& isWon, bool& isContinue, bool& quit, Top20List topPlayer);
bool isValidName(std::string name, Top20List topPlayer, SavedPlayersList savedPlayer);


void CheckGameInput(Board& board, Stack& prev, Stack& next, bool& isLost, bool& isWon, bool& isContinue, bool& quit, Top20List topPlayer);
void NewGame(int size, bool canUndo, bool canRedo, bool canAuto);
void Resume(bool canUndo, bool canRedo, bool canAuto);
void SaveGame(Board board, SavedPlayersList& savedPlayer);

