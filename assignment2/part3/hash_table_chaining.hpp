#ifndef HASH_TABLE_CHAINING
#define HASH_TABLE_CHAINING

#include <iostream>
#include <memory>


namespace hash_table_chaining {
    
    template <typename T, typename Hash = std::hash<T>, typename Allocator = std::allocator<T>>
    class hash_table {    

        struct Node {
            T value;
            Node* next = nullptr;

            Node(const T& _value): value(_value), next(nullptr) {}
        };

        Node** container = nullptr; 
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

        explicit hash_table(size_t size): capacity(size), elements(0) {
            container = NodePtrAllocTraits::allocate(NodePtrAlloc, capacity);
            for(size_t i = 0; i < capacity; ++i) {
                NodePtrAllocTraits::construct(NodePtrAlloc, container+i, nullptr);
            }
        }

        void insert(const T& value) {        
            size_t index = hashable_obj(value)%capacity;
            
            Node* curr = container[index];
            if(!curr) {
                container[index] = NodeAllocTraits::allocate(NodeAlloc, 1);
                NodeAllocTraits::construct(NodeAlloc, container[index], value);
            }
            else {                
                while (curr->next != nullptr) {
                    curr = curr->next;
                }

                curr->next = NodeAllocTraits::allocate(NodeAlloc, 1);
                NodeAllocTraits::construct(NodeAlloc, curr->next, value);
            }
            ++elements;

        }

        bool search(const T& value) {
            size_t index = hashable_obj(value)%capacity;

            if(container[index] == nullptr) {
                return false;
            }

            Node* curr = container[index];
            while(curr) {
                if(curr->value == value) {
                    return true;
                }
                curr = curr->next;
            }

            return false;
        }

        size_t size() const {
            return elements;
        }


        ~hash_table() {           
            for(size_t i = 0; i < capacity; ++i) {
                Node* curr = container[i];
            
                while(curr) {
                    Node* next = curr->next;
                    NodeAllocTraits::destroy(NodeAlloc, curr);
                    NodeAllocTraits::deallocate(NodeAlloc, curr, 1);
                    curr = next;
                }
                NodeAllocTraits::destroy(NodeAlloc, container[i]);
            }
            NodePtrAllocTraits::deallocate(NodePtrAlloc, container, capacity);
        }


    };

}



#endif