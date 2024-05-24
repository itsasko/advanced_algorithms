#ifndef RABIN_KARP
#define RABIN_KARP

#include <iostream>
#include <string>
#include <vector>


constexpr int prime = 17;
constexpr long long mod = 1e10+33;


auto compute_hash(const std::string& text) {

    long long hash = 0;
    
    for(auto c: text) {
        hash = (hash * prime + static_cast<int>(c)) % mod;
    }

    return hash;
}


auto compute_multiplier(size_t length) {
    long long multiplier = 1;
    
    for(size_t i = 1; i < length; ++i) {
        multiplier *= prime;
        multiplier %= mod;
    }

    return multiplier;
}

bool check_text(const std::string& text, const std::string& pattern) {
    return text == pattern;
}


std::vector<size_t> rabin_karp_search(const std::string& text, const std::string& pattern) {
    std::vector<size_t> result;

    auto searched_hash = compute_hash(pattern);

    if(text.size() < pattern.size()) {
        return result;
    }

    
    auto current_hash = compute_hash(text.substr(0, pattern.size()));
    auto multiplier = compute_multiplier(pattern.size());

    size_t i = pattern.size();
    
    for(; i < text.size(); ++i) {
        if(current_hash == searched_hash && check_text(text.substr(i-pattern.size(), pattern.size()), pattern)) {
           result.push_back(i-pattern.size());
        }

        current_hash = current_hash + mod;

        current_hash = (current_hash - (static_cast<int>(text[i-pattern.size()]) * multiplier)) % mod;
        current_hash = (current_hash * prime + static_cast<int>(text[i])) % mod;

    }

    if(current_hash == searched_hash && check_text(text.substr(i-pattern.size(), pattern.size()), pattern)) {
        result.push_back(i-pattern.size());
    }

    return result;


}

#endif