//
//Travis and Christopher
//

#ifndef HASH_MAP_HASH_MAP_H
#define HASH_MAP_HASH_MAP_H
#include<utility> //allows us to use std::
namespace edu{ namespace vcccd{ namespace vc{ namespace csv15{
//Find Method: Key info
//Insert: Key and value info
    template<class KeyType, class ValueType>
    class HashMap {
    public:
        class Iterator{
        public:
            Iterator(std::pair<KeyType, ValueType> **first, std::pair<KeyType, ValueType> **last){
                _current = first;
                for(_current++; _current == nullprt && _current != last; _current++)
                _last = last;
            }
            Iterator(const Iterator &other){
                _current = other._current();
                _last = other._last;
            }
        public:
            const std::pair<KeyType, ValueType> &operator*(){
                return **_current()
            }


            Iterator &operator++(){
                for(_current++; _current == nullptr && _current != _last; _current++);
                return *this;
            }

            //using bool because we want to return a true or false value being that something either IS or IS NOT equal to something
            bool operator!=(const Iterator &other){ //apply this->_current?
                return _current != other._current;
            }

        private:
            std::pair<KeyType, ValueType> **_current();
            std::pair<KeyType, ValueType> **_last();
        };
    public: // two publics is just a way of visually organizing
        static constexpr size_t DEFAULT_BUCKET_SIZE = 7;
        static constexpr size_t C1 = 11; //size_t because its a random number
        static constexpr size_t C2 = 14;

    public:
        HashMap() { //default
            buckets = new std::pair<KeyType, ValueType>*[DEFAULT_BUCKET_SIZE];// using square buckets to allocate
            for(size_t i = 0; i < size; i++){
                buckets[i] = nullptr; //makes us start with an empty set of buckets
            }
            size = DEFAULT_BUCKET_SIZE;
        }; // Default Constructor
        HashMap(const HashMap &other){ //Copy Constructor uses const because you want to keep other value as a read and this is a deep copy
            this->buckets = new std::pair<KeyType, ValueType>[other.size];
            this->size = other.size;
            for(size_t i = 0; i < this->size; i++ ) { //Copies each value from the other value
                this->bucket[i] = other.buckets[i];
            }

        };
        HashMap(HashMap &&other){  // Move semantic (shallow copy) where we steal memory from something that will be deleted
            buckets = other.buckets;
            size = other.size;

        };
        ~HashMap(){
            delete [] buckets; //using square buckets to de-allocate
        };

        //-----------------------------------------
    public:

        ValueType find(const KeyType &key){ //using reference is important here because if we passed in 1000 elements, we would then copy 1000 elements, reference keeps us from having to do this
            return operator[](key);
        }
        void insert(const KeyType &key, ValueType value){
            operator[](key) = value;
        }
        ValueType &operator[] (const KeyType &key){ //Allows us to override the bracket operator
            size_t hashValue = hash(key);
            size_t index = hashValue % size;
            for( size_t i = 1 ; i < size && (buckets[index] != nullptr && buckets[index]->first !=key ) ; i++ ){ //i < size keeps the program from running infinitely, i = 1 because if i @0 collides, then it enters the loop. Or Statement allows us to "Short Circuit"
                index = (hashValue + C1*i + C2*i*i) % size;
            }
            //checks to see if this is case where we insert
            if(buckets[index] == nullptr) {
                buckets[index] = new std::pair<KeyType, ValueType>; //Allocates new memory
                buckets[index]->first = key;
            }
            return buckets[index]->second;
        }
        Iterator begin(){
            return Iterator(buckets, buckets + size);
        }
        Iterator end(){
            return Iterator(nullptr, nullptr)
        }
    private:
        size_t hash(const KeyType &key) { //Our hashing function
            return 1;
        }
    private:
        std::pair<KeyType, ValueType> **buckets; //buckets is initialized in the constructor
        size_t size;

    };

}}}}
#endif //HASH_MAP_HASH_MAP_H
