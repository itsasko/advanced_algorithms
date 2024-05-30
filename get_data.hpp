#ifndef GET_DATA
#define GET_DATA

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

using std::chrono::nanoseconds;

std::random_device rd;
std::mt19937 gen(rd());

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
    file.close();
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

#endif