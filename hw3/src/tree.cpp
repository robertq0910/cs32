#include <iostream>
#include <string>
using namespace std;

int countContains(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0) {
        return 1;   // Empty a2 always matches
    }
    if (n1 <= 0) {  // Empty a1 has no match 
        return 0;
    }
    if (a1[0] == a2[0]) {   // If first values match
        int firstMatch = countContains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
        int moreMatches = countContains(a1 + 1, n1 - 1, a2, n2);   // Keep finding more matches  
        return firstMatch + moreMatches;
    }
    else {  // If first values don't match 
        return countContains(a1 + 1, n1 - 1, a2, n2);
    }
}

void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

void split(string a[], int n, string splitter,
    int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > splitter)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < splitter)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

void order(string a[], int n)
{
    if (n <= 1) {   // Base case
        return;
    }
    int firstNotLess, firstGreater;
    split(a, n, a[0], firstNotLess, firstGreater);
    // Don't use return on the recursion here bc we gotta go on each time? 
    // I know this is gonna mean it gets lost but also this is a void function?
    order(a, firstNotLess);
    order(a + firstGreater, n - firstGreater);
}

int main()
{
    string array1[7] = { "donald", "keir", "claudia", "jinping", "keir", "claudia", "narendra" };
    string array2[3] = { "donald", "jinping", "claudia" };
    cerr << countContains(array1, 7, array2, 3) << endl;
    string array3[3] = { "donald", "claudia", "narendra" };
    cerr << countContains(array1, 7, array3, 3);
}
