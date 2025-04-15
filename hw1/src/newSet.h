#ifndef NEWSET_INCLUDED
#define NEWSET_INCLUDED

#include <string>

using ItemType = std::string;
//using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 140;

class Set {
public:
	Set(); // Default constructor
	Set(int capacity); // Constructor for variable size
	~Set(); // Destructor
	Set(const Set& other); // Copy constructor 
	Set& operator = (const Set& other); // Assignment operator

	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int i, ItemType& value) const;
	void swap(Set& other);
	void dump() const;
private:
	ItemType* m_items; // Now a pointer for dynamic array
	int m_size;
	int m_capacity;
};


#endif
