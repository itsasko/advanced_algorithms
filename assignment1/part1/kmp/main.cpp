#include <iostream>
#include "KMP.H"

int main()
{
    std::string txt = "AABAACAADAABAAABAA";
    std::string pat = "AABA";
    KMP kmp(pat, txt);
    kmp.search();

    for (int index : kmp.occurences) {
        std::cout << "Pattern found at index " << index << std::endl;
    }
    return 0;

}

