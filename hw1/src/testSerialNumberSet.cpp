#include "Set.h"
#include "SerialNumberSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int main()
{
    Set s;
    assert(s.empty());
    ItemType x = 42949672UL;
    assert(!s.get(42, x) && x == 42949672UL); // x unchanged by get failure
        // Get fails bc default constructor makes an empty set
        // Make sure it doesn't
    s.insert(32949672UL);
    assert(s.size() == 1);
    assert(s.get(0, x) && x == 32949672UL);

    s.erase(32949672UL);

    // Try to insert more than 140 items
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {

        assert(s.insert(52949672UL + i));
    }
    assert(!s.insert(52949671UL));  // Full so should overflow

    // Check swap()
    Set a, b;
    a.insert(12949672UL);
    a.insert(22949672UL);
    b.insert(32949672UL);

        // Before swap
    assert(a.size() == 2);
    assert(b.size() == 1);
    assert(a.contains(12949672UL));
    assert(a.contains(22949672UL));
    assert(b.contains(32949672UL));

    a.swap(b);

        // After swap
    assert(a.size() == 1);
    assert(b.size() == 2);
    assert(a.contains(32949672UL));
    assert(b.contains(12949672UL));
    assert(b.contains(22949672UL));

    // Check that repeats aren't allowed
    Set c;
    c.insert(62949672UL);
    assert(!c.insert(62949672UL));

    cout << "Passed all tests" << endl;

}



