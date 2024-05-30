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

    assert(found != obj.end());

    return time;
}

template <typename T>
auto measure_search_time(T& obj, const std::string& searched_element) -> decltype(std::declval<T>().search(searched_element), nanoseconds()) {

    bool found = false;

    auto start = std::chrono::steady_clock::now();
    found = obj.search(searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    assert(found);

    return time;
}


auto measure_search_time(std::list<std::string>& obj, const std::string& searched_element) {

    bool found = false;

    auto start = std::chrono::steady_clock::now();
    found = list_search(obj, searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    assert(found);

    return time;
}





void test(std::vector<std::string> words, std::string filename, std::string filename2) {
    nanoseconds insert_list = nanoseconds(0);
    nanoseconds insert_set = nanoseconds(0);
    nanoseconds insert_trie = nanoseconds(0);
    nanoseconds insert_hash = nanoseconds(0);


    std::vector<nanoseconds> search_list(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_set(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_trie(max_size, nanoseconds(0));
    std::vector<nanoseconds> search_hash(max_size, nanoseconds(0));


    std::list<std::string> word_list_1;
    std::set<std::string> word_list_2;
    Trie word_list_3;
    std::unordered_set<std::string> word_list_4;

    std::ofstream file(filename);

    for(size_t i = 0; i < words.size(); ++i) {
        insert_list = measure_insert(word_list_1, words[i]);
        insert_set = measure_insert(word_list_2, words[i]);
        insert_trie = measure_insert(word_list_3, words[i]);
        insert_hash = measure_insert(word_list_4, words[i]);
    
        file << i+1 << ' ' << insert_list.count() << ' ' << insert_set.count() << ' ' << insert_trie.count()<< ' ' << insert_hash.count() << '\n';
    }

    file.close();


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


    std::ofstream file2(filename2);
    for(size_t i = 0; i < max_size; i += increment) {
        file2 << i << ' ' << search_list[i].count()/max_count << ' ' << search_set[i].count()/max_count << ' ' << search_trie[i].count()/max_count << ' ' << search_hash[i].count()/max_count << '\n';
    }
    file2.close();


}
 
   


int main() {
    std::string file_loc = "data/english_words.txt";

    std::vector<std::string> words(count_number_of_lines(file_loc));

    get_words(words, file_loc);




    test(words, "data/build.txt", "data/search.txt");
}


