#include <iostream>
#include "../part_a/rabin_karp.hpp"
#include "../part_a/kmp/KMP.h"
#include "../../../get_data.hpp"
#include <cassert>

constexpr int max_count = 100;
constexpr int max_size = 40000;
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



template <typename T>
nanoseconds measure_time(const std::string& text, const std::string& word) {
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


std::string generatePattern(size_t length) {
    const std::string characters = "abc"; 
    std::string pattern;
    
    std::uniform_int_distribution<size_t> block_size_dist(1, 3);
    std::uniform_int_distribution<size_t> repeat_dist(1, 3);  
    std::uniform_int_distribution<size_t> char_dist(0, characters.length() - 1);  

    while (pattern.length() < length) {
        size_t block_size = block_size_dist(gen); 
        std::string block;
        
        for (size_t i = 0; i < block_size; ++i) {
            block += characters[char_dist(gen)];
        }
        
        size_t repeats = repeat_dist(gen); 
        std::string full_block;
        
        for (size_t i = 0; i < repeats; ++i) {
            full_block += block;
        }
        full_block += characters[char_dist(gen)]; 
        
        pattern += full_block.substr(0, length);
    }

    return pattern;
}

void test_search(std::string filename) {
    std::vector<nanoseconds> results(10, nanoseconds(0));
    std::ofstream file(filename);

    for(size_t size = 20000; size < max_size; size += increment) {
        for(size_t count = 0; count < max_count; ++count) {

            std::string word = generatePattern(size-size/4);
            std::string text = generatePattern(size);

            results[0] += measure_time(rabin_karp_search, text, word);
            results[1] += measure_time<KMP>(text, word);


        }
        file << size << ' ' << results[0].count()/max_count << ' ' << results[1].count()/max_count << '\n';

        std::fill(results.begin(), results.end(), nanoseconds(0));
        std::cout << size << '\n';
    }

    file.close();

}
 
    


int main() {
    test_search("data2.txt");
}