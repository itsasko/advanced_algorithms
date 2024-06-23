#include <iostream>
#include "../part_a/rabin_karp.hpp"
#include "../part_a/Sunday.hpp"
#include "../../../get_data.hpp"
#include <cassert>

constexpr int max_count = 100;
constexpr int max_size = 10000;
constexpr int increment = 1000;



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

void test_search(std::string filename) {
    std::vector<nanoseconds> results(10, nanoseconds(0));
    std::ofstream file(filename);

    for(size_t size = 3000; size < max_size; size += increment) {
        for(size_t count = 0; count < max_count; ++count) {

            std::string text = std::string(size, 'a') + "b";
            std::string word = std::string(size/10, 'a');

            results[0] += measure_time(rabin_karp_search, text, word);
            results[1] += measure_time(Sunday, text, word);


        }
        file << size << ' ' << results[0].count()/max_count << ' ' << results[1].count()/max_count << '\n';

        std::fill(results.begin(), results.end(), nanoseconds(0));
        std::cout << size << '\n';
    }

    file.close();

}
 
    


int main() {
    test_search("data3.txt");
}