#include "Header.h"
#include "Menu.h"
#include "Game.h"
#include "Board.h"
#include "Setting.h"
#include "Player.h"

void DisplayMenu(int& size, bool& canUndo, bool& canRedo, bool& canAuto) {

	int option = 1;

	bool quit = false;

	while (!quit) {
		system("cls");
		cout << "\n\n";
		cout << "\t\t\t\t     \033[93m  /$$$$$$   /$$$$$$  /$$   /$$  /$$$$$$ \033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m /$$__  $$ /$$$_  $$| $$  | $$ /$$__  $$\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m|__/  \\ $$| $$$$\\ $$| $$  | $$| $$  \\ $$\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m  /$$$$$$/| $$ $$ $$| $$$$$$$$|  $$$$$$/\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m /$$____/ | $$\\ $$$$|_____  $$ >$$__  $$\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m| $$      | $$ \\ $$$      | $$| $$  \\ $$\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m| $$$$$$$$|  $$$$$$/      | $$|  $$$$$$/\033[0m" << '\n';
		cout << "\t\t\t\t     \033[93m|________/ \\______/       |__/ \\______/ \033[0m" << '\n';
		cout << "\n\n\n";

		SavedPlayersList savedPlayer;
		savedPlayer.LoadFromFile("SavedPlayers.bin");
		int player = savedPlayer.size;
		savedPlayer.Release();

		cout << "\t\t\t\t\t ----------====****====----------\n\n";
		if (option == 1)
			cout << "\t\t\t\t\t\t \x1B[33m-*  NEW GAME  *-\33[0m\n\n";
		else
			cout << "\t\t\t\t\t\t     NEW GAME\n\n";

		if (option == 2 && player > 0)
			cout << "\t\t\t\t\t\t \x1B[33m-*   RESUME   *-\33[0m\n\n";
		else if (option == 2 && player == 0)
			cout << "\t\t\t\t\t\t \x1B[90m-*   RESUME   *-\33[0m\n\n";
		else if (player == 0)
			cout << "\t\t\t\t\t\t   \x1B[90m   RESUME  \33[0m\n\n";
		else 
			cout << "\t\t\t\t\t\t      RESUME\n\n";

		if (option == 3)
			cout << "\t\t\t\t\t\t \x1B[33m-* TOP20 LIST *-\33[0m\n\n";
		else
			cout << "\t\t\t\t\t\t    TOP20 LIST\n\n";

		if (option == 4)
			cout << "\t\t\t\t\t\t \x1B[33m-*  SETTINGS  *-\33[0m\n\n";
		else
			cout << "\t\t\t\t\t\t     SETTINGS\n\n";
		cout << "\t\t\t\t\t ----------====****====----------\n";


		//get option
		char key = _getch();

		if (key == 'w' && option > 1) {
			option--;
		}
		else if (key == 's' && option < 4) {
			option++;
		}
		else if (key == ' ') {
			switch (option) {
			case 1:
				NewGame(size, canUndo, canRedo, canAuto);
				break;
			case 2:
				if (player > 0)
					Resume(canUndo, canRedo, canAuto);
				break;
			case 3:
				DisplayTopPlayer();
				break;
			case 4:
				DisplaySetting(size, canUndo, canRedo, canAuto);
				break;
			}
		}
	}

	system("cls");
}
