#ifndef FSM_H
#define FSM_H
#include <iostream>
#include <vector>

class FSM
{
    std::string txt;
    std::string pat;
    int M;
    int N;
    int** TF;

    void computeTF();
    int getNextState(int state, int x);

public:
    std::vector<int> occurences;
    FSM(const std::string& txt, const std::string& pat);
    ~FSM();
    void search();
};

#endif

