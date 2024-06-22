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
        std::cout << std::endl;
    }
    else 
        std::cout << "Pattern not found" << std::endl;
}
