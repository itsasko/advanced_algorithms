#include <iostream>
#include <string>
#include <vector>


bool match(const std::string& pat, const std::string& _t, size_t m, size_t n, size_t ti, size_t pi) {
    while (ti < n && pi < m) {
        if (pat[pi] == '\\' && pi + 1 < m) {
            pi++;
            if (pat[pi] != _t[ti]) {
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
                if (match(pat, _t, m, n, ti, pi + 1)) {
                    return true;
                }
                ti++;
            }
            return false;
        }
        else {
            if (pat[pi] != _t[ti]) {
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

std::vector<size_t> Sunday(const std::string& P, const std::string& T) {
    size_t n = T.size();
    size_t m = P.size();

    std::vector<size_t> ind;

    if (m == 0) return ind;

    std::vector<size_t> skip(128, m + 1);

    for (size_t j = 0; j < m; j++) {
        skip[static_cast<unsigned char>(P[j])] = m - j;
    }

    size_t i = 0;

    while (i <= n - m) {
        if (match(P, T, m, n, i, 0)) {
            ind.push_back(i);
        }
        if (i + m < n) {
            i += skip[static_cast<unsigned char>(T[i + m])];
        }
        else {
            break;
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

    std::vector<size_t> indices = Sunday(pattern, text);

    if (!indices.empty()) {
        std::cout << "Pattern found at indices: ";
        for (size_t index : indices) 
            std::cout << index << " ";
    }
    else 
        std::cout << "Pattern not found" << std::endl;
}
