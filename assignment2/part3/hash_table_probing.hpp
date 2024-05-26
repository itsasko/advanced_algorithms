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
            for(size_t i = 0; i < capacity; ++i) {
                PtrAllocTraits::construct(PtrAlloc, container+i, nullptr);
            }
        }

        void insert(const T& value) {        

            if(elements >= capacity) {
                throw std::runtime_error("No free space");
            }

            size_t index = hashable_obj(value)%capacity;
            
            if(!container[index]) {
                container[index] = AllocTraits::allocate(Alloc, 1);
                AllocTraits::construct(Alloc, container[index], value);
            }
            else {
                
                while (container[index]) {   
                    index = (index + 1) % capacity;
                }
                
                container[index] = AllocTraits::allocate(Alloc, 1);
                AllocTraits::construct(Alloc, container[index], value);
            }
            ++elements;
        }

        bool search(const T& value) {
            size_t index = hashable_obj(value)%capacity;

            if(container[index] == nullptr) {
                return false;
            }

            size_t counter = 0;
            while(container[index] && counter < capacity) {
                if(*(container[index]) == value) {
                    return true;
                }
                index = (index + 1) % capacity;
                ++counter;
            }

            return false;
        }

        size_t size() const {
            return elements;
        }


        ~hash_table() { 
            for(size_t i = 0; i < capacity; ++i) {
                AllocTraits::destroy(Alloc, container[i]);
                AllocTraits::deallocate(Alloc, container[i], 1);  
            }
            PtrAllocTraits::deallocate(PtrAlloc, container, capacity);
        }


    };

}



#endif