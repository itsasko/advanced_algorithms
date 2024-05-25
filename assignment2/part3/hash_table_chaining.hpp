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

        Node(const T& value): value(value) {}
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
    Hash hashable_obj;

public:

    hash_table(size_t size): capacity(size), elements(0) {
        values = NodePtrAllocTraits::allocate(NodePtrAlloc, capacity);
    }

    void insert(const T& value) {
        if(static_cast<double>(elements)/capacity > max_load_factor) {
            // rehash
        }
        
        size_t index = hashable_obj(value)%capacity;
        
        Node* curr = values[index];
        if(!curr) {
            values[index] = NodeAllocTraits::allocate(NodeAlloc, 1);
            NodeAllocTraits::construct(NodeAlloc, values[index], value);
        }
        else {
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = NodeAllocTraits::allocate(NodeAlloc, 1);
            NodeAllocTraits::construct(NodeAlloc, curr->next, value);
        }

    }

    bool search(const T& value) {
        size_t index = hashable_obj(value)%capacity;

        if(values[index] == nullptr) {
            return false;
        }

        Node* curr = values[index];
        while(curr) {
            if(curr->value == value) {
                return true;
            }
            curr = curr->next;
        }

        return false;
    }


    ~hash_table() {
          
       
       for(size_t i = 0; i < capacity; ++i) {
            Node* curr = values[i];
           
            NodeAllocTraits::destroy(NodeAlloc, values[i]);
           
            if(curr) {
                Node* next = curr->next;
           
                while (next) {
                    curr = next;
                    next = curr->next;
                    NodeAllocTraits::destroy(NodeAlloc, curr);
                    NodeAllocTraits::deallocate(NodeAlloc, curr, sizeof(Node));
                }
            }
           
           NodeAllocTraits::deallocate(NodeAlloc, values[i], sizeof(Node));
        }
        NodePtrAllocTraits::deallocate(NodePtrAlloc, values, capacity*sizeof(Node*));
  
    }
        

    


};





#endif