#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
/*
int main()
{
    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
        // Get fails bc default constructor makes an empty set
        // Make sure it doesn't 
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x) && x == "chapati");

    s.erase("chapati");

    // Try to insert more than 140 items 
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {
        
        assert(s.insert("mcflurry" + to_string(i)));
    }
    assert(!s.insert("overflow"));  // Full so should overflow 

    // Check swap()
    Set a, b;
    a.insert("pizza");
    a.insert("ramen");
    b.insert("spam");

        // Before swap 
    assert(a.size() == 2);
    assert(b.size() == 1);
    assert(a.contains("pizza"));
    assert(a.contains("ramen"));
    assert(b.contains("spam"));

    a.swap(b);

        // After swap
    assert(a.size() == 1);
    assert(b.size() == 2);
    assert(a.contains("spam"));
    assert(b.contains("pizza"));
    assert(b.contains("ramen"));

    // Check that repeats aren't allowed 
    Set c;
    c.insert("waffle");
    assert(!c.insert("waffle"));

    cout << "Passed all tests" << endl;
    

}*/
