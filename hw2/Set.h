#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

using ItemType = std::string;
//using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 140;

class Set {
public:
	Set();
	~Set();                        // Destructor
	Set(const Set& other);         // Copy constructor
	Set& operator=(const Set& rhs);// Assignment operator

	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int i, ItemType& value) const;
	void swap(Set& other);
	void dump() const;
private:
	int m_size;

	struct Node {
		ItemType data;

		Node* prev;
		Node* next;

		// Default constructor
		Node() : data(), prev(nullptr), next(nullptr){}

		// Constructor with arguments
		Node(ItemType const& val) {
			data = val;
			prev = nullptr;
			next = nullptr;
		}

	};

	Node* head;

};

void unite(const Set& s1, const Set& s2, Set& result);
void excludeInclude(const Set& s1, const Set& s2, Set& result);

#endif