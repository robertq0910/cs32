#include "newSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
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


void test()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x) && x == "pita");
    assert(ss.get(1, x) && x == "roti");
}


int main() {
    test();

    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { "12949672UL", "22949672UL", "32949672UL", "42949672UL", "52949672UL", "62949672UL" };

    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++) {
        assert(b.insert(v[k]));
    }

    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));

    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5]) && b.insert(v[5]));

    // Default constructor works
    assert(c.empty());
    assert(c.size() == 0);

    // contains() works
    assert(!b.contains(v[0]));
    assert(!b.contains("987654321UL"));

    Set d(5);      // b can hold at most 5 distinct items
    ItemType w[6] = { "12949672UL", "22949672UL", "32949672UL", "42949672UL", "52949672UL", "62949672UL" };

    // erase() works
    assert(d.insert(v[0]));
    assert(d.erase(v[0]));
    assert(!d.contains(w[0]));
    assert(d.size() == 0);       // size should decrease
    assert(!d.erase(v[0]));      // can't erase something already gone

    // get() works
    ItemType x;
    assert(b.get(0, x));
    assert(!b.get(-1, x));
    assert(!b.get(100, x));

    // Can't insert duplicates
    assert(b.insert("77777777UL"));
    assert(!b.insert("77777777UL"));



    // Copy assignment works
    Set copy = b;
    assert(copy.size() == b.size());
    for (int i = 0; i < b.size(); i++) {
        ItemType val1, val2;
        assert(b.get(i, val1) && copy.get(i, val2));
        assert(val1 == val2);
    }

    // Assignment operator works
    Set assign;
    assign = b;
    assert(assign.size() == b.size());
    for (int i = 0; i < b.size(); i++) {
        ItemType val1, val2;
        assert(b.get(i, val1) && assign.get(i, val2));
        assert(val1 == val2);
    }

    cout << "Passed all tests" << endl;
}
