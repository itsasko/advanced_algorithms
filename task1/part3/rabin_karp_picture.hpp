#ifndef RABIN_KARP_PIC
#define RABIN_KARP_PIC


#include <iostream>
#include <string>
#include <vector>
#include <random>


std::random_device rd;
std::mt19937 gen(rd());

constexpr int prime = 17;
constexpr long long shift = 30;
long long mask = (1 << shift) - 1;



class Picture {
    char** picture = nullptr;
    size_t rows = 0;
    size_t collumns = 0;

public:

    Picture(size_t rows, size_t collumns): rows(rows), collumns(collumns) {
        picture = new char*[rows];

        for(size_t i = 0; i < rows; ++i) {
            picture[i] = new char[collumns];
        }
    }

    void set_picture() {
        char symbol = '\0';

        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < collumns; ++j) {
                std::cin >> symbol;
                picture[i][j] = symbol;
            }
        }
    }

    void generate_picture(size_t K) {
        std::uniform_int_distribution<size_t> dist(32, 120);

        std::string pattern;
        for(size_t i = 0; i < K*K; ++i) {
            pattern += static_cast<char>(dist(gen));
        }

        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < collumns; ++j) {
                picture[i][j] = pattern[pattern.size() - 1 -(i+j)%pattern.size()];            
            }
        }


        for(size_t i = 0; i < K; ++i) {
            for(size_t j = collumns - K; j < collumns; ++j) {
                picture[i][j] = pattern[pattern.size() -  1 - (i+j)%pattern.size()];
            }
        }        

    }

    void display_picture() const {
        for(size_t i = 0; i < rows; ++i) {
            for(size_t j = 0; j < collumns; ++j) {
               std::cout << picture[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    size_t get_rows() const {
        return rows;
    }

    size_t get_collumns() const {
        return collumns;
    }

    size_t size() const {
        return rows * collumns;
    }

    char* operator[](size_t rows) {
        return picture[rows];
    }

    const char* operator[](size_t rows) const {
        return picture[rows];
    }


    ~Picture() {
        for(size_t i = 0; i < rows; ++i) {
            delete [] picture[i];
        }
        delete [] picture;
    }

};


auto compute_hash(const Picture& pic, size_t row, size_t indent_r = 0, size_t indent_l = 0) {

    long long hash = 0;

    for(size_t j = indent_l; j < pic.get_collumns() - indent_r; ++j) {
        hash = (hash * prime + static_cast<int>(pic[row][j])) & mask;
    }

    return hash;
}

auto compute_lined_hash(const Picture& pic, size_t K) {
    std::vector<long long> lined_hash;

    long long hash = 0;
    for(size_t i = 0; i < K; ++i) {
        for(size_t j = pic.get_collumns() - K; j < pic.get_collumns(); ++j) {
            hash = (hash * prime + static_cast<int>(pic[i][j])) & mask;
        }

        lined_hash.push_back(hash);
        hash = 0;
    }

    return lined_hash;
}


auto compute_start_lined_hash(const Picture& pic, size_t K) {
    std::vector<long long> lined_hash;

    long long hash = 0;
    for(size_t i = 0; i < pic.get_rows(); ++i) {
        for(size_t j = 0; j < K; ++j) {
            hash = (hash * prime + static_cast<int>(pic[i][j])) & mask;
        }

        lined_hash.push_back(hash);
        hash = 0;
    }

    return lined_hash;
}

auto compute_lined_text(const Picture& pic, size_t K) {
    std::vector<std::string> lined_text;

    std::string text;
    for(size_t i = 0; i < K; ++i) {
        for(size_t j = pic.get_collumns() - K; j < pic.get_collumns(); ++j) {
            text += pic[i][j];
        }
        lined_text.push_back(std::move(text));
    }

    return lined_text;
}


auto compute_multiplier(size_t length) {
    long long multiplier = 1;
    
    for(size_t i = 1; i < length; ++i) {
        multiplier *= prime;
        multiplier & mask;
    }

    return multiplier;
}

bool check_text(const Picture& pic, std::vector<std::string> pattern, size_t text_i, size_t text_j, size_t k, size_t pattern_i) {
    if(pattern.size() != k && pattern[0].size() != k) {
        return false;
    }


    size_t pattern_j = 0;
    while(k > 0) {
        
        if(pic[text_i][text_j] != pattern[pattern_i][pattern_j]) {
            return false;
        }

        ++text_j;
        ++pattern_j;
        --k;
    }
    
    
    
    return true;
}


auto picture_search(const Picture& pic, size_t K) {
    std::vector<std::pair<size_t, size_t>> result;


    if(pic.size() < K*K) {
        return result;
    }


    auto pattern_lined_hash = compute_lined_hash(pic, K);
    auto picture_lined_hash = compute_start_lined_hash(pic, K);
    auto pattern_lined_text = compute_lined_text(pic, K);
    
    auto multiplier = compute_multiplier(K);

    long long current_hash;
    
    for(size_t i = 0; i < pic.get_rows(); ++i) {
        current_hash = picture_lined_hash[i];

        for(size_t j = K; j < pic.get_collumns(); ++j) {
            if(i < K && j >= pic.get_collumns()-K) {
                continue;
            }
            
            if(current_hash == pattern_lined_hash[0] && check_text(pic, pattern_lined_text, i, j-K, K, 0)) {                
                size_t picture_level = i;
                

                if(picture_level+K > pic.get_rows()) {
                    break;
                }

                for(size_t pattern_level = 1; pattern_level < K; ++pattern_level) {
                    ++picture_level;
                    
                    if(!check_text(pic, pattern_lined_text, picture_level, j-K, K, pattern_level)) {
                        break;
                    }

                    result.emplace_back(i, j-K);
                }
            }


            current_hash = (current_hash - (static_cast<int>(pic[i][j-K]) * multiplier)) & mask;
            current_hash = (current_hash * prime + static_cast<int>(pic[i][j])) & mask;
        }

        if(current_hash == pattern_lined_hash[0] && check_text(pic, pattern_lined_text, i, pic.get_collumns()-K, K, 0)) {
            size_t picture_level = i;
                
            if(picture_level+K > pic.get_rows()) {
                break;
            }

            for(size_t pattern_level = 1; pattern_level < K; ++pattern_level) {
                ++picture_level;
                
                if(!check_text(pic, pattern_lined_text, picture_level, pic.get_collumns()-K, K, pattern_level)) {
                    break;
                }

                result.emplace_back(i, pic.get_collumns()-K);
            }
        }

    }

    return result;
}     



#endif