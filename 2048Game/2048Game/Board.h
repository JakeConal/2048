#pragma once
#include <string>

struct Board {
	int size;
	int score;
	int** a;

	float ptime;

	bool canUndo;
	bool canRedo;
	bool canAuto;

	std::string name;
	Board* next;

	Board();
	Board(int size);
	Board(int** data, int size, int score, float ptime, std::string name, bool canUndo, bool canRedo, bool canAuto);

	bool CanMoveHorizontally();
	bool CanMoveVertically();

	void GenNum();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void Display();
	void Release();
};

struct Stack {
	Board* head;
	int size;

	Stack();

	bool Empty();

	void Push(Board board);
	void Pop();
	void Release();

	Board Top();
};