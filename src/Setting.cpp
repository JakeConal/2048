
#include "Header.h"
#include "Setting.h"

using namespace std;

void DisplaySetting(int& size, bool& canUndo, bool& canRedo, bool& canAuto) {
	system("cls");

	string undo = canUndo ? "UNDO: ON" : "UNDO: OFF";
	string redo = canRedo ? "REDO: ON" : "REDO: OFF";
	string autoPlay = canAuto ? "AUTO: ON" : "AUTO: OFF";
	string reSize = "SIZE: " + to_string(size);
	int option = 1;
	bool quit = false;

	while (!quit) {
		system("cls");
		
		cout << "\t\t\t\x1B[93m  /$$$$$$  /$$$$$$$$ /$$$$$$$$ /$$$$$$$$ /$$$$$$ /$$   /$$  /$$$$$$ \x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m /$$__  $$| $$_____/|__  $$__/|__  $$__/|_  $$_/| $$$ | $$ /$$__  $$\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m| $$  \\__/| $$         | $$      | $$     | $$  | $$$$| $$| $$  \\__/\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m|  $$$$$$ | $$$$$      | $$      | $$     | $$  | $$ $$ $$| $$ /$$$$\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m \\____  $$| $$__/      | $$      | $$     | $$  | $$  $$$$| $$|_  $$\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m /$$  \\ $$| $$         | $$      | $$     | $$  | $$\\  $$$| $$  \\ $$\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m|  $$$$$$/| $$$$$$$$   | $$      | $$    /$$$$$$| $$ \\  $$|  $$$$$$/\x1B[0m" << '\n';
		cout << "\t\t\t\x1B[93m \\______/ |________/   |__/      |__/   |______/|__/  \\__/ \\______/ \x1B[0m" << '\n';

		cout << "\n\n\n\n";

		cout << "\t\t\t\t\t ----------====****====----------\n\n";
		if (option == 1) 
			cout << "\t\t\t\t\t\t\x1B[33m  -* " << undo << " *-\33[0m\n\n";
		else cout << "\t\t\t\t\t\t     " << undo << "\n\n";

		if (option == 2)
			cout << "\t\t\t\t\t\t\x1B[33m  -* " << redo << " *-\33[0m\n\n";
		else cout << "\t\t\t\t\t\t     " << redo << "\n\n";

		if (option == 3)
			cout << "\t\t\t\t\t\t\x1B[33m  -* " << autoPlay << " *-\33[0m\n\n";
		else cout << "\t\t\t\t\t\t     " << autoPlay << "\n\n";

		if (option == 4)
			cout << "\t\t\t\t\t\t\x1B[33m  -* " << reSize << "   *-\33[0m\n\n";
		else cout << "\t\t\t\t\t\t     " << reSize << "\n\n";

		if (option == 5)
			cout << "\t\t\t\t\t\t\x1B[33m  -* EXIT     *-\33[0m\n\n";
		else cout << "\t\t\t\t\t\t     EXIT \n\n";
		cout << "\t\t\t\t\t ----------====****====----------\n\n";

		char key = _getch();

		if (key == 'w' && option > 1)
			option--;
		else if (key == 's' && option < 5)
			option++;
		else {
			switch (option) {
			case 1:
				if (key == 'a' || key == 'd' || key == ' ')
					canUndo = !canUndo;
				break;
			case 2:
				if (key == 'a' || key == 'd' || key == ' ')
					canRedo = !canRedo;
				break;
			case 3:
				if (key == 'a' || key == 'd' || key == ' ')
					canAuto = !canAuto;
				break;
			case 4:
				if (key == 'a' && size > 4)
					size--;
				else if (key == 'd' && size < 10)
					size++;
				break;
			case 5:
				if (key == 'a' || key == 'd' || key == ' ')
					quit = !quit;
				break;
			}
		}
		

		undo = canUndo ? "UNDO: ON" : "UNDO: OFF";
		redo = canRedo ? "REDO: ON" : "REDO: OFF";
		autoPlay = canAuto ? "AUTO: ON" : "AUTO: OFF";
		reSize = "SIZE: " + to_string(size);
	}
}