#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include "type_traits"
#include "trie.hpp"
#include "../../../get_data.hpp"


constexpr int max_count = 10;
constexpr int max_size = 200;
constexpr int increment = 10;


bool list_search(std::list<std::string>& obj, std::string searched_word) {
    for(auto& word: obj) {
        if(word == searched_word) {
            return true;
        }
    }
    return false;
}



template <typename T>
nanoseconds measure_insert(T& obj, const std::string& word) {    
    auto start = std::chrono::steady_clock::now();
    obj.insert(word);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    return time;
}

template <>
nanoseconds measure_insert<std::list<std::string>>(std::list<std::string>& obj, const std::string& word) {    
    auto start = std::chrono::steady_clock::now();
    obj.push_back(word);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    return time;
}

template <typename T>
auto measure_search_time(T& obj, const std::string& searched_element) -> decltype(std::declval<T>().find(searched_element), nanoseconds()) {


    auto start = std::chrono::steady_clock::now();
    auto found = obj.find(searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    if(found == obj.end()) {
        std::cout << searched_element << " is incorrect" << std::endl;
    }

    return time;
}

template <typename T>
auto measure_search_time(T& obj, const std::string& searched_element) -> decltype(std::declval<T>().search(searched_element), nanoseconds()) {

    bool found = false;

    auto start = std::chrono::steady_clock::now();
    found = obj.search(searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    if(!found) {
        std::cout << searched_element << " is incorrect" << std::endl;
    }

    return time;
}


auto measure_search_time(std::list<std::string>& obj, const std::string& searched_element) {

    bool found = false;

    auto start = std::chrono::steady_clock::now();
    found = list_search(obj, searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    if(!found) {
        std::cout << searched_element << " is incorrect" << std::endl;
    }

    return time;
}


void test_insert(std::vector<std::string>& words, const std::string& filename) {
    std::ofstream file(filename);

    for (size_t i = 1; i <= words.size(); i += 100) {
        std::list<std::string> word_list;
        std::set<std::string> word_set;
        Trie word_trie;
        std::unordered_set<std::string> word_hash;

        nanoseconds total_time_list(0), total_time_set(0), total_time_trie(0), total_time_hash(0);

        for (size_t j = 0; j < i; ++j) {
            total_time_list += measure_insert(word_list, words[j]);
            total_time_set += measure_insert(word_set, words[j]);
            total_time_trie += measure_insert(word_trie, words[j]);
            total_time_hash += measure_insert(word_hash, words[j]);
        }

        nanoseconds avg_time_list = total_time_list / i;
        nanoseconds avg_time_set = total_time_set / i;
        nanoseconds avg_time_trie = total_time_trie / i;
        nanoseconds avg_time_hash = total_time_hash / i;

        file << i << ' '
             << avg_time_list.count() << ' '
             << avg_time_set.count() << ' '
             << avg_time_trie.count() << ' '
             << avg_time_hash.count() << '\n';
    
        std::cout << i << '\n';
    }
    file.close();
}


void test(std::vector<std::string> words, const std::string& filename) {
    std::vector<nanoseconds> search_list(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_set(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_trie(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_hash(max_size, nanoseconds(0));


    std::list<std::string> word_list_1;
    std::set<std::string> word_list_2;
    Trie word_list_3;
    std::unordered_set<std::string> word_list_4;


    for(size_t i = 0; i < words.size(); ++i) {
        word_list_1.push_back(words[i]);
        word_list_2.insert(words[i]);
        word_list_3.insert(words[i]);
        word_list_4.insert(words[i]);
    }


    for(size_t count = 0; count < max_count; ++count) {


       for(size_t size = 0; size < max_size; size += increment) {
           auto sentence = generate_sentence(words, size+1);

            for(auto& word: sentence) {
                search_list[size] += measure_search_time(word_list_1, word);
                search_set[size] += measure_search_time(word_list_2, word);
                search_trie[size] += measure_search_time(word_list_3, word);
                search_hash[size] += measure_search_time(word_list_4, word);
            }

       }

       std::cout << count << '\n';

    }


    std::ofstream file(filename);
    for(size_t i = 0; i < max_size; i += increment) {
        file << i << ' ' << search_list[i].count()/max_count << ' ' << search_set[i].count()/max_count << ' ' << search_trie[i].count()/max_count << ' ' << search_hash[i].count()/max_count << '\n';
    }
    file.close();

}
 
   


int main() {
    std::string file_loc = "data/english_words.txt";

    std::vector<std::string> words(count_number_of_lines(file_loc));

    get_words(words, file_loc);



    test_insert(words, "data/build.txt");
    test(words,  "data/search.txt");
}


