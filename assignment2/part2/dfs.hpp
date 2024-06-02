#ifndef DFS_COLOR
#define DFS_COLOR

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <set>
#include <unordered_map>


class Graph {
    std::vector<std::string> guests;
    std::unordered_map<std::string, std::vector<std::string>> guest_animosities;
    

public:    
    Graph(const std::vector<std::string>& obj1, const std::unordered_map<std::string, std::vector<std::string>>& obj2): guests(obj1), guest_animosities(obj2) {}

    size_t size() {
        return guests.size();
    }

    const auto& get_data() const {
        return guests;
    }

    const std::string& get_guest(size_t index) const {
        return guests[index];
    }

    const auto& get_animosities(const std::string& guest) const {
        auto it = guest_animosities.find(guest);
        if(it == guest_animosities.end()) {
            throw std::logic_error("Guest not found");
        }

        return it->second;
    }


};



void divide_guests(Graph& graph) {
    std::unordered_map<std::string, int> colored;
    std::stack<std::pair<std::string, int>> dfs_stack;
   

    std::string guest;
    int color = 0;

    for(size_t i = 0; i < graph.size(); ++i) {

        if(colored.find(graph.get_guest(i)) == colored.end()) {
            dfs_stack.emplace(graph.get_guest(i), 0);

            while(!dfs_stack.empty()) {
                    
                guest = dfs_stack.top().first;
                color = dfs_stack.top().second;

                colored.emplace(guest, color);

                dfs_stack.pop();
                
                for(auto& person: graph.get_animosities(guest)) {
                    auto it = colored.find(person);
                    
                    if(it == colored.end()) {
                        dfs_stack.emplace(person, color^1);
                    }
                    else if (it->second == color) {
                        std::cout << "Not possible to divide \n";
                        return ;
                    }

                }
            
            }
        }
    
    }

    for(const auto& guest: graph.get_data()) {
        auto it = colored.find(guest);

        if(!(it->second)) {
            std::cout << it->first  << " left table" << std::endl;
        }
        else {
            std::cout << it->first << " right table" << std::endl;
        }
    }
}



#endif
