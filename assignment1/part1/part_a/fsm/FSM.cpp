#include "FSM.h"


FSM::FSM(const std::string& txt, const std::string& pat)
    : txt(txt), pat(pat)
{
    M = pat.size();
    N = txt.size();
    TF = new int* [M + 1];
    for (int i = 0; i <= M; ++i)
    {
        TF[i] = new int[256];
    }
}

FSM::~FSM()
{
    for (int i = 0; i <= M; ++i)
    {
        delete[] TF[i];
    }
    delete[] TF;
}

void FSM::computeTF()
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < 256; ++x)
            TF[state][x] = getNextState(state, x);
}

int FSM::getNextState(int state, int x)
{
    if (state < M && x == pat[state])
        return state + 1;
    int ns, i;
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns - 1] == x)
        {
            for (i = 0; i < ns - 1; i++)
                if (pat[i] != pat[state - ns + 1 + i])
                    break;
            if (i == ns - 1)
                return ns;
        }
    }

    return 0;
}


void FSM::search()
{
    computeTF();

    int i, state = 0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
            occurences.push_back(i - M + 1);
    }
}