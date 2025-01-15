#include "Header.h"
#include "Player.h"

Player::Player() {
	name = "unkown";
	size = 0;
	score = 0;
	board = NULL;
	next = NULL;
}

Player::Player(string name, int score, float ptime) {
	this->name = name;
	this->score = score;
	this->ptime = ptime;
	this->size = 0;
	this->board = NULL;
	this->next = NULL;
}

Player::Player(string name, int score, float ptime, int size, int** board) {
	this->name = name;
	this->score = score;
	this->ptime = ptime;
	this->size = size;
	
	this->board = new int* [size];
	for (int i = 0; i < size; i++)
		this->board[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			this->board[i][j] = board[i][j];

	this->next = NULL;
}

void Player::Release() {
	if (board != NULL) {
		for (int i = 0; i < size; i++)
			delete[] board[i];

		delete[]board;
	}
}

SavedPlayersList::SavedPlayersList() {
	head = NULL;
	size = 0;
}

void SavedPlayersList::Add(Player* player) {

	if (head == NULL) {
		head = player;
	}
	else {
		Player* last = head;
		while (last->next != NULL)
			last = last->next;

		last->next = player;
	}

	size++;
}

void SavedPlayersList::Insert(Player* player, int index) {

	if (index == 1) {
		player->next = head;
		head = player;
	}
	else {
		int i = 1;
		Player* temp = head;
		while (temp->next != NULL && i + 1 != index) {
			temp = temp->next;
			i++;
		}

		player->next = temp->next;
		temp->next = player;
	}

	size++;
}

void SavedPlayersList::Delete(int index) {
	if (head == NULL && size <= 0) return;

	if (index == 1) {
		Player* temp = head;
		head = head->next;
		temp->Release();
		delete temp;
		temp = NULL;
	}
	else {
		Player* temp = head;
		int i = 1;
		while (temp->next != NULL && i + 1 != index) {
			temp = temp->next;
			i++;
		}
			
		
		Player* p = temp->next;
		temp->next = temp->next->next;
		p->Release();
		delete p;
		p = NULL;
	}
	size--;
}

void SavedPlayersList::LoadFromFile(string fileName) {
	fstream rdata(fileName, ios::binary | ios::in);
	
	string name;
	int nameSize;
	int score;
	int size;
	float ptime;
	
	while (rdata.read((char*)&nameSize, sizeof(int))) {
		name.resize(nameSize);
		rdata.read(&name[0], nameSize);
		rdata.read((char*)&score, sizeof(int));
		rdata.read((char*)&ptime, sizeof(float));
		rdata.read((char*)&size, sizeof(int));

		int** board = new int* [size];
		for (int i = 0; i < size; i++)
			board[i] = new int[size];

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				rdata.read((char*)&board[i][j], sizeof(int));
				board[i][j] -= 170105;
			}
		}


		Player* p = new Player(name, score + 170105, ptime, size, board);

		Add(p);

		for (int i = 0; i < size; i++)
			delete[] board[i];
		delete[] board;
	}

	rdata.close();
}

void SavedPlayersList::SaveToFile(string fileName) {
	fstream wdata(fileName, ios::binary | ios::out);

	for (Player* i = head; i != NULL; i = i->next) {

		i->score -= 170105;

		int nameSize = i->name.size();

		wdata.write((char*)&nameSize, sizeof(int));
		wdata.write(i->name.c_str(), nameSize);
		wdata.write((char*)&i->score, sizeof(int));
		wdata.write((char*)&i->ptime, sizeof(float));
		wdata.write((char*)&i->size, sizeof(int));

		for (int j = 0; j < i->size; j++) {
			for (int k = 0; k < i->size; k++) {
				i->board[j][k] += 170105;
				wdata.write((char*)&i->board[j][k], sizeof(int));
			}
		}
	}

	wdata.close();
}

void SavedPlayersList::Release() {
	while (head != NULL) {
		Player* temp = head;
		head = head->next;
		temp->Release();
		delete temp;
		temp = NULL;
	} 
}

Top20List::Top20List() {
	head = NULL;
	size = 0;
}

void Top20List::Add(Player* player) {
	
	if (head == NULL) {
		head = player;
	}
	else if (head->score == player->score) {
		if (head->ptime >= player->ptime) {
			player->next = head;
			head = player;
		}
		else {
			player->next = head->next;
			head->next = player;
		}
	}
	else if (head->score < player->score) {
		player->next = head;
		head = player;
	}
	else {
		Player* last = head;
		while (last->next != NULL) {
			if (last->next->score < player->score)
				break;
			else if (last->next->score == player->score)
				if (last->next->ptime >= player->ptime)
					break;

			last = last->next;
		}
			
		player->next = last->next;
		last->next = player;
	}

	size++;
}

void Top20List::LoadFromFile(string fileName) {
	fstream rdata(fileName, ios::binary | ios::in);

	string name;
	int nameSize;
	int score;
	float ptime;

	while (rdata.read((char*)&nameSize, sizeof(int))) {
		name.resize(nameSize);
		rdata.read(&name[0], nameSize);
		rdata.read((char*)&score, sizeof(int));
		rdata.read((char*)&ptime, sizeof(float));
		
		Player* p = new Player(name, score + 170105, ptime);

		Add(p);
	}

	rdata.close();
}

void Top20List::SaveToFile(string fileName) {
	fstream wdata(fileName, ios::binary | ios::out);

	for (Player* i = head; i != NULL; i = i->next) {
		int nameSize = i->name.size();
		i->score -= 170105;

		wdata.write((char*)&nameSize, sizeof(int));
		wdata.write(i->name.c_str(), nameSize);
		wdata.write((char*)&i->score, sizeof(int));
		wdata.write((char*)&i->ptime, sizeof(float));
	}

	wdata.close();
}

void Top20List::Release() {
	while (head != NULL) {
		Player* temp = head;
		head = head->next;
		temp->Release();
		delete temp;
		temp = NULL;
	}
}

void DisplayTopPlayer() {
	bool quit = false;
	
	Top20List topPlayer;
	topPlayer.LoadFromFile("Top20.bin");

	
	system("cls");
	cout << "\t\t\t     \033[93m /$$$$$$$$ /$$$$$$  /$$$$$$$         /$$$$$$   /$$$$$$ \033[0m" << '\n';
	cout << "\t\t\t     \033[93m|__  $$__//$$__  $$| $$__  $$       /$$__  $$ /$$$_  $$\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   | $$  | $$  \\ $$| $$  \\ $$      |__/  \\ $$| $$$$\\ $$\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   | $$  | $$  | $$| $$$$$$$/        /$$$$$$/| $$ $$ $$\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   | $$  | $$  | $$| $$____/        /$$____/ | $$\\ $$$$\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   | $$  | $$  | $$| $$            | $$      | $$ \\ $$$\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   | $$  |  $$$$$$/| $$            | $$$$$$$$|  $$$$$$/\033[0m" << '\n';
	cout << "\t\t\t     \033[93m   |__/   \\______/ |__/            |________/ \\______/ \033[0m" << '\n';
	cout << "\n\n\n\n";

	string tab = "";
	for (int i = 0; i < 35; i++)
		tab += ' ';

	cout << tab << "NAME" << setw(21) << "SCORE" << setw(21)  << "TIME" << '\n';
	int j = 1;
	for (Player* i = topPlayer.head; i != NULL; i = i->next) {
		if (j > 20)
			break;
		if (j == 1) 
				cout << tab << "\033[6;38;5;15;48;5;1m" << '[' << j << ']' << i->name << setw(23 - i->name.size() - to_string(j).size()) << setfill('.') << i->score << setw(20) << i->ptime << 's' << "\033[0m" << '\n';
		else if (j == 2)
			cout << tab << "\033[38;5;15;48;5;2m" << '[' << j << ']' << i->name << setw(23 - i->name.size() - to_string(j).size()) << setfill('.') << i->score << setw(20) << i->ptime << 's' << "\033[0m" << '\n';
		else if (j == 3) 
			cout << tab << "\033[38;5;15;48;5;3m" << '[' << j << ']' << i->name << setw(23 - i->name.size() - to_string(j).size()) << setfill('.') << i->score << setw(20) << i->ptime << 's' << "\033[0m" << '\n';
		else 
			cout << tab << "\033[33m" << '[' << j << ']' << i->name << setw(23 - i->name.size() - to_string(j).size()) << setfill('.') << i->score << setw(20) << i->ptime << 's' << "\033[0m" << '\n';
		j++;
	}

	
	while (!quit) {
		char key = _getch();

		if (key == 'e')
			quit = true;
		
		
	}

	system("cls");
	topPlayer.Release();
}