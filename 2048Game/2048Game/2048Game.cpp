#include "Board.h"
#include "Game.h"
#include "Menu.h"
#include "Header.h"
#include "Graphic.h"
#include "Setting.h"
#include "Player.h"

int main() {
	ShowCur(false);
	int size = 4;
	bool canUndo = false;
	bool canRedo = false;
	bool canAuto = false;

	DisplayMenu(size, canUndo, canRedo, canAuto);

	return 0;
}