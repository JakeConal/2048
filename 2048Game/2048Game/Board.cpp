#include "Header.h"
#include <Windows.h>
#include "Board.h"
#include "Graphic.h"

Board::Board() {
	size = 0;
	score = 0;
	a = NULL;
	next = NULL;
	name = "unknown";
	canRedo = false;
	canUndo = false;
	canAuto = false;
}

Board::Board(int size) {
	this->size = size;
	this->score = 0;
	this->next = NULL;
	this->canUndo = false;
	this->canRedo = false;
	this->canAuto = false;

	a = new int* [size];

	for (int i = 0; i < size; i++) {
		a[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = 0;
		}
	}

	GenNum();
}

Board::Board(int** data, int size, int score, float ptime, string name, bool canUndo, bool canRedo, bool canAuto) {
	this->size = size;
	this->score = score;
	this->next = NULL;
	this->ptime = ptime;
	this->name = name;
	this->canUndo = canUndo;
	this->canRedo = canRedo;
	this->canAuto = canAuto;

	a = new int* [size];

	for (int i = 0; i < size; i++) {
		a[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = data[i][j];
		}
	}
}

bool Board::CanMoveHorizontally() {
	bool canMove = false;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if ((j > 0 && a[i][j] == a[i][j - 1]) || a[i][j] == 0)
				canMove = true;

	return canMove;
}

bool Board::CanMoveVertically() {
	bool canMove = false;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if ((i > 0 && a[i][j] == a[i - 1][j]) || a[i][j] == 0)
				canMove = true;

	return canMove;
}

void Board::GenNum() {
	srand(time(0));

	int zeroCount = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (a[i][j] == 0) {
				zeroCount++;
			}
		}
	}
	if (zeroCount == size * size) {
		zeroCount = 2;
	}
	else if (zeroCount > 1) {
		zeroCount = 1;
	}

	while (zeroCount) {
		int i = rand() % size;
		int j = rand() % size;
		if (a[i][j] == 0) {
			a[i][j] = rand() % 2 ? 2 : 4;
			//a[i][j] = rand() % 2 ? 512 : 1024;
			zeroCount--;
		}
	}
}

void Board::MoveLeft() {
	for (int i = 0; i < size; i++) {

		int k = 0;

		for (int j = 0; j < size; j++) {
			if (a[i][j] != 0) {
				a[i][k++] = a[i][j];
			}
		}

		while (k < size) {
			a[i][k++] = 0;
		}

		for (int j = 0; j < size - 1; j++) {
			if (a[i][j] == a[i][j + 1]) {
				a[i][j] += a[i][j + 1];
				score += a[i][j];
				for (int k = j + 1; k < size - 1; k++) {
					a[i][k] = a[i][k + 1];
				}
				a[i][size - 1] = 0;
			}
		}
	}
}

void Board::MoveRight() {
	for (int i = 0; i < size; i++) {

		int k = size - 1;

		for (int j = size - 1; j >= 0; j--) {
			if (a[i][j] != 0) {
				a[i][k--] = a[i][j];
			}
		}

		while (k >= 0) {
			a[i][k--] = 0;
		}

		for (int j = size - 1; j > 0; j--) {
			if (a[i][j] == a[i][j - 1]) {
				a[i][j] += a[i][j - 1];
				score += a[i][j];
				for (int k = j - 1; k > 0; k--) {
					a[i][k] = a[i][k - 1];
				}
				a[i][0] = 0;
			}
		}
	}
}

void Board::MoveUp() {
	for (int j = 0; j < size; j++) {

		int k = 0;

		for (int i = 0; i < size; i++) {
			if (a[i][j] != 0) {
				a[k++][j] = a[i][j];
			}
		}

		while (k < size) {
			a[k++][j] = 0;
		}

		for (int i = 0; i < size - 1; i++) {
			if (a[i][j] == a[i + 1][j]) {
				a[i][j] += a[i + 1][j];
				score += a[i][j];
				for (int k = i + 1; k < size - 1; k++) {
					a[k][j] = a[k + 1][j];
				}
				a[size - 1][j] = 0;
			}
		}
	}
}

void Board::MoveDown() {
	for (int j = 0; j < size; j++) {

		int k = size - 1;

		for (int i = size - 1; i >= 0; i--) {
			if (a[i][j] != 0) {
				a[k--][j] = a[i][j];
			}
		}

		while (k >= 0) {
			a[k--][j] = 0;
		}

		for (int i = size - 1; i > 0; i--) {
			if (a[i][j] == a[i - 1][j]) {
				a[i][j] += a[i - 1][j];
				score += a[i][j];
				for (int k = i - 1; k > 0; k--) {
					a[k][j] = a[k - 1][j];
				}
				a[0][j] = 0;
			}
		}
	}
}

void Board::Display() {
	cout << "\t\t\t     \x1B[93m ____   ___  _  _    ___\33[0m" << '\n';
	cout << "\t\t\t     \x1B[93m|___ \\ / _ \\| || |  ( _ )\33[0m           \x1B[33;1mNAME: " << name << '\n';
	cout << "\t\t\t     \x1B[93m  __) | | | | || |_ / _ \\\33[0m" << '\n';
	cout << "\t\t\t     \x1B[93m / __/| |_| |__   _| (_) |\33[0m          \x1B[33;1mSCORE: " << score << '\n';
	cout << "\t\t\t     \x1B[93m|_____|\\___/   |_|  \\___/\33[0m" << '\n';

	string undo, redo, autoPlay;
	undo = canUndo ? "\033[33mUNDO[U]\33[0m" : "\033[90mUNDO[U]\33[0m";
	redo = canRedo ? "\033[33mREDO[R]\33[0m" : "\033[90mREDO[R]\33[0m";
	autoPlay = canAuto ? "\033[33mAUTO[H]\33[0m" : "\033[90mAUTO[H]\33[0m";

	cout << "\t\t\t     \033[33m---------------------------------------------------------\33[0m" << '\n';
	cout << "\t\t\t     \033[33m|   \33[0m" << undo << "\x1B[33m   |   \33[0m" << redo << "\x1B[33m   |   \33[0m" << autoPlay << "\x1B[33m   |   EXIT[E]   | \33[0m" << '\n';
	cout << "\t\t\t     \033[33m---------------------------------------------------------\33[0m" << '\n';
	cout << "\n\n\n\n";

	int max = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (max < a[i][j])
				max = a[i][j];

	int space = to_string(max).size();
	if (space < 3) space = 3;

	string tab = "";
	for (int i = 0; i < 57 - (size / 2) * (space * 2) - (size % 2) * 2; i++)
		tab += ' ';

	cout << tab;
	for (int j = 0; j < size * space * 2 + 1; j++) {
		cout << "-";
	}
	cout << '\n';

	for (int i = 0; i < size; i++) {
		cout << tab;
		for (int j = 0; j < size; j++) {
			if (j == 0) cout << '|' << setfill(' ');
			if (a[i][j] == 0)
				cout << setfill(' ') << setw(space) << " " << setw(space) << '|' << setfill(' ');
			else
				cout << setfill(' ') << GetColor(a[i][j]) << setw(space) << a[i][j] << "\33[0m" << setw(space) << '|' << setfill(' ');
		}
		cout << '\n';
		cout << tab;
		for (int j = 0; j < size * space * 2 + 1; j++) {
			cout << "-";
		}
		cout << '\n';
	}

}

void Board::Release() {
	for (int i = 0; i < size; i++) {
		delete[]a[i];
	}

	delete[]a;
}

Stack::Stack() {
	head = NULL;
	size = 0;
}

bool Stack::Empty() {
	return (size == 0);
}

void Stack::Push(Board board) {
	Board* p = new Board(board.a, board.size, board.score, board.ptime, board.name, board.canUndo, board.canRedo, board.canAuto);

	if (head == NULL) {
		head = p;
	}
	else {
		p->next = head;
		head = p;
	}

	size++;
}

void Stack::Pop() {
	if (head != NULL) {
		Board* temp = head;
		head = head->next;
		delete temp;
		temp = NULL;
		size--;
	}
}

void Stack::Release() {
	while (head != NULL) {
		Board* temp = head;
		head = head->next;
		temp->Release();
		delete temp;
		temp = NULL;
	}
	size = 0;
}

Board Stack::Top() {
	return Board(head->a, head->size, head->score, head->ptime, head->name, head->canUndo, head->canRedo, head->canAuto);
}
