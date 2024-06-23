#ifndef BRUTE_FORCE
#define BRUTE_FORCE


#include <iostream>
#include <string>
#include <vector>


std::vector<size_t> BruteForce(const std::string& t, const std::string& p) {
    size_t n = t.size();
    size_t m = p.size();

    std::vector<size_t> ind;

    for (size_t i = 0; i <= n - m; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            if (t[i + j] != p[j]) {
                break;
            }
        }
        if (j == m) {
            ind.push_back(i);
        }
    }
    return ind;
}


#endif