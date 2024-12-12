#pragma once
#include <string>

struct Player {
	std::string name;

	int score;
	int size;
	int** board;
	
	float ptime;

	Player* next;

	Player();
	Player(std::string name, int score, float ptime);
	Player(std::string name, int score, float ptime, int size, int** board);

	void Release();
};

//store 5 players
struct SavedPlayersList {
	Player* head;
	
	int size;

	SavedPlayersList();

	void Add(Player* player);
	void Insert(Player* player, int index);
	void Delete(int index);
	void LoadFromFile(std::string fileName);
	void SaveToFile(std::string fileName);
	void Release();
};

//store 20 players with highest score
struct Top20List {
	Player* head;

	int size;

	Top20List();

	void Add(Player* player);
	void LoadFromFile(std::string fileName);
	void SaveToFile(std::string fileName);
	void Release();
};

void DisplayTopPlayer();