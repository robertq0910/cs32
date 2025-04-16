#include "newSet.h"
#include <iostream>

Set::Set() {
    m_size = 0;
    m_capacity = DEFAULT_MAX_ITEMS;
    m_items = new ItemType[m_capacity];

}

Set::Set(int capacity) {
    m_size = 0;
    m_capacity = capacity;
    if (capacity < 0)
        exit(1); // Can't have a negative capacity
    m_items = new ItemType[m_capacity];
    // Reserve a chunk of memory to hold m_capacity # of ItemType objects
    // m_items is a pointer and points to the start of the dynamic array 
}

Set::~Set() {
    delete[] m_items;
}

Set::Set(const Set& other) {    // COPY CONSTRUCTOR
    m_size = other.m_size;  // Match sizes to passed object
    m_capacity = other.m_capacity;  // Match capacity to passed object
    m_items = new ItemType[m_capacity]; // Dynamically create a new item 

    for (int i = 0; i < m_size; i++) {
        m_items[i] = other.m_items[i];
    }

    // Don't need delete[] m_items here bc we're not changing the original version, just making a new copy
    // Copies content by POINTER, not underlying data-- so we need an assignment operator
}

Set& Set::operator = (const Set& other) {   // ASSIGNMENT OPERATOR
    //if this isn't pointing to its own address
    if (this != &other) {
        ItemType* newItems = new ItemType[other.m_capacity];
        for (int i = 0; i < other.m_size; i++) {
            newItems[i] = other.m_items[i];
        }
        delete[] m_items;
        m_items = newItems;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    return *this;   // Return reference so assignment operator is chainable like a = b = c 

    //allocate new memory that's the same size as other's array 
    //copy contents of rhs into new array
    //free memory of old array with delete
    //update data members to reflect values of other 
    //return this object 

}

/*
 bool Set::insert(const ItemType& value) {
    if (m_size >= m_capacity || contains(value)) {
        return false;
    }
    m_items[m_size] = value;
    m_size++;
    return true;
}
*/

 
 bool Set::insert(const ItemType& value) {
    if (m_size >= m_capacity || contains(value)) {
        return false;
    }
    m_items[m_size] = value;  // Insert the item first
    m_size++;                  // Increment m_size after inserting
    return true;
}
 
 
 

 /*
 bool Set::insert(const ItemType& value) {
    std::cerr << "Attempting to insert: " << value << std::endl;

    if (contains(value)) {
        std::cerr << "Item already exists in the set." << std::endl;
        return false;
    }

    if (m_size >= m_capacity) {
        std::cerr << "Set is full, cannot insert new item." << std::endl;
        return false;
    }

    // Insert the item...
    m_items[m_size++] = value;  // Example, adjust based on your insert logic
    std::cerr << "Successfully inserted: " << value << std::endl;
    return true;
}
 */



bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}


bool Set::erase(const ItemType& value) {
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value) {
            // Shift all later items to the left
            for (int j = i; j < m_size - 1; j++) {
                m_items[j] = m_items[j + 1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (int i = 0; i < m_size; i++) {
        if (m_items[i] == value)
            return true;
    }

    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (i < 0 || i >= m_size) {
        return false;
    }

    ItemType* sorted = new ItemType[m_size];
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.

    // Copy array "m_items" to array "sorted" 
    for (int j = 0; j < m_size; j++) {
        sorted[j] = m_items[j];
    }
    // Sort array "sorted" 
    for (int j = 0; j < m_size - 1; j++) {
        int minIndex = j;
        for (int k = j + 1; k < m_size; k++) {
            if (sorted[k] < sorted[minIndex]) { // If the next value is smaller, that becomes the minimum 
                minIndex = k;
            }
        }

        ItemType temp = sorted[j];
        sorted[j] = sorted[minIndex];
        sorted[minIndex] = temp;
    }

    value = sorted[i];
    delete[] sorted;

    return true;
}

void Set::swap(Set& other) {   
    // Swap sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;

    // Swap capacities 
    int tempCapacity = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tempCapacity;

    // Swap pointers 
    ItemType* tempItems = m_items;
    m_items = other.m_items;
    other.m_items = tempItems;
}

void Set::dump() const {
    for (int i = 0; i < m_size; i++) {
        std::cerr << m_items[i] << " ";
    }

}
