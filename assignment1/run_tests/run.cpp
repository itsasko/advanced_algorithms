#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../part1/part_a/gusfield_z.hpp"
#include "../part1/part_a/rabin_karp.hpp"
#include "../../get_data.hpp"
#include "../part1/part_a/fsm/FSM.h"
#include "../part1/part_a/kmp/KMP.h"

#include "../part1/part_a/Brute-Force.hpp"
#include "../part1/part_a/Sunday.hpp"

constexpr int max_count = 100;
constexpr int max_size = 10000;
constexpr int increment = 10;




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

template <typename T>
nanoseconds measure_time_fk(const std::string& text, const std::string& word) {
    auto start = std::chrono::steady_clock::now();
	
    T obj(text, word);
    obj.search();

    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);
	
    for(auto i: obj.occurences) {
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
            results[2] += measure_time_fk<FSM>(text, word);     
            results[3] += measure_time(BruteForce, text, word);
            results[4] += measure_time(Sunday, text, word);
            results[5] += measure_time_fk<KMP>(text, word);


        }
        file << size << ' ' << results[0].count()/max_count << ' ' << results[1].count()/max_count << ' ' << results[2].count()/max_count <<
        ' ' << results[3].count()/max_count << ' ' << results[4].count()/max_count <<  ' ' << results[5].count()/max_count << '\n';


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