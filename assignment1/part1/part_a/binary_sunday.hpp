#ifndef BINARY_SUNDAY
#define BINARY_SUNDAY


#include <iostream>
#include <string>
#include <unordered_map>


std::unordered_map<char, size_t> createShiftTable(const std::string& pattern) {
    std::unordered_map<char, size_t> shiftTable;
    size_t patternLength = pattern.length();
    
    for (size_t i = 0; i < patternLength; ++i) {
        shiftTable[pattern[i]] = patternLength - i;
    }
    
    return shiftTable;
}

std::vector<size_t> binarySundaySearch(const std::string& text, const std::string& pattern) {
    std::vector<size_t> results;

    size_t textLength = text.length();
    size_t patternLength = pattern.length();
    
    std::unordered_map<char, size_t> shiftTable = createShiftTable(pattern);
    
    int i = 0;
    while (i <= textLength - patternLength) {
        int j = 0;
        while (j < patternLength && pattern[j] == text[i + j]) {
            ++j;
        }
        
        if (j == patternLength) {
            results.push_back(i);
        }
        
        if (i + patternLength < textLength) {
            char nextChar = text[i + patternLength];
            if (shiftTable.find(nextChar) != shiftTable.end()) {
                i += shiftTable[nextChar];
            } else {
                i += patternLength + 1; 
            }
        } else {
            ++i; 
        }
    }

    return results;
}

#endif