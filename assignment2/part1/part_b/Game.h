#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <queue>

class Wizzard {
public:
	Wizzard();
	float node;
	float distance;
	float speed;
};

class Game
{
	int**& map;
	int size;
	Wizzard wizzard_1;
	Wizzard wizzard_2;
	Wizzard wizzard_3;

	std::vector<int> distances;

	Wizzard& choose_winner();

	int exit;

	std::string winner;
	void bfs();
	void divide_by_speed();

public:
	Game(int**& _map, int _wizzard_1, int _wizzard_2, int _wizzard_3, int _exit, int size, int speed_1, int speed_2, int speed_3);
	void run();
};

#endif

