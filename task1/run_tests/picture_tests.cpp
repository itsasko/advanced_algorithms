#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>
#include "../part3/rabin_karp_picture.hpp"

using std::chrono::nanoseconds;


constexpr int max_count = 200;
constexpr int max_size = 300;
constexpr int increment = 10;



nanoseconds measure_time(std::vector<std::pair<size_t, size_t>>(*search)(const Picture& pic, size_t K), const Picture& pic, size_t K) {
    auto start = std::chrono::steady_clock::now();
	auto xs = search(pic, K);	
    auto end = std::chrono::steady_clock::now();
	nanoseconds time = std::chrono::duration_cast<nanoseconds>(end - start);
	
    return time;
}

void test_search(std::string filename) {
    std::vector<nanoseconds> results(10, nanoseconds(0));
    std::ofstream file(filename);

    for(size_t size = 5; size < max_size; size += increment) {

        Picture pic(size, size);        
        for(size_t count = 0; count < max_count; ++count) {
            pic.generate_picture(size/4);

            results[0] += measure_time(picture_search, pic, size/4);
        }
        file << size*size << ' ' << results[0].count()/max_count << '\n';
        std::fill(results.begin(), results.end(), nanoseconds(0));

        std::cout << size << '\n';
    }

    file.close();

}
 
    


int main() {

    test_search("pic_data.txt");
}