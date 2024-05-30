#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../part1/gusfield_z.hpp"
#include "../part1/rabin_karp.hpp"
#include "../../get_data.hpp"


constexpr int max_count = 100;
constexpr int max_size = 5000;
constexpr int increment = 100;




nanoseconds measure_time(std::vector<size_t>(*search)(const std::string& ,  const std::string&), const std::string& text, const std::string& word) {
    auto start = std::chrono::steady_clock::now();
	auto xs = search(text, word);	
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);
	
    for(auto i: xs) {
        assert(text.substr(i, word.size()) == word);
    }

    return time;
}

void test_search(std::vector<std::string>& words, std::string filename) {
    std::vector<nanoseconds> results(10, nanoseconds(0));
    std::ofstream file(filename);

    for(size_t size = 1; size < max_size; size += increment) {
        
        for(size_t count = 0; count < max_count; ++count) {
            std::vector<std::string> sentence = generate_sentence(words, size);
            std::string word = get_random_word(sentence);

            std::string text = convert_to_string(sentence);

            results[0] += measure_time(z_search, text, word);
            results[1] += measure_time(rabin_karp_search, text, word);
        }
        file << size << ' ' << results[0].count()/max_count << ' ' << results[1].count()/max_count << '\n';
        std::fill(results.begin(), results.end(), nanoseconds(0));

        std::cout << size << '\n';
    }

    file.close();

}
 
    


int main() {
    std::string file_loc = "../data/english_words.txt";
    std::vector<std::string> words(count_number_of_lines(file_loc));

    get_words(words, file_loc);

    test_search(words, "data.txt");
}