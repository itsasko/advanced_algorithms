#ifndef ZSEARCH
#define ZSEARCH


#include <iostream>
#include <vector>


void get_z_array(std::vector<size_t>& z_array, std::string& text) {
    z_array[0] = 0;
    
    size_t L = 0;
    size_t R = 0;
    size_t k = 0;

    for(size_t i = 1; i < text.size(); ++i) {
        if (i > R) {
            L = i;
            R = i;

            size_t start = 0;
            while (R < text.size() && text[start] == text[R])
            {
                ++start;
                ++R;
            }
            z_array[i] = R-L;            
            --R;
        }
        else {

            k = i - L;

            if(z_array[k] < R-i+1) {
                z_array[i] = z_array[k]; 
            }
            else {
    
                L = i;

                while (R < text.size() && text[R-L] == text[R]) 
                {
                    ++R;
                }
                z_array[i] = R-L;        
               --R;
                
            }
        }

        
    }   
}


std::vector<size_t> z_search(const std::string& text, const std::string& pattern) {
    std::vector<size_t> result;
    
    std::string full_pattern = pattern + '%' + text;
    std::vector<size_t> z_array(full_pattern.size());

    get_z_array(z_array, full_pattern);

    size_t pattern_len = pattern.size();
    for(size_t i = 0; i < z_array.size(); ++i) {
        if(z_array[i] == pattern_len) {
            result.push_back(i-pattern_len-1);
        }
    }

    return result;
}




#endif