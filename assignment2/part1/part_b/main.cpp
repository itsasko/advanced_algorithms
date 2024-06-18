#include <iostream>
#include "Game.h"

int main()
{
    int size = 6;
    int** map1 = new int* [size];
    for (int i = 0; i < size; ++i) {
        map1[i] = new int[size] {0};
    }

    map1[0][1] = map1[1][0] = 1;
    map1[1][2] = map1[2][1] = 1;
    map1[2][3] = map1[3][2] = 1;
    map1[3][4] = map1[4][3] = 1;
    map1[4][5] = map1[5][4] = 1;

    int wizzard_1 = 0;
    int wizzard_2 = 2;
    int wizzard_3 = 4;
    int exit = 5;
    int speed_1 = 1;
    int speed_2 = 1;
    int speed_3 = 1;

    Game game1(map1, wizzard_1, wizzard_2, wizzard_3, exit, size, speed_1, speed_2, speed_3);
    game1.run();

    for (int i = 0; i < size; ++i) {
        delete[] map1[i];
    }
    delete[] map1;
    size = 6;
    int** map2 = new int* [size];
    for (int i = 0; i < size; ++i) {
        map2[i] = new int[size] {0};
    }

    map2[0][1] = map2[1][0] = 1;
    map2[1][2] = map2[2][1] = 1;
    map2[1][3] = map2[3][1] = 1;
    map2[3][4] = map2[4][3] = 1;
    map2[4][5] = map2[5][4] = 1;

    wizzard_1 = 0;
    wizzard_2 = 1;
    wizzard_3 = 3;
    exit = 5;
    speed_1 = 1;
    speed_2 = 2;
    speed_3 = 1;

    Game game2(map2, wizzard_1, wizzard_2, wizzard_3, exit, size, speed_1, speed_2, speed_3);
    game2.run();

    for (int i = 0; i < size; ++i) {
        delete[] map2[i];
    }
    delete[] map2;
    size = 6;
    int** map3 = new int* [size];
    for (int i = 0; i < size; ++i) {
        map3[i] = new int[size] {0};
    }

    map3[0][1] = map3[1][0] = 1;
    map3[1][2] = map3[2][1] = 1;
    map3[2][3] = map3[3][2] = 1;
    map3[3][4] = map3[4][3] = 1;
    map3[4][5] = map3[5][4] = 1;
    map3[5][0] = map3[0][5] = 1;

    wizzard_1 = 0;
    wizzard_2 = 2;
    wizzard_3 = 5;
    exit = 3;
    speed_1 = 1;
    speed_2 = 1;
    speed_3 = 2;

    Game game3(map3, wizzard_1, wizzard_2, wizzard_3, exit, size, speed_1, speed_2, speed_3);
    game3.run();

    for (int i = 0; i < size; ++i) {
        delete[] map3[i];
    }
    delete[] map3;
    size = 8;
    int** map4 = new int* [size];
    for (int i = 0; i < size; ++i) {
        map4[i] = new int[size] {0};
    }

    map4[0][1] = map4[1][0] = 1;
    map4[0][4] = map4[4][0] = 1;
    map4[1][5] = map4[5][1] = 1;
    map4[2][3] = map4[3][2] = 1;
    map4[2][6] = map4[6][2] = 1;
    map4[3][7] = map4[7][3] = 1;

    wizzard_1 = 0;
    wizzard_2 = 2;
    wizzard_3 = 6;
    exit = 3;
    speed_1 = 1;
    speed_2 = 1;
    speed_3 = 1;

    Game game4(map4, wizzard_1, wizzard_2, wizzard_3, exit, size, speed_1, speed_2, speed_3);
    game4.run();

    for (int i = 0; i < size; ++i) {
        delete[] map4[i];
    }
    delete[] map4;
    size = 9;
    int** map5 = new int* [size];
    for (int i = 0; i < size; ++i) {
        map5[i] = new int[size] {0};
    }

    map5[0][1] = map5[1][0] = 1;
    map5[1][2] = map5[2][1] = 1;
    map5[0][3] = map5[3][0] = 1;
    map5[1][4] = map5[4][1] = 1;
    map5[2][5] = map5[5][2] = 1;
    map5[3][4] = map5[4][3] = 1;
    map5[4][5] = map5[5][4] = 1;
    map5[3][6] = map5[6][3] = 1;
    map5[4][7] = map5[7][4] = 1;
    map5[5][8] = map5[8][5] = 1;
    map5[6][7] = map5[7][6] = 1;
    map5[7][8] = map5[8][7] = 1;

    wizzard_1 = 0;
    wizzard_2 = 4;
    wizzard_3 = 8;
    exit = 5;
    speed_1 = 1;
    speed_2 = 2;
    speed_3 = 1;

    Game game5(map5, wizzard_1, wizzard_2, wizzard_3, exit, size, speed_1, speed_2, speed_3);
    game5.run();

    for (int i = 0; i < size; ++i) {
        delete[] map5[i];
    }
    delete[] map5;


}
