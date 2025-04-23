#include "Set.h"
#include <iostream>

// Constructor 
Set::Set() {
    m_size = 0;

    // Circular doubly linked list, empty 
    head = new Node;
    head->next = head;
    head->prev = head;
}

// Destructor 
Set::~Set() {
    Node* p = head->next;
    while (p != head) {
        // Traverse through nodes and delete each one
        Node* temp = p;
        p = p->next;
        delete temp;
    }
    delete head;    // Delete dummy node
}

// Copy constructor 
Set::Set(const Set& other) {
    m_size = 0;
    // Create new dummy node 
    head = new Node;
    head->next = head;
    head->prev = head;

    Node* p = other.head->next;     // Node "p" belongs to "other" (it's one after head)
    while (p != other.head) {       // Iterate through "other" with "p" until we circle back to head
        insert(p->data);            // Insert the data from p 
        p = p->next;
    }

}

// Assignment operator 
Set& Set::operator=(const Set& rhs) {
    if (this != &rhs) {     // Check for self-assignment
        Set temp(rhs);      // Use copy constructor 
        swap(temp);         // Swap current object with copy 
    }
    return *this;
}


bool Set::empty() const {
    return m_size == 0;
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    Node* p;
    for (p = head->next; p != head; p = p->next) {
        if (p->data == value) {
            return false;
        }

        if (p->data > value) {
            break;
        }
    }

    // Create a new node  
    Node* newNode = new Node(value);   
    newNode->data = value; // This line is not needed. This is done in Node's ctor

    // Link new node 
    newNode->next = p;
    newNode->prev = p->prev;
    p->prev->next = newNode;
    p->prev = newNode;

    m_size++;
    return true;
}

bool Set::erase(const ItemType& value) {
    for (Node* p = head->next; p != head; p = p->next) {
        if (p->data == value) {
            // Relink neighbors
            p->prev->next = p->next;
            p->next->prev = p->prev;

            delete p;   // Free memory
            m_size--;
            return true;
        } 
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    for (Node* p = head->next; p != head; p = p->next) {
        if (p->data == value) {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    // GOAL: If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.

    if (i < 0 || i >= size()) {
        return false;
    }

    int j = 0;
    for (Node* p = head->next; p != head; p = p->next) {
        if (j == i) {
            value = p->data;
            return true;
        }
        j++;
    }
    return false;
}

void Set::swap(Set& other) {
    // GOAL: Exchange the contents of this set with the other one.
    // Point original head to new head 
    Node* temphead = head;
    head = other.head;
    other.head = temphead;

    // Exchange sizes
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}

void Set::dump() const {
    for (Node* p = head->next; p != head; p = p->next) {
        std::cerr << p->data << " ";
    }
}

void unite(const Set& s1, const Set& s2, Set& result) {
    // GOAL: replace result's values with s1 and s2's values
    
    ItemType value;     // Don't need to assign value bc functions pass by reference

    result = s1; // Copy s1's values to result. result's original values will be deleted

    for (int i = 0; i < s2.size();i++) {    // Loop thru s2 with get()
        if (s2.get(i, value) == true) {             // If calling get() on s2 is valid // 
            result.insert(value);   // Insert value into result
        }
    }
}

void excludeInclude(const Set& s1, const Set& s2, Set& result) {
    // GOAL: s2 - s1 = result
    // Copy s2 to result 
    
    result = s2;
    // Erase s1 values from result 
    ItemType value;

    for (int i = 0; i < s1.size(); i++) {
        if (s1.get(i, value) == true) {
            result.erase(value);
        }
    }

}