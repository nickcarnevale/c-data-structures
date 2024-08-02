#include <cstddef>
#include <iostream>
#include "linkedlist.hpp"

class HashSet {
  private:
    // The backbone of the hash set. This is an array of Linked List pointers.
    LinkedList** array;

    // The number of buckets in the array
    size_t size; 

    // The number of items in the set
    size_t count;

    // Generate a prehash for an item with a given size
    unsigned long prehash(int item);

    //resize function
    void resize();

  public:
    // Initialize an empty hash set, where size is the number of buckets in the array
    HashSet(size_t size);

    // Free all memory allocated by the hash set
    ~HashSet();

    // Hash an unsigned long into an index that fits into a hash set
    unsigned long hash(int item);

    // Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
    // Recalculate the load factor after each successful insert (round to nearest whole number).
    // If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
    bool insert(int item);

    // Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
    bool remove(int item);

    // Return true if the item exists in the set, false otherwise
    bool contains(int item);

    // Returns the number of items in the hash set
    size_t len();

    // Returns the number of empty buckets that can be filled before reallocating
    size_t capacity();

    // Print Table. You can do this in a way that helps you implement your hash set.
    void print();

};

//modified prehash
unsigned long HashSet::prehash(int num) {
    unsigned long h = 5381;
    int c = num;
    h = ((h << 5) + h) + c;
    return h;
}

//constructor
HashSet::HashSet(size_t size) {
    this->array = new LinkedList*[size];
    for (size_t i = 0; i < size; i++) {
        this->array[i] = new LinkedList();
    }
    this->size = size;
    this->count = 0;
}

//deconstructor
HashSet::~HashSet() {
    for (size_t i = 0; i < size; i++) {
        delete this->array[i];
    }
    delete[] this->array;
}

//hash
unsigned long HashSet::hash(int item) {
    unsigned long hashval = this->prehash(item);
    return hashval % this->size;
}


//resize function
void HashSet::resize() {
    
    //create a new linkedlist array with new size
    size_t newSize = this->size * 2;
    LinkedList** new_array = new LinkedList*[newSize];
    for (size_t i = 0; i < newSize; i++) {
        new_array[i] = new LinkedList();
    }
    size_t oldSize = this->size; //keep track of the old size
    this->size = newSize; // set size to be the new size
    
    //rehash all items in the old array into the new array
    for(size_t i = 0; i < oldSize; i++){
        LinkedList* list = this->array[i];
        int bucketSize = list->getSize();
        for(int i = 0; i < bucketSize; i++){
            if(bucketSize > 0){
                int item = list->itemAtIndex(i);
                unsigned long index = this->hash(item);
                if(new_array[index]->contains(item)){ // item is already in table
                    continue;
                }
                new_array[index]->add(item);
            }
        }
        delete list;
    }
    
    delete[] this->array;
    this->array = new_array;

}


//insert
bool HashSet::insert(int item){
    unsigned long index = this->hash(item);
    if(this->array[index]->contains(item)){ // item is already in table
        return false;
    }
    this->array[index]->add(item);
    this->count++;

    double lf = (double) count/size;

    if(lf>0.7){
        resize();
    }
    return true;
}



//remove
bool HashSet::remove(int item){
    unsigned long index = this->hash(item);
    if(!this->array[index]->contains(item)){
        return false;
    }
    this->count--;
    return this->array[index]->remove(item);
}

//contains
bool HashSet::contains(int item){
    unsigned long index = this->hash(item);
    if(this->array[index]->contains(item)){ // item is already in table
        return true;
    }
    return false;
}

//number of items in hashset
size_t HashSet::len(){
    return this->count;
}

size_t HashSet::capacity(){
    size_t counter = 0;
    for (size_t i = 0; i < size; i++) {
        if(this->array[i]->isEmpty()){
            counter++;
        }
    }
    return counter;
}

//print the hash set
void HashSet::print(){
    printf("\nHashSet:\n\n");
    for (size_t i = 0; i < size; i++) {
        if(!this->array[i]->isEmpty()){
            printf("Bucket %d: ", i);
            this->array[i]->printList();
        }
    }
}
