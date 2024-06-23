#include <iostream>
#include "FSM.h"

int main()
{
    std::string txt = "AABAACAADAABAAABAA";
    std::string pat = "AABA";
    FSM fsm(txt, pat);
    fsm.search();
    for (auto i : fsm.occurences) {
        std::cout << i << " ";
    }
    return 0;
}





