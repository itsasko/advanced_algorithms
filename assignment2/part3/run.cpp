#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>
#include "hash_table_chaining.hpp"
#include "hash_table_probing.hpp"
#include "hash_table_double.hpp"

using std::chrono::nanoseconds;

std::random_device rd;
std::mt19937 gen(rd());

constexpr int max_count = 1000;
constexpr int capacity = 2000;

// void* operator new[](size_t n) {
//     std::cout << "array of " << n << " bytes allocated\n";
//     return malloc(n);
// }

// void operator delete[](void* p, size_t n) {
//     std::cout << n << " array of deallocated\n";
//     return free(p);
// }

// void* operator new(size_t n) {
//     std::cout << n << " bytes allocated\n";
//     return malloc(n);
// }

// void operator delete(void* p, size_t n) {
//     std::cout << n << " deallocated\n";
//     free(p);
// }


template <typename T>
nanoseconds measure_time(T& obj, size_t& searched_element) {
    std::uniform_int_distribution<size_t> dist(0, 2000);
    size_t number = dist(gen);
    
    searched_element = number;
    
    auto start = std::chrono::steady_clock::now();
    obj.insert(number);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    return time;
}

template <typename T>
nanoseconds measure_search_time(T& obj, size_t searched_element) {

    bool found = false;

    auto start = std::chrono::steady_clock::now();
    found = obj.search(searched_element);
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);

    assert(found == true);

    return time;
}


void test(std::string filename, std::string filename2) {
    std::vector<nanoseconds> insert_chaining(capacity, nanoseconds(0));
    std::vector<nanoseconds> insert_probing(capacity, nanoseconds(0));
    std::vector<nanoseconds> insert_double(capacity, nanoseconds(0));

    std::vector<nanoseconds> search_chaining(capacity, nanoseconds(0));
    std::vector<nanoseconds> search_probing(capacity, nanoseconds(0));
    std::vector<nanoseconds> search_double(capacity, nanoseconds(0));

    size_t last_element_chaining = 0;
    size_t last_element_probing = 0;
    size_t last_element_double = 0;


    for(size_t count = 0; count < max_count; ++count) {

        hash_table_chaining::hash_table<int> tb1(2048);
        hash_table_probing::hash_table<int> tb2(2048);
        hash_table_double::hash_table<int> tb3(2048);
        

        for(size_t i = 0; i < capacity; ++i) {
            insert_chaining[i] += measure_time(tb1, last_element_chaining);
            insert_probing[i] += measure_time(tb2, last_element_probing);
            insert_double[i] += measure_time(tb3, last_element_double);

            search_chaining[i] += measure_search_time(tb1, last_element_chaining);
            search_probing[i] += measure_search_time(tb1, last_element_chaining);
            search_double[i] += measure_search_time(tb1, last_element_chaining);

        }
       std::cout << count << ' ' << std::endl;
    
    
    }

    std::ofstream file(filename);
    for(size_t i = 0; i < capacity; ++i) {
        file << i+1 << ' ' << insert_chaining[i].count()/max_count << ' ' << insert_probing[i].count()/max_count << ' ' << insert_double[i].count()/max_count << '\n';
    }
    file.close();

    std::ofstream file2(filename2);
    for(size_t i = 0; i < capacity; ++i) {
        file2 << i+1 << ' ' << search_chaining[i].count()/max_count << ' ' << search_probing[i].count()/max_count << ' ' << search_double[i].count()/max_count << '\n';
    }
    file2.close();

}
 
    


int main() {

    test("insert_dt.txt", "search_dt.txt");
}