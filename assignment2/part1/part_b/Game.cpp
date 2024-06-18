#include "Game.h"
#ifndef GAME_CPP
#define GAME_CPP

Wizzard::Wizzard(): distance(0){}


void Game::bfs() {
    std::queue<int> q;
    q.push(exit);
    std::vector<bool> visited(size, 0);
    distances[exit] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int i = 0; i < size; ++i) {
            if (map[node][i] != 0 && !visited[i]) { // There is an edge and the node is not visited
                distances[i] = distances[node] + 1;
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

Game::Game(int**& _map, int _wizzard_1, int _wizzard_2, int _wizzard_3, int _exit, int _size, int speed_1, int speed_2, int speed_3) : map(_map), exit(_exit), size(_size), distances(size, 0) {
    wizzard_1.node = _wizzard_1;
    wizzard_2.node = _wizzard_2;
    wizzard_3.node = _wizzard_3;

    wizzard_1.speed = speed_1;
    wizzard_2.speed = speed_2;
    wizzard_3.speed = speed_3;
}

void Game::divide_by_speed() {
    if(wizzard_1.speed != 0) wizzard_1.distance = distances[wizzard_1.node] / wizzard_1.speed;
    if(wizzard_2.speed != 0) wizzard_2.distance = distances[wizzard_2.node] / wizzard_2.speed;
    if(wizzard_3.speed != 0) wizzard_3.distance = distances[wizzard_3.node] / wizzard_3.speed;
}

Wizzard& Game::choose_winner() {
    if (wizzard_1.distance < wizzard_2.distance) {
        if (wizzard_1.distance < wizzard_3.distance) {
            return wizzard_1;
        }
        else {
            return wizzard_3;
        }
    }
    else {
        if (wizzard_2.distance < wizzard_3.distance) {
            return wizzard_2;
        }
        else {
            return wizzard_3;
        }
    }
}

void Game::run() {
    bfs();
    divide_by_speed();
    Wizzard winner(choose_winner());
    std::cout << "The wizzard on the position " << winner.node << " is winner" << std::endl;
    std::cout << wizzard_1.distance << " " << wizzard_2.distance << " " << wizzard_3.distance << " " << std::endl;

}




#endif