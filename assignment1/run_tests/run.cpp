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

using std::chrono::nanoseconds;

std::random_device rd;
std::mt19937 gen(rd());

constexpr int max_count = 100;
constexpr int max_size = 5000;
constexpr int increment = 100;

void remove_carriage(std::string& line) {
    for(size_t i = 0; i < line.size(); ++i) {
        if(line[i] == '\r') {
            line.erase(line.begin()+i);
        }
    }
}

std::vector<std::string> generate_sentence(std::vector<std::string>& obj, size_t sentence_size) {
    std::uniform_int_distribution<size_t> dist(0, obj.size()-1);
    std::vector<std::string> result(sentence_size);

    for(size_t i = 0; i < sentence_size; ++i) { 
        result[i] = obj[dist(gen)];
    }

    return result;
}

std::string get_random_word(std::vector<std::string>& obj) {
    std::uniform_int_distribution<size_t> dist(0, obj.size()-1);

    return obj[dist(gen)];
} 

size_t count_number_of_lines(std::string& file_name) {
    size_t count = 0;
    
    std::ifstream file(file_name);
    std::string line;
    while(std::getline(file, line)) {
        ++count;
    }

    return count;
}

void get_words(std::vector<std::string>& words, std::string& file_name) {
    
    std::ifstream file(file_name);
    std::string line;

    size_t i = 0;
    while(std::getline(file, line)) {
        remove_carriage(line);
        words[i++] = std::move(line);
    }

}


std::string convert_to_string(std::vector<std::string>& obj) {
    std::string text;

    for(size_t i = 0; i < obj.size(); ++i) {
        text += std::move(obj[i]);
        text += ' ';
    }
    text.pop_back();

    return text;
}


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