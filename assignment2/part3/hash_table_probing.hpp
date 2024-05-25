#ifndef HASH_TABLE_PROBING
#define HASH_TABLE_PROBING

#include <iostream>
#include <memory>


namespace hash_table_probing {
    
    template <typename T, typename Hash = std::hash<T>, typename Allocator = std::allocator<T>>
    class hash_table {    

        T** container = nullptr; 
        size_t capacity = 0;
        size_t elements = 0;

        using AllocTraits = std::allocator_traits<Allocator>;
        
        using PtrAllocator = typename AllocTraits::rebind_alloc<T*>;
        using PtrAllocTraits = std::allocator_traits<PtrAllocator>;

        Allocator Alloc;
        PtrAllocator PtrAlloc;

        Hash hashable_obj;

    public:

        explicit hash_table(size_t size): capacity(size), elements(0) {
            container = PtrAllocTraits::allocate(PtrAlloc, capacity);
        }

        void insert(const T& value) {        
            size_t index = hashable_obj(value)%capacity;
            
            if(!container[index]) {
                container[index] = AllocTraits::allocate(Alloc, 1);
                AllocTraits::construct(Alloc, container[index], value);
            }
            else {
                
                size_t counter = 1;
                while (container[index+counter]) {
                    if(index+counter >= capacity) {
                        throw std::logic_error("No free places");
                    }      
                    ++counter;
                }
                
                container[index+counter] = AllocTraits::allocate(Alloc, 1);
                AllocTraits::construct(Alloc, container[index+counter], value);
            }
            ++elements;
        }

        bool search(const T& value) {
            size_t index = hashable_obj(value)%capacity;

            if(container[index] == nullptr) {
                return false;
            }

            size_t counter = 0;
            while(container[index+counter] && index+counter < capacity) {
                if(*(container[index+counter]) == value) {
                    return true;
                }
                ++counter;
            }

            return false;
        }

        size_t size() const {
            return elements;
        }


        ~hash_table() {        
            for(size_t i = 0; i < capacity; ++i) {
                            
                if(container[i]) {
                    AllocTraits::destroy(Alloc, container[i]);
                    AllocTraits::deallocate(Alloc, container[i], 1);
                }

            }
            PtrAllocTraits::deallocate(PtrAlloc, container, capacity);
        }


    };

}



#endif