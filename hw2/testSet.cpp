#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void test()
{
    Set ss;     // Default constructor
    assert(ss.size() == 0);     // Check for empty set
    assert(ss.empty());         // Check for empty set
    assert(!ss.erase("roti"));  // Can't erase a nonexisting value 
    assert(ss.insert("roti"));  // Add a node with value
    assert(ss.insert("pita"));  // Add another node with value 
    assert(ss.size() == 2);     // Check for set with 2 values 
    assert(ss.contains("pita"));    // Check that the set contains "pita"

    
    // Check get()
    ItemType x = "laobing";     // Create a variable x to store values from the get() function
    assert(ss.get(0, x) && x == "pita");    // Store 0th value ("pita") into variable x  
    assert(ss.get(1, x) && x == "roti");    // Store 1st value ("roti") into variable x

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
    
    a.insert("pizza");
    // Check that repeats aren't allowed
    Set c;
    c.insert("waffle");
    assert(!c.insert("waffle"));
    c.insert("eggs");
    assert(!c.insert("eggs"));

    // Check unite()
        // Result already contains a value
    unite(a, b, c);
    assert(c.size() == 3);
    assert(c.contains("pizza"));    // result set contains s1 + s2
    assert(c.contains("ramen"));
    assert(c.contains("spam"));
    assert(!c.contains("waffle"));  // result set doesn't contain original value
    assert(!c.contains("eggs"));  // result set doesn't contain original value

        // Result starts out empty 
    c.erase("pizza");
    c.erase("ramen");
    c.erase("spam");
    unite(a, b, c);
    assert(c.contains("pizza"));    
    assert(c.contains("ramen"));
    assert(c.contains("spam"));


    // Check excludeInclude()
        // Result already contains a value, both sets are diff sizes 
    Set d, e, f;
    d.insert("mango");  // s1 = mango
    e.insert("mango");  // s2 = mango, apple
    e.insert("apple");
    f.insert("banana");
    
    excludeInclude(d, e, f);
    assert(f.size() == 1);
    assert(f.contains("apple"));    // result set only contains s2 - s1
    assert(!f.contains("mango"));   // result set should only contain "apple"
    assert(!f.contains("banana"));  // result set doesn't contain origianl value

    excludeInclude(e, d, f);
    assert(f.empty());

        // Result already contains a value, both sets are the same size 
    d.insert("melon");
    excludeInclude(d, e, f);
    assert(f.size() == 1);
    assert(f.contains("apple"));    // result set only contains s2 - s1
    assert(!f.contains("melon"));   // result set should only contain "apple"
    assert(!f.contains("banana"));  // result set doesn't contain origianl value
    
        // Result starts out empty 
    f.erase("apple");
    excludeInclude(d, e, f);
    assert(f.size() == 1);
    assert(f.contains("apple"));
    assert(!f.contains("mango"));

}


int main()
{
    test();
    cout << "Passed all tests" << endl;
}
/*
void test(const Set& uls)
{
    assert(uls.size() == 2);
    assert(uls.contains(10));
    ItemType x = 30;
    assert(uls.get(0, x) && x == 10);
    assert(uls.get(1, x) && x == 20);
}

int main()
{
    Set s;
    assert(s.insert(20));
    assert(s.insert(10));
    test(s);
    cout << "Passed all tests" << endl;
}
*/
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


}

*/

