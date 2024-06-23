#include <iostream>
#include "../part_a/gusfield_z.hpp"
#include "../part_a/binary_sunday.hpp"
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



void test_search(std::string filename) {
    std::vector<nanoseconds> results(10, nanoseconds(0));
    std::ofstream file(filename);

    for(size_t size = 20000; size < max_size; size += increment) {
        for(size_t count = 0; count < max_count; ++count) {

            std::string text(size, 'x');
            text += "abcdefg";
            std::string word = "abcdefg";


            results[0] += measure_time(binarySundaySearch, text, word);
            results[1] += measure_time(z_search, text, word);


        }
        file << size << ' ' << results[0].count()/max_count << ' ' << results[1].count()/max_count << '\n';

        std::fill(results.begin(), results.end(), nanoseconds(0));
        std::cout << size << '\n';
    }

    file.close();

}
 
    


int main() {
    test_search("data.txt");
}