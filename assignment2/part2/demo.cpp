#include <iostream>
#include "dfs.hpp"



int main() {
    std::vector<std::string> guests = {"Aachen", "Baliyah", "Caron", "Ebbas", "Fringilia", "Jane", "Gabby"};
    std::unordered_map<std::string, std::vector<std::string>> guest_animosities_1;

    guest_animosities_1["Aachen"] = std::vector<std::string>{"Baliyah", "Caron"};
    guest_animosities_1["Baliyah"] = std::vector<std::string>{"Aachen", "Ebbas"};
    guest_animosities_1["Caron"] = std::vector<std::string>{"Aachen", "Ebbas", "Fringilia"};
    guest_animosities_1["Ebbas"] = std::vector<std::string>{"Baliyah", "Caron"};
    guest_animosities_1["Fringilia"] = std::vector<std::string>{"Caron", "Jane"};
    guest_animosities_1["Jane"] = std::vector<std::string>{"Fringilia", "Gabby"};
    guest_animosities_1["Gabby"] = std::vector<std::string>{"Jane"};


    Graph gr1(guests, guest_animosities_1);    
    divide_guests(gr1);

    std::cout << "\n\n";

    std::unordered_map<std::string, std::vector<std::string>> guest_animosities_2;

    guest_animosities_2["Aachen"] = std::vector<std::string>{"Baliyah", "Caron"};
    guest_animosities_2["Baliyah"] = std::vector<std::string>{"Aachen", "Ebbas"};
    guest_animosities_2["Caron"] = std::vector<std::string>{"Aachen", "Ebbas", "Fringilia"};
    guest_animosities_2["Ebbas"] = std::vector<std::string>{"Baliyah", "Caron", "Jane"};
    guest_animosities_2["Fringilia"] = std::vector<std::string>{"Caron", "Gabby"};
    guest_animosities_2["Jane"] = std::vector<std::string>{"Ebbas", "Gabby"};
    guest_animosities_2["Gabby"] = std::vector<std::string>{"Jane", "Fringilia"};


    Graph gr2(guests, guest_animosities_2);
    divide_guests(gr2);

}