#ifndef HASH_TABLE_DOUBLE
#define HASH_TABLE_DOUBLE

#include <iostream>
#include <memory>



namespace hash_table_double {

    constexpr size_t prime = 3;


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

            if(elements >= capacity) {
                throw std::runtime_error("No free space");
            }

            size_t index = hashable_obj(value)%capacity;
            
            if(!container[index]) {
                container[index] = AllocTraits::allocate(Alloc, 1);
                AllocTraits::construct(Alloc, container[index], value);
            }
            else {
                size_t x = 0;
                while (container[index]) {
                    index = (hashable_obj(value) + x * secondary_hash(value)) % capacity;
                    ++x;
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

            size_t x = 0;
            while (container[index] && x <= capacity) {
                if(*(container[index]) == value) {
                    return true;
                }
            
                index = (hashable_obj(value) + x * secondary_hash(value)) % capacity;
                ++x;
            }

            return false;
        }

        size_t secondary_hash(const T& value) const {
            std::size_t hash1 = hashable_obj(value);
            std::size_t hash2 = hashable_obj(value) * prime;

            return hash1 ^ (hash2 << 1);  
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