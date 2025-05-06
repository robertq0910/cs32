#include <iostream>
#include <string>
using namespace std;

bool somePredicate(string s) {
    return !s.empty();
    // True if NOT empty
}

bool allTrue(const string a[], int n);  // string a[] means a pointer to a[0]
int countTrue(const string a[], int n);
int firstTrue(const string a[], int n);
int locateMax(const string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);

int main()
{
    string arr1[] = { "d", "b", "c" };
    allTrue(arr1, 3);
    //countTrue(arr1, 3);
    //firstTrue(arr1, 3);
    locateMax(arr1, 3);
    return 0;
}

bool allTrue(const string a[], int n) {
    if (n <= 0) {    // Base case 
        //cerr << "Base case, true-- sure it's all true bc there's nothing";
        return true;
    }
    //cerr << "Not base case, false";
    return somePredicate(a[0]) && allTrue(a + 1, n - 1);    // Move pointer in array forward by 1
}

int countTrue(const string a[], int n) {
    if (n <= 0) {
        return 0;
    }
    return countTrue(a + 1, n - 1) + (somePredicate(a[0]) ? 1 : 0); // more concise
}

int firstTrue(const string a[], int n) {
    if (n <= 0) {
        return -1;
    }
    // Check if first value is true 
    if (somePredicate(a[0])) {
        return 0;
    }
    // Start recursively checking everything else 
    int count = firstTrue(a + 1, n - 1);
    if (count == -1) {  // Can't find a true value
        cerr << "Can't find a true value";
        return -1;
    }
    else {
        cerr << "Found true value: " << count+1 << endl; 
        return count+1;
    }
    //return -1; // not needed
}

int locateMax(const string a[], int n) {
    if (n <= 0) {
        cout << "Invalid" << endl;
        return -1;
    }

    if (n == 1) {   // Base case with only 1 element
        cerr << "Only 1 element";
        return 0;
    }
    int max = locateMax(a + 1, n - 1);
    max++;
    if (a[0] >= a[max]) { 
        cerr << "New max is: 0";
        return 0;
    }
    else {
        cerr << "New max is: " << max;
        return max;
    }
}

bool contains(const string a1[], int n1, const string a2[], int n2) {
    if (n2 <= 0) {
        return true;
    }
    // use n1 < n2 to return false faster. To hav1 a1 contains a2, n1 must be >= n2
    if (n1 < n2/* && n2 > 0*/) { // n2 > 0 must be true after the above check
        return false;
    }
    
    if (a1[0] == a2[0]) {
        // Decreasing size of current arrays
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else {
        // If no match, advance a1
        // Returning a recursive sequence means that you restart function until you hit a base case and return true/false
        return contains(a1 + 1, n1 - 1, a2, n2);
    }
}