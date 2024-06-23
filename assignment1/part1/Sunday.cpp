#include <iostream>
#include <string>
#include <vector>


std::vector<size_t> Sunday(const std::string& _text, const std::string& _pattern) {
    size_t n = _text.size();
    size_t m = _pattern.size();

    std::vector<size_t> ind;
    std::vector<size_t> skip(128, m + 1);

    for (size_t j = 0; j < m; j++) {
        skip[_pattern[j]] = m - j;
    }

    size_t i = 0;

    while (i <= n - m) {
        size_t j = 0;

        while (j < m && _pattern[j] == _text[i + j]) {
            j++;
        }
        if (j == m) {
            ind.push_back(i);
        }

        if (i + m < n) {
            i += skip[_text[i + m]];
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

    std::vector<size_t> indices = Sunday(text, pattern);

    if (!indices.empty()) {
        std::cout << "Pattern found at indices: ";
        for (size_t index : indices) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Pattern has not been found" << std::endl;
    }

    return 0;
}
