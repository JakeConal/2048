#include "Header.h"
#include "Game.h"
#include "Menu.h"
#include "Graphic.h"
#include "Auto.h"

bool IsWon(Board board) {
	for (int i = 0; i < board.size; i++)
		for (int j = 0; j < board.size; j++)
			if (board.a[i][j] == 2048)
				return true;
	return false;
}

bool IsLost(Board board) {
	return (!board.CanMoveHorizontally() && !board.CanMoveVertically());
}

bool IsGameOver(Board board, bool& isLost, bool& isWon, bool& isContinue, bool& quit, Top20List topPlayer) {
	
	isWon = IsWon(board);
	isLost = IsLost(board);

	if (isWon && !isContinue) {

		//check rank
		int rank = 1;
		for (Player* i = topPlayer.head; i != NULL; i = i->next) {
			if (i->score < board.score)
				break;
			rank++;
		}
		

		//announce win
		GoTo(49, 9);
		cout << "\033[32;1m---==YOU WON==---\033[0m";
		GoTo(53, 10);
		if (rank <= 20) 
			cout << "\033[32;1m*RANK " << rank << "*\033[0m";
		else 
			cout << "\033[32;1m*UNRANK*\033[0m";
			
		//ask continue
		GoTo(42, 11);
		cout << "\033[93;6mDo you want to continue? [Y/N]\033[0m";
		
		while (true) {
			char key = _getch();
			if (key == 'y') {
				isContinue = true;
				system("cls");
				board.Display();
				break;
			}
			else if (key == 'n') {
				isContinue = false;
				quit = true;
				break;
			}
		}
	}

	else if (isLost) {

		//check rank
		int rank = 1;
		for (Player* i = topPlayer.head; i != NULL; i = i->next) {
			if (i->score < board.score)
				break;
			rank++;
		}

		//announce lose
		GoTo(48, 9);
		cout << "\033[31;1m---==GAME OVER==---\033[0m";
		GoTo(53, 10);
		if (rank <= 20)
			cout << "\033[31;1m*RANK " << rank << "*\033[0m";
		else
			cout << "\033[31;1m*UNRANK*\033[0m";

		//if can undo then ask continue else exit
		if (board.canUndo) {
			GoTo(36, 11);
			cout << "\033[93;6mDo you want to undo your move or exit? [U/E]\033[0m";
		}
		else {
			GoTo(50, 11);
			cout << "\033[93;6mPress E to exit\033[0m";
		}
	}

	return (isWon && !isContinue) || isLost;
}

bool isValidName(string name, Top20List topPlayer, SavedPlayersList savedPlayer) {
	if (name.size() > 17) return false;

	for (int i = 0; i < name.size(); i++) {
		if (isdigit(name[i]) || isalpha(name[i]))
			continue;
		else
			return false;
	}


	for (Player* i = savedPlayer.head; i != NULL; i = i->next) {
		if (name == i->name)
			return false;
	}

	int j = 1;
	for (Player* i = topPlayer.head; i != NULL; i = i->next) {
		if (j > 20) break;
		if (name == i->name)
			return false;
		j++;
	}

	return true;
}

void CheckGameInput(Board& board, Stack& prev, Stack& next, bool& isLost, bool& isWon, bool& isContinue, bool& quit, Top20List topPlayer) {

	char key = _getch();

	if (key == 'a' && board.CanMoveHorizontally()) {
		system("cls");
		prev.Push(board);
		next.Release();
		board.MoveLeft();
		board.GenNum();
		board.Display();
	}
	else if (key == 'd' && board.CanMoveHorizontally()) {
		system("cls");
		prev.Push(board);
		next.Release();
		board.MoveRight();
		board.GenNum();
		board.Display();
	}
	else if (key == 'w' && board.CanMoveVertically()) {
		system("cls");
		prev.Push(board);
		next.Release();
		board.MoveUp();
		board.GenNum();
		board.Display();
	}
	else if (key == 's' && board.CanMoveVertically()) {
		system("cls");
		prev.Push(board);
		next.Release();
		board.MoveDown();
		board.GenNum();
		board.Display();
	}
	else if (key == 'u' && prev.size != 0 && board.canUndo) {
		system("cls");
		next.Push(board);
		board = prev.Top();
		prev.Pop();
		board.Display();
	}
	else if (key == 'r' && next.size != 0 && board.canRedo) {
		system("cls");
		prev.Push(board);
		board = next.Top();
		next.Pop();
		board.Display();
	}
	else if (key == 'h' && board.canAuto) {
		AutoPlay(board, prev, next, isWon, isLost, isContinue, quit, topPlayer);
	}
	else if (key == 'e') {
		GoTo(37, 11);
		cout << "\r" << std::string(80, ' ') << "\r";

		GoTo(40, 11);
		cout << "\033[93;6mAre you sure you want to exit? [Y/N]\033[0m";
		
		while (true) {
			char key = _getch();
			if (key == 'y') {
				quit = true;
				break;
			}
			else if (key == 'n') {
				system("cls");
				board.Display();
				break;
			}
		}
	}
}

void NewGame(int size, bool canUndo, bool canRedo, bool canAuto) {
	system("cls");
	
	SavedPlayersList savedPlayer;
	Top20List topPlayer;

	savedPlayer.LoadFromFile("SavedPlayers.bin");
	topPlayer.LoadFromFile("Top20.bin");

	Board board(size);
	Stack prev, next;
	string name;

	bool quit = false;
	bool isLost = false;
	bool isWon = false;
	bool isContinue = false;

	board.canUndo = canUndo;
	board.canRedo = canRedo;
	board.canAuto = canAuto;

	//get name
	while (true) {
		GoTo(38, 9);
		cout << "\033[90m*Does not include special characters*\033[0m";
		GoTo(42, 10);
		cout << "\033[90m*Name length shorter than 17*\033[0m";


		GoTo(47, 6);
		cout << "Enter your name:\n ";
		GoTo(50, 7);
		getline(cin, name);
		if (!isValidName(name, topPlayer, savedPlayer))
		{
			GoTo(38, 7);
			cout << "Your name has been taken or invalid";
			Sleep(1000);
		}
		else break;

		system("cls");
 	}
	
	
	board.name = name;

	system("cls");

	//start game
	board.Display();

	const clock_t begin_time = clock();
	while (!quit) {
		CheckGameInput(board, prev, next, isLost, isWon, isContinue, quit, topPlayer);
		IsGameOver(board, isLost, isWon, isContinue, quit, topPlayer);
	}
	board.ptime = float(clock() - begin_time) / CLOCKS_PER_SEC;

	//save game
	if ((!isWon || isContinue) && !isLost) {
		SaveGame(board, savedPlayer);
	} 
	else {
		Player* p = new Player(board.name, board.score, board.ptime);
		topPlayer.Add(p);
	}

	savedPlayer.SaveToFile("SavedPlayers.bin");
	topPlayer.SaveToFile("Top20.bin");

	//delete pointer
	savedPlayer.Release();
	topPlayer.Release();
	board.Release();
	prev.Release();
	next.Release();

	system("cls");
}

void Resume(bool canUndo, bool canRedo, bool canAuto) {

	SavedPlayersList savedPlayer;
	Top20List topPlayer;

	savedPlayer.LoadFromFile("SavedPlayers.bin");
	topPlayer.LoadFromFile("Top20.bin");

	char key = '1';
	int option = 1;

	//get account
	while (key != ' ') {
		
		system("cls");
		cout << "\n\n\n";
		cout << "\t\t\t\t\t\033[38;5;34m    ----==*CHOOSE AN ACCOUNT*==----\033[0m";
		cout << "\n\n\n";
		
		
		cout << "\t\t\t\t\t\t\033[38;5;106m " << "NAME" << setw(17) << setfill(' ') << "SCORE" << '\n';

		int j = 1;
		for (Player* i = savedPlayer.head; i != NULL; i = i->next) {
			if (j == option)
				cout << "\t\t\t\t\t\033[38;5;142m      " << "-* " << i->name << setw(21 - i->name.size()) << setfill('.') << i->score << " *-" << '\n';
			else
				cout << "\t\t\t\t\t\033[38;5;142m         " << i->name << setw(21 - i->name.size()) << setfill('.') << i->score << '\n';

			j++;
		}

		key = _getch();

		if (key == 'w' && option > 1) 
			option--;
		else if (key == 's' && option < 5 && option < savedPlayer.size) 
			option++;
		else if (key == ' ') 
			break;
		
	}


	Player* p = savedPlayer.head;
	int index = 1;
	while (p->next != NULL && index != option) {
		p = p->next;
		index++;
	}
		

	Board board(p->board, p->size, p->score, p->ptime, p->name, canUndo, canRedo, canAuto);
	Stack prev, next;
	bool quit = false;
	bool isLost = false;
	bool isWon = false;
	bool isContinue = false;

	system("cls");

	//start game
	board.Display();

	const clock_t begin_time = clock();
	while (!quit) {
		CheckGameInput(board, prev, next, isLost, isWon, isContinue, quit, topPlayer);
		IsGameOver(board, isLost, isWon, isContinue, quit, topPlayer);
	}
	board.ptime += float(clock() - begin_time) / CLOCKS_PER_SEC;

	//save game
	if ((isWon && !isContinue) || isLost) {
		savedPlayer.Delete(option);
		Player* player = new Player(board.name, board.score, board.ptime);
		topPlayer.Add(player);
	}
	else {
		for (int i = 0; i < board.size; i++)
			for (int j = 0; j < board.size; j++)
				p->board[i][j] = board.a[i][j];

		p->score = board.score;
		p->ptime = board.ptime;
	}
	

	savedPlayer.SaveToFile("SavedPlayers.bin");
	topPlayer.SaveToFile("Top20.bin");

	//delete pointer
	savedPlayer.Release();
	topPlayer.Release();
	board.Release();
	prev.Release();
	next.Release();

	system("cls");
}

void SaveGame(Board board, SavedPlayersList& savedPlayer) {
	Player* p = new Player(board.name, board.score, board.ptime, board.size, board.a);
	
	if (savedPlayer.size < 5) {
		savedPlayer.Add(p);
	}
	else {
		char key = '1';
		int option = 1;

		while (key != ' ') {
			system("cls");
			cout << "\n\n\n";
			cout << "\t\t\t\t\t\033[38;5;34m   ----==*SELECT 1 SLOT TO SAVE*==----\033[0m";
			cout << "\n\n\n";


			cout << "\t\t\t\t\t\t\033[38;5;106m " << "NAME" << setw(17) << setfill(' ') << "SCORE" << '\n';

			int j = 1;
			for (Player* i = savedPlayer.head; i != NULL; i = i->next) {
				if (j == option)
					cout << "\t\t\t\t\t\033[38;5;142m      " << "-* " << i->name << setw(21 - i->name.size()) << setfill('.') << i->score << " *-" << '\n';
				else
					cout << "\t\t\t\t\t\033[38;5;142m         " << i->name << setw(21 - i->name.size()) << setfill('.') << i->score << '\n';

				j++;
			}
			
			key = _getch();

			if (key == 'w' && option > 1) {
				option--;
			}
			else if (key == 's' && option < 5) {
				option++;
			}
			else if (key == ' ') {
				savedPlayer.Delete(option);
				savedPlayer.Insert(p, option);
			}
		}
	}
}