#include <iostream>
#include "rabin_karp_picture.hpp"




int main() {
    Picture pic(5, 5);

    pic.set_picture();
    pic.display_picture();

    picture_search(pic, 2);
}