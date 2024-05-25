#ifndef HASH_TABLE_CHAINING
#define HASH_TABLE_CHAINING

#include <iostream>
#include <memory>

constexpr double max_load_factor = 0.6;

template <typename T, typename Hash = std::hash<T>, typename Allocator = std::allocator<T>>
class hash_table {    

    struct Node {
        T value;
        Node* next = nullptr;
    };

    Node** values = nullptr; 
    size_t capacity = 0;
    size_t elements = 0;

    using AllocTraits = std::allocator_traits<Allocator>;

    using NodeAllocator = typename AllocTraits::rebind_alloc<Node>;
    using NodeAllocTraits = std::allocator_traits<NodeAllocator>;
    
    using NodePtrAllocator = typename AllocTraits::rebind_alloc<Node*>;
    using NodePtrAllocTraits = std::allocator_traits<NodePtrAllocator>;


    NodeAllocator NodeAlloc;
    NodePtrAllocator NodePtrAlloc;

public:

    hash_table(): capacity(0), elements(0) {}
    hash_table(size_t size): capacity(size), elements(0) {
        values = NodePtrAllocTraits::allocate(NodePtrAlloc, capacity*sizeof(Node*));
    }

    void insert() {
        if(static_cast<double>(elements)/capacity > max_load_factor) {
            // rehash
        }

    }

    bool search(const T& value) {
    
    }




    //~hash_table() {
       // for(size_t i = 0; i < capacity; ++i) {
         //   if(values[i]) {
                
                //Node* curr = values[i];
                //while(curr != nullptr) {
                    // destroy
                //}
                // deallocate
           // }
           // NodeAllocator::deallocate()

        //}
        

    


};





#endif