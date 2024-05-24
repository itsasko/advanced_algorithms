#include <iostream>
#include "rabin_karp_picture.hpp"




int main() {
    Picture pic(5, 5);

    pic.generate_picture(2);

    // pic.set_picture();
    pic.display_picture();

    auto xs = picture_search(pic, 2);

    for(auto& pair: xs) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }

}