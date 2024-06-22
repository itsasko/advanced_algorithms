#include <iostream>
#include <string>
#include <vector>

bool match(const std::string& text, const std::string& pat, size_t n, size_t m, size_t ti, size_t pi) {
    while (ti < n && pi < m) {
        if (pat[pi] == '\\' && pi + 1 < m) {
            pi++;
            if (pat[pi] != text[ti]) {
                return false;
            }
        }
        else if (pat[pi] == '?') {
        }
        else if (pat[pi] == '*') {
            if (pi + 1 == m) {
                return true;
            }
            while (ti < n) {
                if (match(text, pat, n, m, ti, pi + 1)) {
                    return true;
                }
                ti++;
            }
            return false;
        }
        else {
            if (pat[pi] != text[ti]) {
                return false;
            }
        }
        ti++;
        pi++;
    }

    while (pi < m && pat[pi] == '*') {
        pi++;
    }

    return pi == m;
}

std::vector<size_t> BruteForce(const std::string& T, const std::string& P) {
    size_t n = T.size();
    size_t m = P.size();

    std::vector<size_t> ind;

    for (size_t i = 0; i <= n - m; i++) {
        if (match(T, P, n, m, i, 0)) {
            ind.push_back(i);
        }
    }
    return ind;
}

int main() {
    std::string text, pattern;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    std::cout << "Enter pattern: ";
    std::getline(std::cin, pattern);

    std::vector<size_t> indices = BruteForce(text, pattern);

    if (!indices.empty()) {
        std::cout << "Pattern found at indices: ";
        for (size_t index : indices) 
            std::cout << index << " ";
    }
    else 
        std::cout << "Pattern not found" << std::endl;
}
